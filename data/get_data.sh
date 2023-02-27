#!/bin/bash
GREEN=$(tput setaf 2)
RED=$(tput setaf 1)
NC=$(tput sgr0)

echo "Downloading data ..."
git clone https://github.com/DanieleDeSensi/cloud_noise_data.git
echo " ${GREEN}[Done]${NC}"

mv cloud_noise_data/* .
rm -rf cloud_noise_data
./compress.sh -d
rm simulations/* # Remove simulation data, we are going to collect it from scratch
echo " ${GREEN}[Done]${NC}"
