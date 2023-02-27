#!/usr/bin/env python3
from enum import unique
from re import T
import subprocess
import argparse
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np
import csv
import os
import sys
import time
import uuid
import random
from loggp_params import get_loggp_params

unique_id = 0
providers_all = ["AWS", "Azure", "GCP", "Daint", "Alps", "DEEP-EST", "Oracle"]

#collectives_all = ["binarytreebcast", "binomialtreebcast", "nwaydissemination", "pipelinedring", "linear_alltoall", "nwaydissemination_nocompute"]
#collectives_all = ["binomialtreebcast", "nwaydissemination", "pipelinedring", "linear_alltoall"]
collectives_all = ["nwaydissemination_nocompute", "pipelinedring"]
paths = {}

simulation_data_folder = "../data/simulations/"

gemm_sizes = [16, 128, 1024, 2048]

def instance_to_fname(instance):
    if instance == "HPC (200 Gb/s)":
        return "hpc_200"
    elif instance == "HPC":
        return "hpc"
    elif instance == "HPC (Metal)":
        return "hpc_metal"
    elif instance == "Normal":
        return "normal"
    else:
        sys.exit("Unkown instance " + instance)

def fix_boxplot(g):
    for i in range(3):
        box_col = sns.color_palette()[i]
        mybox = g.artists[i]
        mybox.set_edgecolor(box_col)
        mybox.set_fccecolor(None) #or white, if that's what you want

        # If you want the whiskers etc to match, each box has 6 associated Line2D objects (to make the whiskers, fliers, etc.)
        # Loop over them here, and use the same colour as above
        for j in range(i*6,i*6+6):
            line = g.lines[j]
            line.set_color(box_col)
            line.set_mfc(box_col)
            line.set_mec(box_col)


nodes_total = [4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 65536]
msgsize_total = [16]

def run_cmd(cmd):
    output = subprocess.check_output(cmd, shell=True)
    return output.decode().split('\n')
    
def convert_noise(args, scenario, lat_or_bw, L, G, filename, normalize):
    warmup_iterations = 20
    iterations_per_run = 1000
    # Convert from us to ps
    df = pd.read_csv(scenario + "/ng_netnoise_mpi_" + lat_or_bw + ".out", sep="\t", comment="#", names=["size", "rtt"])    
    df = df[(df.index % iterations_per_run) > warmup_iterations] # Exclude warmup iterations
    df = df.dropna()
    df["L"] = (df["rtt"] * 1000000).astype(int) # Convert us to ps
    df["G"] = ((df["L"]) / df["size"]).astype(int) 
    df = df.drop(columns=["size", "rtt"])    
    if lat_or_bw == "lat":
        df = df.drop(columns=["G"])
        if normalize:
            df["L"] = df["L"] * (L / float(df["L"].median())) # Scale up
            #df["L"] += (L - float(df["L"].mean())) # Scale up
        df["L"] = df["L"].astype(int)
    else:
        df = df.drop(columns=["L"])
        if normalize:
            df["G"] = df["G"] * (G / float(df["G"].median())) # Scale up
        df["G"] = df["G"].astype(int)
    df.to_csv(filename, index=False, header=False)

def simulate(collective, nodes, msgsize, scenario, provider, args, noise, instance, placement):
    print("[Collective: " + str(collective) + "][Nodes: " + str(nodes) + "][Msg size: " + str(msgsize) + "][Provider: " + str(provider) + "][Noise: " + str(noise) + "][Instance: " + str(instance) + "][Placement: " + str(placement) + "]")

    normalize = True
    suffix = "x1"
    #if (provider == "AWS" or provider == "GCP"):
    #    suffix = "y16"
    #    normalize = True
    #elif provider == "Azure" and instance == "Normal":
    #    suffix = "y2"
    #    normalize = True

    os_noise_flag = ""
    L_flag = ""
    G_flag = ""

    if noise == "os" or noise == "os+net":
        os_noise_file = "./loggopsfiles/os_noise_" + provider + "_" + instance_to_fname(instance) + ".out"
        # Generate OS noise file if it does not exist
        if not os.path.exists(os_noise_file):
            # Convert from ns to ps
            cmd = "cat " + scenario + "/ng_osnoise.out | grep -v '#' | awk '{print int(1000*$1)\"\t\"int(1000*$2)}' > " + os_noise_file # ns to ps
            run_cmd(cmd)
        os_noise_flag = "--noise-trace=" + os_noise_file

    placements = ["Same Rack"]
    if placement == "Different Racks":
        placements += ["Different Racks"]

    for placement in placements:
        # Get params and convert to ps
        (Li, oi, gi, Gi, Si) = get_loggp_params(provider, instance, suffix, placement)
        o = int(oi*1000000) # us to ps
        g = int(gi*1000000) # us to ps
        L = int(Li*1000000) # us to ps
        G = int(Gi*1000000) # us to ps
        S = Si
        O = 0                 
        
        far = ""
        if placement == "Different Racks":
            far = "_far"

        if noise == "net" or noise == "os+net":
            lat_noise_file = "./loggopsfiles/lat_noise_" + provider + "_" + instance_to_fname(instance) + "_" + placement.replace(" ", "_").lower() + ".out"
            # Generate lat noise file if it does not exist
            if not os.path.exists(lat_noise_file):
                convert_noise(args, scenario, "lat", L, G, lat_noise_file, normalize)
            L_flag += " --LogGOPS_Lfile" + far + "=" + lat_noise_file
        else:
            L_flag += " --LogGOPS_L" + far + "=" + str(L)

        if noise == "net" or noise == "os+net":
            bw_noise_file = "./loggopsfiles/bw_noise_" + provider + "_" + instance_to_fname(instance) + "_" + placement.replace(" ", "_").lower() + ".out"
            # Generate bw noise file if it does not exist
            if not os.path.exists(bw_noise_file):
                convert_noise(args, scenario, "bw", L, G, bw_noise_file, normalize)
            G_flag += " --LogGOPS_Gfile" + far + "=" + bw_noise_file
        else:
            G_flag += " --LogGOPS_G" + far + "=" + str(G)

    # Generate schedule
    segmentsize = ""
    if collective == "pipelinedring":
        if int(msgsize) < int(nodes):
            return -1
        segmentsize = "--segmentsize " + str(int(int(msgsize)/int(nodes)))
        

    compute = True
    if collective == "nwaydissemination_nocompute":
        collective = "nwaydissemination"
        compute = False
    #elif collective == "MILC":
    #    compute = False

    # Generate schedgen if it does not exist
    schedgen_file = "./loggopsfiles/schedgen_" + collective + "_" + str(nodes) + "_" + str(msgsize) + ".out"
    schedgen_bin_file = "./loggopsfiles/schedgen_" + collective + "_" + str(nodes) + "_" + str(msgsize) + ".out.bin"
    if not os.path.exists(schedgen_bin_file):   
        sched_pattern = ""
        traces = ""
        if collective != "MILC":     
            sched_pattern = collective
        else:
            sched_pattern = "trace"
            traces = "--traces ../data/MILC/input_64_nodes_tiny/input-00.txt --traces-extr " + str(int(int(nodes)/64))
        cmd = "./schedgen/schedgen -s " + str(nodes) + " -p " + sched_pattern + " -d " + str(msgsize) + " " + segmentsize + " -o " + schedgen_file + ".tmp" + " " + traces
        #print(cmd)
        run_cmd(cmd)
        if compute: 
            # schedgen assumes calc times are in ns, but we are using ps in LogGOPSim, so we need to multiply calc time by 1000
            run_cmd("cat " + schedgen_file + ".tmp | awk '{if($2 == \"calc\"){printf \"%s %s %17.0f\\n\", $1, $2, $3*1000}else{print}}' | tr -s ' ' > " + schedgen_file)
        else:
            # We don't simulate compute
            run_cmd("cat " + schedgen_file + ".tmp | awk '{if($2 == \"calc\"){printf \"%s %s 0\\n\", $1, $2}else{print}}' > " + schedgen_file)
        #os.remove(schedgen_file + ".tmp")
        run_cmd("./LogGOPSim/txt2bin -i " + schedgen_file + " -o " + schedgen_bin_file)
        #os.remove(schedgen_file)

    nodes_per_switch = " --nodes_per_switch "
    if collective == "pingpong":
        nodes_per_switch += "1"
    else:
        if provider == "Daint":
            nodes_per_switch += "16"
        elif provider == "Alps":
            nodes_per_switch += "16"
        elif provider == "DEEP-EST":
            nodes_per_switch += "32"
        elif provider == "Oracle":
            nodes_per_switch += "8"
        elif provider == "AWS":
            nodes_per_switch += "32"
        elif provider == "GCP":
            nodes_per_switch += "22"
        else:
            nodes_per_switch += "1"

    if not args.generate_only:
        cmd = "./LogGOPSim/LogGOPSim -f " + schedgen_bin_file + " " + L_flag + " " + G_flag + " "\
            "-o " + str(o) + " -g " + str(g) + " -O 0 -S " + str(S) + " " + os_noise_flag + " --batchmode " + \
            " --seed " + str(random.randint(0, 2**32 - 1)) + nodes_per_switch
        print(cmd)
        output = run_cmd(cmd)
        #print(output)
        for line in output:
            if "Maximum finishing time" in line:
                #print(int(line.split(" ")[6])/1000000.0)
                return int(line.split(" ")[6])/1000000.0 # Time from picoseconds to microseconds

def main():
    parser = argparse.ArgumentParser(description='Simulates large scale collectives.')
    parser.add_argument('--collective', help='Collective to run [].', default="all")
    parser.add_argument('--provider', help='Provider to simulate [].', default="all")
    parser.add_argument('--msgsize', help='Size of the data used in the collective.')
    parser.add_argument('--nodes', help='Number of nodes')
    parser.add_argument('--noises', help='Type of noises to simulate', default="none,os,net,os+net")
    parser.add_argument('--placements', help='Type of placements to simulate', default="sr")
    parser.add_argument('--num_tests', help='Number of tests to run.', default=1000)
    parser.add_argument('--hpc_only', help='Simulates only HPC instances.', action='store_true')
    parser.add_argument('--generate_only', help='Only generates loggopssim input files without running the simulations.', action="store_true")    
    args = parser.parse_args()
    print(args.provider)
    
    global unique_id
    unique_id = str(uuid.uuid4())
    random.seed(uuid.uuid1().int>>64)
    if not os.path.exists("./loggopsfiles/"):
        os.makedirs("./loggopsfiles/")

    # Load paths
    with open("../data/description.csv", mode='r') as infile:
        reader = csv.reader(infile)    
        global paths
        paths = {(rows[0],rows[1],rows[2],rows[3]):"../data/" + rows[4] for rows in reader}

    if args.generate_only:
        num_tests = 1
        noises = ["none"]
    else:
        num_tests = int(args.num_tests)
        noises = args.noises.split(",")
    df = pd.DataFrame()
    collectives = []
    global msgsize_total    
    for gemm_size in gemm_sizes:
        msgsize_total += [gemm_size*gemm_size*8] # Double values
    global nodes_total
    if args.nodes:
        nn_strings = args.nodes.split(",")
        nodes_total = []
        for nn in nn_strings:
            nodes_total += [int(nn)]
    if args.collective == "all":
        collectives = collectives_all
    else:
        collectives = args.collective.split(",")
    if args.provider == "all":
        providers = providers_all
    else:
        providers = args.provider.split(",")
    if args.msgsize:
        mm_strings = args.msgsize.split(",")
        msgsizes = []
        for mm in mm_strings:
            msgsizes += [int(mm)]
    else:
        msgsizes = msgsize_total

    placements = []
    if "sr" in args.placements:
        placements += ["Same Rack"]
    if "dr" in args.placements:
        placements += ["Different Racks"]
    expected_runs  = len(collectives)*len(providers)*len(nodes_total)*len(msgsizes)*len(placements)*num_tests*(len(noises)-1) # Noise
    expected_runs += len(collectives)*len(providers)*len(nodes_total)*len(msgsizes)*len(placements) # No noise
    current_run_progress = 1
    
    #print(str(len(collectives)) + " " + str(len(providers)) + " " + str(len(nodes_total)) + " " + str(len(msgsizes)))

    df = pd.DataFrame()
    for collective in collectives:
        for provider in providers:    
            if provider == "Daint":
                instances = ["HPC (Metal)"]
            elif provider == "Alps":
                instances = ["HPC (Metal)"]
            elif provider == "DEEP-EST":
                instances = ["HPC (Metal)"]
            elif provider == "Oracle":
                if args.hpc_only:
                    instances = ["HPC (Metal)"]
                else:
                    instances = ["Normal", "HPC (Metal)"]
            elif provider == "AWS":
                if args.hpc_only:
                    instances = ["HPC (Metal)"]
                else:                    
                    instances = ["Normal", "HPC (Metal)"]
            elif provider == "GCP":
                if args.hpc_only:
                    instances = ["HPC"]
                else:
                    instances = ["Normal", "HPC"]                    
            else: # Azure
                if args.hpc_only:
                    instances = ["HPC", "HPC (200 Gb/s)"]
                else:
                    instances = ["Normal", "HPC", "HPC (200 Gb/s)"]
            for instance in instances:
                for nodes in nodes_total:
                    for placement in placements:
                        k = (provider, instance, placement, "Day")                        
                        print(k)
                        if k in paths:            
                            scenario_lb = paths[k]
                        else:
                            scenario_lb = None                        
                        for msgsize in msgsizes:                            
                            # Simulated time
                            for test in range(num_tests):       
                                for noise in noises:             
                                    if noise == "none" and test > 0: # With no noise is deterministic so we just need one sample
                                        continue 
                                    if scenario_lb is not None:                                              
                                        print("[Progress: " + str(current_run_progress) + "/" + str(expected_runs) + "]", end="")                              
                                        time_us = simulate(collective, nodes, msgsize, scenario_lb, provider, args, noise, instance, placement)
                                        tmp = pd.DataFrame([[noise, "Simulated", collective, provider, instance, placement, nodes, scenario_lb, time_us, msgsize]], \
                                                        columns=["Noise", "Type", "Collective", "Provider", "Instance Type", "Placement", "Nodes", "Scenario", "Time (us)", "Message Size"])
                                        df = pd.concat([df, tmp])
                                        current_run_progress += 1
                            # Update the file
                            out_data_name = simulation_data_folder + unique_id + ".csv"
                            if os.path.exists(out_data_name):
                                os.remove(out_data_name)
                            df.reset_index(inplace=True, drop=True)    
                            df.to_csv(out_data_name)


if __name__ == "__main__":
    main()
