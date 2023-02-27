#!/bin/bash

# Saves the current number of used nodes/cpu according to slurm
# Usage : daint_status.sh <output_file_name>
# Note the file gets overwritten

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <output_file_name>"
    exit -1
fi

# File names and sleep time

NODE_FILE=$1_nodes
CPU_FILE=$1_cpus
SLEEP_SECS=58 # with 58 secs, it should print something every minute (sinfo takes a couple of seconds to return the result)

# Save file if existing, just in case
if [ -f $NODE_FILE ]; then
    echo "$NODE_FILE exists"
    exit -1
fi

if [ -f $CPU_FILE ]; then
    echo "$CPU_FILE exists"
    exit -1
fi


date > $1

# Headers
echo -e "#Node Status\n#Time\tAct\tIdl\tOth\tTot" > $NODE_FILE
echo -e "#CPU Status\n#Time\tAct\tIdl\tOth\tTot" > $CPU_FILE

echo "Monitoring cluster status...."
echo "Output files: $NODE_FILE, $CPU_FILE"
echo "(This will run until killed, nothing will be print out)"

while true; do

    #### Node states
    #remove header and starting character '='
    str=$(sinfo -o=%F | tail -1 | cut -c2-)

    # replace '/' with tabs and print date
    echo -e "$(date +"%H:%M:%S")\t${str////$'\t'}" >> $NODE_FILE

    #### CPU states
    #remove header and starting character '='                                                                                                                                                                                                     
    str=$(sinfo -o=%C | tail -1 | cut -c2-)

    # replace '/' with tabs                                                                                                                                                                                                                       
    echo -e "$(date +"%H:%M:%S")\t${str////$'\t'}" >> $CPU_FILE

    sleep $SLEEP_SECS

done



