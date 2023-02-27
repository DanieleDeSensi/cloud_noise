# Simple script that invokes run.sh for MKL and redirect the result in a file

# Instructions
# - edit gemmbench.c and define the THEO_PEAK macro with the expected theo peak. If needed change the number of execution (LOOP)
# - compile with "make mkl" (icc and MKL paths must be set)
# - run the script

# Theo peak can be found in:
# - Intel: https://www.intel.com/content/dam/support/us/en/documents/processors/APP-for-Intel-Xeon-Processors.pdf

#!/bin/bash
THREADS=""
KEY=""


while getopts k:t: flag
do
    case "${flag}" in
	k) KEY=${OPTARG};;
	t) THREADS=${OPTARG};;
    esac
done


if [ "$KEY" = "" ] ; then
    echo "Please specify the key in the form \'Provider,InstanceType,Same Rack,Time\' with -k."
    exit 1
fi

if [ "$THREADS" = "" ] ; then
    THREADS=$(grep \"cpu cores\" /proc/cpuinfo | sort -u | cut -d":" -f2 | awk '{s+=$1} END {print s}')
fi

OUT_PATH=../../data/${SYSTEM}
TIMESTAMP=$(TZ=":Europe/Rome" date +%Y_%m_%d_%H_%M_%S)
OUT_FOLDER=${OUT_PATH}/${TIMESTAMP}
mkdir -p ${OUT_FOLDER}

# Actual benchmarking

COMPR_FILE=gemm_${SYSTEM}_${INSTANCETYPE}_${PLACEMENT}_$(TZ=":Europe/Rome" date +%Y_%m_%d_%H_%M_%S)
SZ="16 128 1024 2048 4096 8192"
for sz in $SZ
do
    echo "Running with N = $sz, with $THREADS threads"
    out_file="gemm_${SYSTEM}_${INSTANCETYPE}_${PLACEMENT}_$sz.dat"
    echo -e "#N\tTIME(s)\tGFLOPs/s\tTHEO_PEAK" > $out_file # delete file if present
    ./run.sh $THREADS $sz mkl >>$out_file
done

echo "Compressing ..."
tar vcfJ ${COMPR_FILE}.tar.xz gemm_*.dat


