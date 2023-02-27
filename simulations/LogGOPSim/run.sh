#!/bin/bash

# Example
# ./run.sh binarytreebcast 64 1024 ../../data/aws_c5n.metal_cluster/2022_03_16_10_13_52/ 123 456 789 1048576

#Tools
schedgen=../schedgen/schedgen
txt2bin=../LogGOPSim/txt2bin
loggopsim=../LogGOPSim/LogGOPSim

# Parameters (in ps!!!)
collective=$1
P=$2
size=$3
noisepath=$4
o=$5
g=$6
O=$7
S=$8

Lfile=${noisepath}/ng_netnoise_mpi_lat.out
Gfile=${noisepath}/ng_netnoise_mpi_bw.out
OSfile=${noisepath}/ng_osnoise.out

# Generate schedule
#echo "$schedgen -s $P -p $collective -d $size"
$schedgen -s $P -p $collective -d $size -o .sched.txt.tmp

# txt2bin
$txt2bin -i .sched.txt.tmp -o .sched.bin.tmp

# prepare input files for L and G (one column, in ps)
# Also exclude the first 10 warmup samples
cat $Lfile | grep -v '#' | awk 'NR%1000 > 10' | awk '{print int(1000000*$2)}' > .lat.out
cat $Gfile | grep -v '#' | awk 'NR%1000 > 10' | awk '{print int(1000000*$2/$1)}' > .bw.out
cat $OSfile | grep -v '#' | awk '{print int(1000*$1)"\t"int(1000*$2)}' > .os.out # ns to ps

# run simulation
#echo "$loggopsim -f .sched.bin.tmp --LogGOPS_Gfile=.bw.out --LogGOPS_Lfile=.lat.out -o=$o -g=$g -O=$O -S=$S"
$loggopsim -f .sched.bin.tmp --LogGOPS_Gfile=.bw.out --LogGOPS_Lfile=.lat.out -o $o -g $g -O $O -S $S --noise-trace=.os.out

rm .lat.out .bw.out