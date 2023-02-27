#!/bin/bash

#for collective in "binomialtreereduce"  "binarytreebcast"  "binomialtreebcast"  "nwaydissemination"  \
#                  "doublering"  "gather"  "scatter"  "linbarrier"  "dissemination"  "random_bisect"  \
#                  "random_bisect_fd_sym"  "linear_alltoall" #"pipelinedring" "pipelinedringdep" 
#for collective in "binarytreebcast"  "binomialtreebcast"  "nwaydissemination" "pipelinedring" "linear_alltoall" "nwaydissemination_nocompute"
ITERATIONS=10000
for collective in "pipelinedring"  "nwaydissemination_nocompute"
do
    for MESSAGE_SIZE in 16 16384 16777216  
    do
        for NODES in 4 8 16 32 64 128
        do
            SEGMENTSIZE=""
            EXTRA_FLAGS=""
            CC_SUFFIX=""
            if [ "$collective" == "pipelinedring" ]; then
                SEGMENTSIZE="--segmentsize "$((MESSAGE_SIZE / NODES))
            fi                        
            echo "Converting "${collective}" "${MESSAGE_SIZE}" "${NODES}"..."
            if [ "$collective" == "nwaydissemination_nocompute" ]; then
                collective_real="nwaydissemination"
                EXTRA_FLAGS="--skip_compute"
                CC_SUFFIX="_nocompute"
            else
                collective_real=${collective}
            fi
            ../schedgen/schedgen -s ${NODES} -p ${collective_real} -d ${MESSAGE_SIZE} ${SEGMENTSIZE} -o .schedgen.tmp > /dev/null
            # Blocking send, NB receive with Wait
            ./goal2mpi.py --iterations ${ITERATIONS} --prioritize_receive --input .schedgen.tmp --output ../../benchmarks/collectives/${collective}_${NODES}_${MESSAGE_SIZE}.c --message_size=${MESSAGE_SIZE} ${EXTRA_FLAGS}
            # Non-blocking send with wait, NB receive with wait
            ./goal2mpi.py --iterations ${ITERATIONS} --prioritize_receive --input .schedgen.tmp --output ../../benchmarks/collectives/${collective}_nbsend_${NODES}_${MESSAGE_SIZE}.c --message_size=${MESSAGE_SIZE} ${EXTRA_FLAGS} --nb_send
            # With --use_tests
            ./goal2mpi.py --iterations ${ITERATIONS} --prioritize_receive --input .schedgen.tmp --output ../../benchmarks/collectives/${collective}_test_${NODES}_${MESSAGE_SIZE}.c --message_size=${MESSAGE_SIZE} ${EXTRA_FLAGS} --use_tests             
            rm .schedgen.tmp
        done
    done
done