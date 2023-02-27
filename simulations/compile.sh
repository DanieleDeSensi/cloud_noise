#!/bin/bash

GREEN=$(tput setaf 2)
RED=$(tput setaf 1)
NC=$(tput sgr0)

for tool in LogGOPSim schedgen
do
    rm ${tool}/${tool}
    pushd ${tool}
        make
        if [ ! -f "${tool}" ]; then
            echo "${RED}[Error] ${tool} compilation failed, please check error messages above.${NC}"
            exit 1
        fi
    popd
done

echo "${GREEN}Everything compiled successfully.${NC}"