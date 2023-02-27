#!/bin/bash
# If you want to debug and see that everything would run correctly:
# - ./run.sh -f 
#
# If you want to run the full thing (it will take 1-1.5 hours):
# - ./run.sh
#
# If you want to run the long test (it will take 24 hours):
# - ./run.sh -l
#
# If you want to run only OS noise (it will take 5-10 mins):
# - ./run.sh -s

source conf.sh

RUN_NG_NOISE=true
OS_NOISE_TEST_DURATION_SECS=120
OS_NOISE_MAX_TEST_DURATION_SECS=360
NET_NOISE_TEST_DURATION_SECS=3600
NET_NOISE_TEST_DURATION_SECS_DAY=86400
RUN_NG_ONLY_OS_NOISE=false
RUN_GEMM=true
KEY=""
THREADS=""

while getopts flso:n:k:t: flag
do
    case "${flag}" in
        f) RUN_NG_NOISE=false;;        
        l) NET_NOISE_TEST_DURATION_SECS=${NET_NOISE_TEST_DURATION_SECS_DAY};;
        s) RUN_NG_ONLY_OS_NOISE=true;;
        o) OS_NOISE_TEST_DURATION_SECS=${OPTARG};;
        n) NET_NOISE_TEST_DURATION_SECS=${OPTARG};;
        k) KEY=${OPTARG};;
        t) THREADS=${OPTARG};;
    esac
done

if [ "$KEY" = "" ] ; then   
    echo "Please specify the key in the form \'Provider,InstanceType,Same Rack,Time\' with -k."
    exit 1
fi

ONE_ONE_MAX_MSG=16777216
NG_ITERATIONS=1000 # NG -c parameter
PARSE_OSU=" grep -v '#' | tr -s ' ' | tr ' ' ','"

GREEN=$(tput setaf 2)
RED=$(tput setaf 1)
NC=$(tput sgr0)

OUT_PATH=../data/${SYSTEM}
TIMESTAMP=$(TZ=":Europe/Rome" date +%Y_%m_%d_%H_%M_%S)
OUT_FOLDER=${OUT_PATH}/${TIMESTAMP}
mkdir -p ${OUT_FOLDER}

echo "${KEY}",${OUT_FOLDER} >> ../data/description.csv
PROVIDER=$(echo ${KEY} | cut -d ',' -f 1)
INSTANCE=$(echo ${KEY} | cut -d ',' -f 2)
# For backward compatibility
echo "${PROVIDER},${INSTANCE},Compute,,${OUT_FOLDER}/gemm_" >> ../data/description.csv

RUN_NG=true 
RUN_HOVERBOARD=true

echo "Writing to "${OUT_FOLDER}

START_TOTAL=$SECONDS

if [ "$RUN_NG" = true ] ; then   
    if [ "$RUN_NG_NOISE" = true ] ; then
        # Netgauge - OS noise
        START_TEST=$SECONDS
        echo -n "Running netgauge OS noise test for ${OS_NOISE_TEST_DURATION_SECS} seconds ..."
        end=$((SECONDS+OS_NOISE_TEST_DURATION_SECS))
        while [ $SECONDS -lt $end ]; do        
            OUT=$(timeout ${OS_NOISE_MAX_TEST_DURATION_SECS} ${MPIRUN} ${MPIRUN_PINNING_FLAGS} ${MPIRUN_MAP_BY_NODE_FLAG} ${MPIRUN_HOSTFILE_FLAG} -n 1 ${MPIRUN_ADDITIONAL_FLAGS} ./netgauge/netgauge -o ${OUT_FOLDER}/ng_osnoise.out.tmp -m mpi -x noise)
            cat ${OUT_FOLDER}/ng_osnoise.out.tmp >> ${OUT_FOLDER}/ng_osnoise.out
            echo "${OUT}" >> ${OUT_FOLDER}/ng_osnoise.cmdout
            rm ${OUT_FOLDER}/ng_osnoise.out.tmp        
            if [ "$SYSTEM" = "daint" ] ; then
                sleep 1
            fi
        done
        echo " ${GREEN}[Done][$((SECONDS-START_TEST)) seconds]${NC}"

        if [ "$RUN_NG_ONLY_OS_NOISE" = true ] ; then
            echo "${GREEN}[Tests completed][$((SECONDS-START_TOTAL)) seconds]${NC}"

            echo "Compressing "${OUT_FOLDER}" ..."
            pushd ${OUT_PATH}
            tar vcfJ ${TIMESTAMP}.tar.xz ${TIMESTAMP}
            rm -rf ${TIMESTAMP}
            popd
            exit 0
        fi

        # Netgauge - Network noise - MPI
        START_TEST=$SECONDS
        echo -n "Running netgauge network noise MPI test for ${NET_NOISE_TEST_DURATION_SECS} seconds ..."
        end=$((SECONDS+NET_NOISE_TEST_DURATION_SECS))
        while [ $SECONDS -lt $end ]; do        
            # Latency (1 byte msgs)
            OUT=$(${MPIRUN} ${MPIRUN_PINNING_FLAGS} ${MPIRUN_MAP_BY_NODE_FLAG} ${MPIRUN_HOSTFILE_FLAG} -n 2 ${MPIRUN_ADDITIONAL_FLAGS} ./netgauge/netgauge -c ${NG_ITERATIONS} -g 1 -s 1-1 -f ${OUT_FOLDER}/ng_one_one.out.tmp -m mpi -x one_one)
            cat ${OUT_FOLDER}/ng_one_one.out.tmp >> ${OUT_FOLDER}/ng_netnoise_mpi_lat.out
            echo "${OUT}" >> ${OUT_FOLDER}/ng_netnoise_mpi_lat.cmdout
            rm ${OUT_FOLDER}/ng_one_one.out.tmp        
            if [ "$SYSTEM" = "daint" ] ; then
                sleep 1
            fi

            # Bandwidth (${ONE_ONE_MAX_MSG} bytes msgs)            
            if [ "$NET_NOISE_CONC" != 1 ] ; then
                export LD_PRELOAD="./libstripe/libstripe.so"
                export LIBSTRIPE_FACTOR=${NET_NOISE_CONC}
            fi

            OUT=$(${MPIRUN} ${MPIRUN_PINNING_FLAGS} ${MPIRUN_MAP_BY_NODE_FLAG} ${MPIRUN_HOSTFILE_FLAG} -n 2 ${MPIRUN_ADDITIONAL_FLAGS} ./netgauge/netgauge -c ${NG_ITERATIONS} -g 1 -s ${BW_SATURATING_SIZE}-${BW_SATURATING_SIZE} -f ${OUT_FOLDER}/ng_one_one.out.tmp -m mpi -x one_one)
            cat ${OUT_FOLDER}/ng_one_one.out.tmp >> ${OUT_FOLDER}/ng_netnoise_mpi_bw.out
            echo "${OUT}" >> ${OUT_FOLDER}/ng_netnoise_mpi_bw.cmdout
            rm ${OUT_FOLDER}/ng_one_one.out.tmp
            if [ "$NET_NOISE_CONC" != 1 ] ; then
                unset LD_PRELOAD
                unset LIBSTRIPE_FACTOR
            fi
            if [ "$SYSTEM" = "daint" ] ; then
                sleep 1
            fi
        done        
        echo " ${GREEN}[Done][$((SECONDS-START_TEST)) seconds]${NC}"
    fi
    
    # Timer res
    START_TEST=$SECONDS
    echo -n "Checking MPI_Wtime resolution ..."
    OUT=$(${MPIRUN} ${MPIRUN_MAP_BY_NODE_FLAG} ${MPIRUN_HOSTFILE_FLAG} -n 1 ${MPIRUN_ADDITIONAL_FLAGS} ./misc/check_mpi_wtime_res)
    echo "${OUT}" >> ${OUT_FOLDER}/wtime_res.out
    echo " ${GREEN}[Done][$((SECONDS-START_TEST)) seconds]${NC}"

    # Netgauge - LogGP        
    START_TEST=$SECONDS
    echo -n "Running netgauge LogGP test ..."  
    if [ "$NET_NOISE_CONC" != 1 ] ; then
        export LD_PRELOAD="./libstripe/libstripe.so"
        export LIBSTRIPE_FACTOR=${NET_NOISE_CONC}
    fi
    OUT=$(${MPIRUN} ${MPIRUN_PINNING_FLAGS} ${MPIRUN_MAP_BY_NODE_FLAG} ${MPIRUN_HOSTFILE_FLAG} -n 2 ${MPIRUN_ADDITIONAL_FLAGS} ./netgauge/netgauge -o ${OUT_FOLDER}/ng_loggp.out.tmp -m mpi -x loggp)
    cat ${OUT_FOLDER}/ng_loggp.out.tmp >> ${OUT_FOLDER}/ng_loggp.out
    echo "${OUT}" >> ${OUT_FOLDER}/ng_loggp.cmdout
    rm ${OUT_FOLDER}/ng_loggp.out.tmp        
    if [ "$NET_NOISE_CONC" != 1 ] ; then
        unset LD_PRELOAD
        unset LIBSTRIPE_FACTOR
    fi
    if [ "$SYSTEM" = "daint" ] ; then
        sleep 1
    fi
    echo " ${GREEN}[Done][$((SECONDS-START_TEST)) seconds]${NC}"

    for BI in "" "_mpi_bidirect"
    do
        for CONC in 1 2 4 8 16
        do
            # Netgauge - Latency & Bw - MPI - Concurrent connections
            if [[ "$CONC" != 1 ]] ; then
                START_TEST=$SECONDS
                echo -n "Running netgauge one_one${BI} MPI test with "${CONC}" concurrent connections ..."  
                SCALED_DOWN_MSG=$((ONE_ONE_MAX_MSG / CONC))            
                OUT=$(${MPIRUN} ${MPIRUN_MAP_BY_NODE_FLAG} ${MPIRUN_HOSTFILE_FLAG} -n $((${CONC} * 2)) ${MPIRUN_ADDITIONAL_FLAGS} ./netgauge/netgauge -c ${NG_ITERATIONS} -g 1 -s -${SCALED_DOWN_MSG} -f ${OUT_FOLDER}/ng_one_one${BI}.out.tmp -m mpi -x one_one${BI})
                cat ${OUT_FOLDER}/ng_one_one${BI}.out.tmp >> ${OUT_FOLDER}/ng_one_one${BI}_mpi_conc${CONC}.out
                echo "${OUT}" >> ${OUT_FOLDER}/ng_one_one${BI}_mpi_conc${CONC}.cmdout
                rm ${OUT_FOLDER}/ng_one_one${BI}.out.tmp
                if [ "$SYSTEM" = "daint" ] ; then
                    sleep 1
                fi
                echo " ${GREEN}[Done][$((SECONDS-START_TEST)) seconds]${NC}"
            fi

            # Netgauge - Latency & Bw - MPI - Striping            
            START_TEST=$SECONDS
            echo -n "Running netgauge one_one${BI} MPI test with striping="${CONC}" ..."  
            if [ "$CONC" != 1 ] ; then
                export LD_PRELOAD="./libstripe/libstripe.so"
                export LIBSTRIPE_FACTOR=${CONC}
            fi
            OUT=$(${MPIRUN} ${MPIRUN_PINNING_FLAGS} ${MPIRUN_MAP_BY_NODE_FLAG} ${MPIRUN_HOSTFILE_FLAG} -n 2 ${MPIRUN_ADDITIONAL_FLAGS} ./netgauge/netgauge -c ${NG_ITERATIONS} -g 1 -s -${ONE_ONE_MAX_MSG} -f ${OUT_FOLDER}/ng_one_one${BI}.out.tmp -m mpi -x one_one${BI})
            cat ${OUT_FOLDER}/ng_one_one${BI}.out.tmp >> ${OUT_FOLDER}/ng_one_one${BI}_mpi_stripe${CONC}.out
            echo "${OUT}" >> ${OUT_FOLDER}/ng_one_one${BI}_mpi_stripe${CONC}.cmdout
            rm ${OUT_FOLDER}/ng_one_one${BI}.out.tmp
            if [ "$CONC" != 1 ] ; then
                unset LD_PRELOAD
                unset LIBSTRIPE_FACTOR
            fi
            if [ "$SYSTEM" = "daint" ] ; then
                sleep 1
            fi
            echo " ${GREEN}[Done][$((SECONDS-START_TEST)) seconds]${NC}"
        done
    done
fi

if [ "$RUN_HOVERBOARD" = true ] ; then
    # Hoverboard
    START_TEST=$SECONDS
    echo -n "Running hoverboard test ..."
    if [ "$NET_NOISE_CONC" != 1 ] ; then
        export LD_PRELOAD="./libstripe/libstripe.so"
        export LIBSTRIPE_FACTOR=${NET_NOISE_CONC}
    fi
    for REPS in 1
    do
        for SLEEP_TIME in 1000000000 800000000 600000000 400000000 200000000 0 200000001 400000001 600000001 800000001 1000000001
        do        
            ${MPIRUN} ${MPIRUN_PINNING_FLAGS} ${MPIRUN_MAP_BY_NODE_FLAG} ${MPIRUN_HOSTFILE_FLAG} -n 2 ${MPIRUN_ADDITIONAL_FLAGS} ./misc/hoverboard 1048576 ${REPS} ${SLEEP_TIME} ${OUT_FOLDER}/hoverboard.tmp
            cat ${OUT_FOLDER}/hoverboard.tmp >> ${OUT_FOLDER}/hoverboard_reps_${REPS}.out
            if [ "$SYSTEM" = "daint" ] ; then
                sleep 1
            fi
        done
        rm ${OUT_FOLDER}/hoverboard.tmp
        sleep 10
    done    
    if [ "$NET_NOISE_CONC" != 1 ] ; then
        unset LD_PRELOAD
        unset LIBSTRIPE_FACTOR
    fi
    echo " ${GREEN}[Done][$((SECONDS-START_TEST)) seconds]${NC}"
fi

if [ "$RUN_GEMM" = true ] ; then
    pushd gemm
    if [ "$THREADS" = "" ] ; then
        THREADS=$(${MPIRUN} ${MPIRUN_MAP_BY_NODE_FLAG} ${MPIRUN_HOSTFILE_FLAG} -n 1 ${MPIRUN_ADDITIONAL_FLAGS} grep "cpu cores" /proc/cpuinfo | sort -u | cut -d":" -f2 | awk '{s+=$1} END {print s}')
    fi
    MKL_OR_BLIS=""
    IS_INTEL=$(grep -c GenuineIntel /proc/cpuinfo)
    if [ $IS_INTEL -gt 0 ] ; then   
        MKL_OR_BLIS="mkl"
    else
        MKL_OR_BLIS="blis"
    fi
    # GEMM
    START_TEST=$SECONDS
    echo -n "Running GEMM test [${MKL_OR_BLIS}] ..."
    SZ="16 128 1024 2048 4096 8192"
    for sz in $SZ
    do
        echo -e "#N\tTIME(s)\tGFLOPs/s\tTHEO_PEAK" > ../${OUT_FOLDER}/gemm_${sz}.dat
        ${MPIRUN} ${MPIRUN_MAP_BY_NODE_FLAG} ${MPIRUN_HOSTFILE_FLAG} -n 1 ${MPIRUN_ADDITIONAL_FLAGS} ./run.sh $THREADS $sz ${MKL_OR_BLIS} >> ../${OUT_FOLDER}/gemm_${sz}.dat
        if [ "$SYSTEM" = "daint" ] ; then
            sleep 1
        fi
    done
    echo " ${GREEN}[Done][$((SECONDS-START_TEST)) seconds]${NC}"
    popd
fi

rm ng.out*
echo "${GREEN}[Tests completed][$((SECONDS-START_TOTAL)) seconds]${NC}"

echo "Compressing "${OUT_FOLDER}" ..."
pushd ${OUT_PATH}
tar vcfJ ${TIMESTAMP}.tar.xz ${TIMESTAMP}
rm -rf ${TIMESTAMP}
popd
