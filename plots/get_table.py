#!/usr/bin/env python3
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np
import sys
import matplotlib.ticker as ticker
import os.path
import csv
import argparse
from matplotlib.lines import Line2D
from collections import OrderedDict
from mpl_toolkits.axes_grid1.inset_locator import mark_inset, inset_axes
from datetime import datetime
from pytz import timezone
import time
providers = ["AWS", "Azure", "GCP", "Oracle", "Alps", "Daint", "DEEP-EST"]
instances = ["Normal", "HPC", "HPC (Metal)", "HPC (200 Gb/s)"]
placements = ["Same Rack", "Different Racks"]
times = ["Night", "Day"]

# Optimal stuff
instance_type_t = {}
instance_type_t["GCP"] = "HPC"
instance_type_t["AWS"] = "HPC (Metal)"
instance_type_t["Azure"] = "HPC"
instance_type_t["Daint"] = "HPC (Metal)"
instance_type_t["Alps"] = "HPC (Metal)"
instance_type_t["DEEP-EST"] = "HPC (Metal)"

placement_t = {}
placement_t["GCP"] = "Same Rack"
placement_t["AWS"] = "Same Rack"
placement_t["Azure"] = "Same Rack"
placement_t["Daint"] = "Same Rack"
placement_t["Alps"] = "Same Rack"
placement_t["DEEP-EST"] = "Same Rack"

time_t = {}
time_t["GCP"] = "Day"
time_t["AWS"] = "Day"
time_t["Azure"] = "Day"
time_t["Daint"] = "Day"
time_t["Alps"] = "Day"
time_t["DEEP-EST"] = "Day"


metric_human = {}
metric_human["unidirectional_lat"] = "RTT/2 (us)"
metric_human["unidirectional_bw"] = "Bandwidth (Gb/s)"
metric_human["bidirectional_lat"] = "RTT/2 (us)"
metric_human["bidirectional_bw"] = "Bandwidth (Gb/s)"
metric_human["noise_lat"] = "RTT/2 (us)"
metric_human["noise_bw"] = "Bandwidth (Gb/s)"

paths = {}

def fname(name):
    if name == "AWS":
        return "aws"
    elif name == "Azure":
        return "azure"
    elif name == "GCP":
        return "gcp"
    elif name == "Daint":
        return "daint"
    elif name == "Alps":
        return "alps"
    elif name == "DEEP-EST":
        return "deep-est"
    elif name == "HPC (Metal)":
        return "hpc_metal"
    elif name == "Normal":
        return "normal"
    elif name == "HPC":
        return "hpc"
    elif name =="HPC (200 Gb/s)":
        return "hpc200"
    elif name == "Same Rack":
        return "same_rack"
    elif name == "Different Racks":
        return "different_racks"
    elif name == "Day":
        return "day"
    elif name == "Night":
        return "night"
    elif name == "any":
        return "any"
    else:
        sys.exit("Unknown fname")

def filter_provider(df, provider):
    r = df[df["Provider"].str.startswith(provider) & df["Provider"].str.endswith(provider)]
    if r is not None:
        r.reset_index(inplace=True, drop=True)
    return r

def filter_instance(df, instance):
    r = df[df["Instance"].str.startswith(instance) & df["Instance"].str.endswith(instance)]
    if r is not None:
        r.reset_index(inplace=True, drop=True)
    return r

def filter_placement(df, placement):
    r = df[df["Placement"].str.startswith(placement) & df["Placement"].str.endswith(placement)]
    if r is not None:
        r.reset_index(inplace=True, drop=True)
    return r

def filter_time(df, time):
    r = df[df["Time"].str.startswith(time) & df["Time"].str.endswith(time)]
    if r is not None:
        r.reset_index(inplace=True, drop=True)
    return r

def hr_size(size):
    if size < 1024:
        return str(int(size)) + "B"
    elif size < 1024*1024:
        return str(int(size / 1024)) + "KiB"
    elif size < 1024*1024*1024:
        return str(int(size / (1024*1024))) + "MiB"
    else:
        sys.exit("Too large size: " + str(size))

def sleep_time(time):
    suffix = ""
    if time % 10:
        suffix = " Post"
        time -= 1
    if time == 900000000 or time == 700000000 or time == 500000000 or time == 300000000 or time == 100000000:
        suffix = " Skip"
    return str(int(time / 1000000)) + "ms" + suffix


def get_data(provider, instance, placement, timestr, data_type):
    warmup_iterations = 20
    iterations_per_run = 1000
    filename = ""
    if data_type == "noise_lat":
        filename = "ng_netnoise_mpi_lat.out"
    elif data_type == "noise_bw":
        filename = "ng_netnoise_mpi_bw.out"
    elif "unidirectional_lat" in data_type or "unidirectional_bw" in data_type:
        if "x" in data_type:
            filename = "ng_one_one_mpi_stripe" + data_type.split("x")[1] + ".out"
        elif "y" in data_type:
            filename = "ng_one_one_mpi_conc" + data_type.split("y")[1] + ".out"
        elif "mpi" in data_type:
            filename = "ng_one_one_mpi_stripe1.out"       
        elif "tcp" in data_type or "udp" in data_type or "ib" in data_type:
            filename = "ng_one_one_" + data_type.split("_")[2] + ".out"       
    elif "bidirectional_lat" in data_type or "bidirectional_bw" in data_type:
        if "x" in data_type:
            filename = "ng_one_one_mpi_bidirect_mpi_stripe" + data_type.split("x")[1] + ".out"
        else:
            filename = "ng_one_one_mpi_bidirect_mpi_conc" + data_type.split("y")[1] + ".out"
            #if (provider, instance, placement, timestr) in paths:
            #    print(paths[(provider, instance, placement, timestr)] + "/" + filename)
    elif data_type == "os_noise":
        filename = "ng_osnoise.out"
    else:
        sys.exit("Unknown data type " + data_type)
    if (provider, instance, placement, timestr) not in paths:
        return None
    full_filename = paths[(provider, instance, placement, timestr)] + "/" + filename
    if not os.path.exists(full_filename):
        return None
    col_names = ["Message Size", "RTT/2 (us)"]
    if data_type == "os_noise":
        col_names = ["Time (s)", "Detour (us)"]
    df = pd.read_csv(full_filename, comment="#", sep="\t", names=col_names) 
    if timestr == "Long" and data_type != "os_noise":
        #drop_perc = 0.99
        #drop_indices = np.random.choice(df.index, int(len(df)*drop_perc), replace=False)
        #df = df.drop(drop_indices)
        bin_size = (len(df) / 1440) # One sample per minute
        df = df.groupby(df.index // bin_size).mean()
        # Rotate data so that it starts at 00:00
        start_time_h = int(paths[(provider, instance, placement, timestr)].split("/")[-1].split("_")[3])
        start_time_m = int(paths[(provider, instance, placement, timestr)].split("/")[-1].split("_")[4])
        minutes_after_midnight_cet = start_time_h*60 + start_time_m
        minutes_after_midnight_et = minutes_after_midnight_cet - 5*60
        minutes_after_midnight = 0
        if provider == "Daint" or provider == "Alps" or provider == "DEEP-EST":
            minutes_after_midnight = minutes_after_midnight_cet
        else:
            minutes_after_midnight = minutes_after_midnight_et
        df.reset_index(inplace=True)
        df = df.reindex(np.roll(df.index, -minutes_after_midnight))

    df["Provider"] = provider
    df["Instance"] = instance
    df["Placement"] = placement
    df["Time"] = timestr    
    if data_type != "os_noise":
        df["RTT/2 (us)"] = df["RTT/2 (us)"].astype(float)
        df["Bandwidth (Gb/s)"] = ((df["Message Size"]*8) / (df["RTT/2 (us)"]*1000.0)).astype(float)
        df["Message Size"] = df.apply(lambda x: hr_size(x["Message Size"]), axis=1)
        df["Time (us)"] = df["RTT/2 (us)"].cumsum()
        df = df[df.index % iterations_per_run > warmup_iterations] # Exclude warmup iterations
    else:
        df["Detour (us)"] = df["Detour (us)"].astype(float) / 1000.0 # It is actually in ns, so we need to convert to us
        df["Time (s)"] = df["Time (s)"].astype(float) / 1000000000.0 # It is actually in ns, so we need to convert to s
        # Cut
        df = df[df["Time (s)"] < 5]
    df["Sample"] = range(len(df))
    return df

def load_all(data_type):
    df = pd.DataFrame()
    for provider in providers:
        for instance in instances:
            for placement in placements:
                for time in times:
                    if (provider, instance, placement, time) not in paths:                        
                        continue
                    df_tmp = get_data(provider, instance, placement, time, data_type)
                    df = pd.concat([df, df_tmp])
    df.reset_index(inplace=True, drop=True)             
    return df

#  providers = ["AWS", "Azure", "GCP", "Oracle", "Alps", "Daint", "DEEP-EST"]

def get_instances_from_provider(provider):
    if provider == "AWS":
        instances = ["Normal", "HPC (Metal)"]
    elif provider == "Azure": 
        instances = ["Normal", "HPC", "HPC (200 Gb/s)"]        
    elif provider == "GCP":
        instances = ["Normal", "HPC"]                    
    elif provider == "Oracle":
        instances = ["Normal", "HPC (Metal)"]
    elif provider == "Alps":
        instances = ["HPC (Metal)"]
    elif provider == "Daint":
        instances = ["HPC (Metal)"]
    elif provider == "DEEP-EST":
        instances = ["HPC (Metal)"]
    else:
        instances = ["NULL"]
    return instances

def get_table(metric):
    for placement in ["Same Rack", "Different Racks"]:
        for row in ["Min Latency", "Mean Latency", "Max Bandwidth", "Mean Bandwidth"]:
            print(row, end=" & ")
            for provider in providers:
                if "Latency" in row:
                    if provider == "GCP":
                        message_size = "16B" # Lower latency for 16B
                    else:
                        message_size = "1B"
                else:
                    message_size = "16MiB"
                suffix = "x1"
                if (provider == "GCP" or provider == "AWS") and not "Latency" in row:
                    suffix = "y16"
                    
                instances = get_instances_from_provider(provider)
                for instance in instances:
                    dfc = load_all(metric + suffix)           
                    dfc = filter_instance(dfc, instance)            
                    dfc = filter_placement(dfc, placement)            
                    dfc = filter_time(dfc, "Day")
                    dfc = filter_provider(dfc, provider)
                    dfc = dfc[dfc['Message Size'] == message_size]
                    #print(dfc)
                    if "Mean Latency" in row:
                        print("{:.2f}".format(np.mean(dfc["RTT/2 (us)"])), end=" & ")
                    elif "Min Latency" in row:
                        print("{:.2f}".format(np.min(dfc["RTT/2 (us)"])), end=" & ")
                    elif "Mean Bandwidth" in row:
                        print("{:.2f}".format(np.mean(dfc["Bandwidth (Gb/s)"])), end=" & ")
                    elif "Max Bandwidth" in row:
                        print("{:.2f}".format(np.max(dfc["Bandwidth (Gb/s)"])), end=" & ")
                
            print("")


def main():     
    with open("../data/description.csv", mode='r') as infile:
        reader = csv.reader(infile)    
        global paths
        paths = {(rows[0],rows[1],rows[2],rows[3]):"../data/" + rows[4] for rows in reader}    
    get_table("unidirectional_bw") # OK

if __name__ == "__main__":
    main()

