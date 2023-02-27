#!/bin/bash
source conf.sh

GREEN=$(tput setaf 2)
RED=$(tput setaf 1)
NC=$(tput sgr0)

KEY=""
while getopts k: flag
do
    case "${flag}" in
        k) KEY=${OPTARG};;
    esac
done

if [ "$KEY" = "" ] ; then   
    echo "Please specify the key in the form \'Provider,InstanceType,Collectives,\' with -k."
    exit 1
fi

OUT_PATH=../data/${SYSTEM}
TIMESTAMP=$(TZ=":Europe/Rome" date +%Y_%m_%d_%H_%M_%S)
OUT_FOLDER=${OUT_PATH}/${TIMESTAMP}
mkdir -p ${OUT_FOLDER}

echo "${KEY}",${OUT_FOLDER} >> ../data/description.csv

#for collective in "binomialtreereduce"  "binarytreebcast"  "binomialtreebcast"  "nwaydissemination"  \
#                  "doublering"  "gather"  "scatter"  "linbarrier"  "dissemination"  "random_bisect"  \
#                  "random_bisect_fd_sym"  "linear_alltoall" #"pipelinedring" "pipelinedringdep" 
for nodes in 4 8 16 32
do
    MESSAGE_SIZE=16
    for collective in "nwaydissemination_nocompute" "nwaydissemination_nocompute_test" "nwaydissemination_nocompute_nbsend"
    do
        echo -n "Running "${collective}" "${MESSAGE_SIZE}" "${nodes}"..."
        ${MPIRUN} ${MPIRUN_MAP_BY_NODE_FLAG} ${MPIRUN_HOSTFILE_LONG_FLAG} -n ${nodes} ${MPIRUN_ADDITIONAL_FLAGS} ./collectives/${collective}_${nodes}_${MESSAGE_SIZE}.bin > ${OUT_FOLDER}/${collective}_${nodes}_${MESSAGE_SIZE}.csv
        echo " ${GREEN}[Done]${NC}"
    done

    MESSAGE_SIZE=16777216
    for collective in "pipelinedring" "pipelinedring_test" "pipelinedring_nbsend"
    do
        echo -n "Running "${collective}" "${MESSAGE_SIZE}" "${nodes}"..."
        ${MPIRUN} ${MPIRUN_MAP_BY_NODE_FLAG} ${MPIRUN_HOSTFILE_LONG_FLAG} -n ${nodes} ${MPIRUN_ADDITIONAL_FLAGS} ./collectives/${collective}_${nodes}_${MESSAGE_SIZE}.bin > ${OUT_FOLDER}/${collective}_${nodes}_${MESSAGE_SIZE}.csv
        echo " ${GREEN}[Done]${NC}"
    done
done

echo "Compressing "${OUT_FOLDER}" ..."
pushd ${OUT_PATH}
tar vcfJ ${TIMESTAMP}.tar.xz ${TIMESTAMP}
rm -rf ${TIMESTAMP}
popd
