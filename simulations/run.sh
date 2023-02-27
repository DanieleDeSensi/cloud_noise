#!/bin/bash
TESTS=500
CORES=$(grep "cpu cores" /proc/cpuinfo | sort -u | cut -d":" -f2 | awk '{s+=$1} END {print s}' | tr -d '\n')
#TESTS_PER_CORE=$((TESTS/CORES))
#TESTS_PER_CORE=$((TESTS_PER_CORE + 1))
TESTS_PER_CORE=$(python3 -c "from math import ceil; print(int(ceil($TESTS/$CORES)))")
export PYTHONUNBUFFERED=1
#PROVIDERS="--provider AWS,Azure,GCP,Alps,Daint,DEEP-EST"
PROVIDERS="--provider Daint,Alps,DEEP-EST,Azure,AWS"
# Validation data
#PARAMS="--noises os+net --hpc_only --placements sr,dr --collective pingpong --nodes 2 --msgsize 1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216 ${PROVIDERS}"
#./simulate.py  ${PARAMS} --generate_only
#seq 1 ${CORES} | parallel -k --linebuffer -N0 -j${CORES} ./simulate.py  ${PARAMS} --num_tests "${TESTS_PER_CORE}"
PARAMS="--noises os+net --hpc_only --placements dr --collective nwaydissemination_nocompute --nodes 32 --msgsize 16 ${PROVIDERS}"
./simulate.py  ${PARAMS} --generate_only
seq 1 ${CORES} | parallel -k --linebuffer -N0 -j${CORES} ./simulate.py  ${PARAMS} --num_tests "${TESTS_PER_CORE}"
PARAMS="--noises os+net --hpc_only --placements dr --collective pipelinedring --nodes 32 --msgsize 16777216 ${PROVIDERS}"
./simulate.py  ${PARAMS} --generate_only
seq 1 ${CORES} | parallel -k --linebuffer -N0 -j${CORES} ./simulate.py  ${PARAMS} --num_tests "${TESTS_PER_CORE}"
#PARAMS="--noises none,os+net --hpc_only --placements dr --collective MILC --nodes 64 --msgsize 16777216 ${PROVIDERS}"
#./simulate.py  ${PARAMS} --generate_only
#seq 1 ${CORES} | parallel -k --linebuffer -N0 -j${CORES} ./simulate.py  ${PARAMS} --num_tests "${TESTS_PER_CORE}"
# nwaydissemination at scale
#PARAMS="--placements dr --hpc_only --collective nwaydissemination_nocompute --nodes 4,64,1024,16384 --msgsize 16,131072 ${PROVIDERS}"
#./simulate.py  ${PARAMS} --generate_only
#seq 1 ${CORES} | parallel -k --linebuffer -N0 -j${CORES} ./simulate.py  ${PARAMS} --num_tests "${TESTS_PER_CORE}"
## ring at scale
#PARAMS="--placements dr --hpc_only --collective pipelinedring --nodes 4,16,64,256,1024 --msgsize 536870912 ${PROVIDERS}"
#./simulate.py  ${PARAMS} --generate_only
#seq 1 ${CORES} | parallel -k --linebuffer -N0 -j${CORES} ./simulate.py  ${PARAMS} --num_tests "${TESTS_PER_CORE}"