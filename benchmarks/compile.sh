#!/bin/bash
source conf.sh

GREEN=$(tput setaf 2)
RED=$(tput setaf 1)
NC=$(tput sgr0)

pushd misc
    ${MPI_COMPILER} hoverboard.c -o hoverboard
    if [ ! -f "hoverboard" ]; then
        echo "${RED}[Error] hoverboard compilation failed, please check error messages above.${NC}"
        exit 1
    fi

    ${MPI_COMPILER} check_mpi_wtime_res.c -o check_mpi_wtime_res
    if [ ! -f "check_mpi_wtime_res" ]; then
        echo "${RED}[Error] check_mpi_wtime_res compilation failed, please check error messages above.${NC}"
        exit 1
    fi
popd

${MPI_COMPILER} -c -fPIC libstripe/libstripe.c -o libstripe/libstripe.o
if [ ! -f "libstripe/libstripe.o" ]; then
    echo "${RED}[Error] libstripe.o compilation failed, please check error messages above.${NC}"
    exit 1
fi

${MPI_COMPILER} -c -fPIC thread-pool/thpool.c -o thread-pool/thpool.o
if [ ! -f "thread-pool/thpool.o" ]; then
    echo "${RED}[Error] thpool.o compilation failed, please check error messages above.${NC}"
    exit 1
fi

${MPI_COMPILER} -shared -pthread -o libstripe/libstripe.so libstripe/libstripe.o thread-pool/thpool.o
if [ ! -f "libstripe/libstripe.so" ]; then
    echo "${RED}[Error] libstripe.so compilation failed, please check error messages above.${NC}"
    exit 1
fi

# Compile collectives
#for collective in "binarytreebcast"  "binomialtreebcast"  "nwaydissemination" "pipelinedring" "linear_alltoall" "nwaydissemination_nocompute"
for collective in "pipelinedring" "nwaydissemination_nocompute" "pipelinedring_test" "nwaydissemination_nocompute_test" "pipelinedring" "nwaydissemination_nocompute" "pipelinedring_nbsend" "nwaydissemination_nocompute_nbsend"
do
    for MESSAGE_SIZE in 16 16384 16777216  
    do
        for NODES in 4 8 16 32
        do
            ${MPI_COMPILER} collectives/${collective}_${NODES}_${MESSAGE_SIZE}.c -o collectives/${collective}_${NODES}_${MESSAGE_SIZE}.bin
            if [ ! -f "collectives/${collective}_${NODES}_${MESSAGE_SIZE}.bin" ]; then
                echo "${RED}[Error] collectives/${collective}_${NODES}_${MESSAGE_SIZE}.bin compilation failed, please check error messages above.${NC}"
                exit 1
            fi
        done
    done
done

# Compile netgauge
pushd netgauge
    ./configure ${NG_CONFIGURE_FLAGS}
    make
    if [ ! -f "netgauge" ]; then
        echo "${RED}[Error] netgauge compilation failed, please check error messages above.${NC}"
        exit 1
    fi

    HAS_MPI=$(cat config.h | grep NG_MPI | cut -d ' ' -f 3)
    if [ "$HAS_MPI" != 1 ] ; then
        echo "${RED}[Error] netgauge did not find MPI. Please specify MPI path in ./configure${NC}"
        exit 1
    fi
popd

# Compile GEMM benchmark
pushd gemm
    GEMM_TYPE=""  
    IS_INTEL=$(grep -c GenuineIntel /proc/cpuinfo)    
    if [ $IS_INTEL -gt 0 ] ; then   
        GEMM_TYPE=mkl
    else
        GEMM_TYPE=blis
    fi
    make ${GEMM_TYPE}
    if [ ! -f "dgemmbench.${GEMM_TYPE}" ]; then
        echo "${RED}[Error] gemmbench compilation failed, please check error messages above.${NC}"
        exit 1
    fi        
popd

echo "${GREEN}Everything compiled successfully.${NC}"