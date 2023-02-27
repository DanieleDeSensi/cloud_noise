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
import matplotlib.ticker as ticker
sys.path.append('../simulations/')
from loggp_params import get_loggp_params


# Costs on 2nd May 2022
costs = {}
# On-demand
costs[("AWS", "Normal", "On-Demand")] = 3.06
costs[("AWS", "HPC", "On-Demand")] = 3.88
costs[("AWS", "HPC (Metal)", "On-Demand")] = 3.88 
costs[("Azure", "Normal", "On-Demand")] = 3.045 
costs[("Azure", "HPC", "On-Demand")] = 3.168
costs[("Azure", "HPC (200 Gb/s)", "On-Demand")] = 3.6
costs[("GCP", "Normal", "On-Demand")] = 3.1321 
costs[("GCP", "HPC", "On-Demand")] = 4.03
costs[("Daint", "HPC (Metal)", "On-Demand")] = 1.73
costs[("Alps", "HPC (Metal)", "On-Demand")] = -1 # TODO
costs[("DEEP-EST", "HPC (Metal)", "On-Demand")] = -1 # TODO
costs[("Oracle", "Normal", "On-Demand")] = 1.188 
costs[("Oracle", "HPC (Metal)", "On-Demand")] = 2.712

# 3-years upfront
costs[("AWS", "Normal", "Upfront")] = 1.34 # https://aws.amazon.com/it/ec2/pricing/reserved-instances/pricing/ -- 3 years, "Payment in advance"
costs[("AWS", "HPC", "Upfront")] = 1.475 # Same
costs[("AWS", "HPC (Metal)", "Upfront")] = 1.475 # Same
costs[("Azure", "Normal", "Upfront")] = 1.116 # https://azure.microsoft.com/en-us/pricing/calculator/?service=cost-management -- 3 years, reserved (no difference between monthly and upfront)
costs[("Azure", "HPC", "Upfront")] = 2.218 # Same (Strangely there is a 30% discount on HPC 100Gb/s, but a 50% discount on 200Gb/s -- that's why it costs more than 200Gb/s instances)
costs[("Azure", "HPC (200 Gb/s)", "Upfront")] = 1.8 # Same
costs[("GCP", "Normal", "Upfront")] = 1.25 
costs[("GCP", "HPC", "Upfront")] =  2.1479 
costs[("Daint", "HPC (Metal)", "Upfront")] = 1.02
costs[("Alps", "HPC (Metal)", "Upfront")] = -1 # TODO
costs[("DEEP-EST", "HPC (Metal)", "Upfront")] = -1 # TODO
costs[("Oracle", "Normal", "Upfront")] = -1 # TODO
costs[("Oracle", "HPC (Metal)", "Upfront")] = -1 # TODO

nodes_total = [4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 65536]
msgsize_total = [16]
paths = {}
simulation_data_folder = "../data/simulations/"
sns.set_style("whitegrid")

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

def load_gemm_times(size, provider, instance):    
    k = (provider, instance, "Compute", "")
    if k in paths:
        path = paths[k]        
        df = pd.read_csv(path + str(size) + ".dat", sep="\t")
        time_us = np.mean(df["TIME(s)"]*1000000) # Seconds to microseconds
        GFLOPs = np.mean(df["GFLOPs/s"]*df["TIME(s)"])
        return (time_us, GFLOPs)
    else:
        sys.exit("Unknown file for " + instance + " " + provider + " " + str(k))

def get_nodes_validation(provider, instance):
    if provider == "Daint" or provider == "Alps":
        nodes_validation = [4, 8, 16, 32, 64, 128]
    elif provider == "DEEP-EST" or provider == "AWS":
        nodes_validation = [4, 8, 16, 32]
    elif provider == "Azure" or provider == "GCP":
        if instance == "HPC":
            nodes_validation = [4, 8, 16]
        else:
            nodes_validation = [4, 8, 16, 32]
    elif provider == "Oracle":
        nodes_validation = [4, 8, 16]
    return nodes_validation

def plot_validation(df, provider, instance):
    msgsize = 16777216
    
    nodes_validation = get_nodes_validation(provider, instance)

    collectives = ["nwaydissemination_nocompute", "pipelinedring", \
                   "nwaydissemination_nocompute_test", "pipelinedring_test", \
                   "nwaydissemination_nocompute_nbsend", "pipelinedring_nbsend"]
    df2 = df.copy()
    df2["Collective"] += "_test"
    df = pd.concat([df, df2])
    df2 = df.copy()
    df2["Collective"] += "_nbsend"
    df = pd.concat([df, df2])
    # Real time
    df["Type"] += " " + df["Placement"]
    #df = df[df["Placement"] == "Same Rack"]
    #df = df[df["Time (us)"] < 1000000]
    
    #if provider == "Alps":
    #    pd.set_option('display.max_columns', None)
    #    ##(df["Provider"] == provider) & (df["Instance Type"] == instance) & (df["Collective"] == collective) & \
    #    ## (df["Message Size"] == msgsize) & (df['Nodes'].isin(nodes_validation)) & (df['Noise'] == "os+net")
    #    print(df[(df["Provider"] == provider)].head(1))
    
    
    for nodes in nodes_validation:
        for collective in collectives:
            for placement in ["Same Rack", "Different Racks"]:
                if "nwaydissemination" in collective:
                    msgsize = 16
                else:
                    msgsize = 16777216
                k = (provider, instance, "Collectives", "")
                if k in paths:
                    vpath = paths[k]
                filename = vpath + "/" + collective + "_" + str(nodes) + "_" + str(msgsize) + ".csv"
                print(filename)
                if os.path.exists(filename):
                    data_real = pd.read_csv(filename, sep=" ")                    
                    if len(data_real) == 0:
                        continue
                    data_real = data_real.loc[:, ~data_real.columns.str.contains('^Unnamed')]
                    colnames_ranks = []
                    for r in range(nodes):
                        colnames_ranks += ["Rank" + str(r) + "Time(us)"]
                    data_real["Time (us)"] = data_real[colnames_ranks].max(axis=1)
                    #data_real = data_real.tail(data_real.shape[0]-20) # Drop first 20 samples (warmup)
                    data_real["Type"] = "Measured"
                    data_real["Collective"] = collective
                    data_real["Provider"] = provider
                    data_real["Instance Type"] = instance
                    data_real["Nodes"] = nodes
                    data_real["Scenario"] = ""
                    data_real["Message Size"] = msgsize
                    data_real["Noise"] = "os+net"
                    df = pd.concat([df, data_real])
    df.reset_index(drop=True, inplace=True)
    df["Time (ms)"] = df["Time (us)"] / 1000.0
    rows = 3
    cols = 2
    fig, axes = plt.subplots(rows, cols, figsize=(10,10), sharex=False, sharey=False)
    i = 0

    for collective in collectives:
        if "nwaydissemination" in collective:
            msgsize = 16
        else:
            msgsize = 16777216
        ax = axes[int(i / cols)][i % cols]
        #ax = axes[i]
        #print(df[(df["Instance Type"] == instance) & (df["Collective"] == collective)])
        #print(df[(df["Instance Type"] == instance) & (df["Collective"] == collective)][["Rank0Time(us)", "Rank1Time(us)", "Rank3Time(us)", "Rank7Time(us)", "Rank15Time(us)"]])
        #print(df[(df["Instance Type"] == instance) & (df["Collective"] == collective)][["Rank0Time(us)", "Rank1Time(us)", "Rank2Time(us)", "Rank3Time(us)", "Time (us)"]])
        #print(df[(df["Instance Type"] == instance) & (df["Collective"] == collective)][["Time (us)"]].mean())
        ax = sns.lineplot(data=df[(df["Provider"] == provider) & (df["Instance Type"] == instance) & (df["Collective"] == collective) & \
                                  (df["Message Size"] == msgsize) & (df['Nodes'].isin(nodes_validation)) & (df['Noise'] == "os+net")], \
                            x="Nodes", y="Time (us)", hue="Type", style="Type", \
                            markers=True, dashes=True, ax=ax,  ci=95, estimator=np.mean)
        ax.set(ylim=(0,None))
        real_title = ""
        if collective == "binomialtreebcast":
            real_title = "Broadcast (Binomial Tree)"
        elif "nwaydissemination" in collective:
            real_title = "Dissemination"
        elif collective == "pipelinedring":
            real_title = "Ring"
        ax.set_title(real_title)
        #ticks = [2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32]
        #ax.set_xticks(ticks)
        #ax.set_xticklabels(ticks)
        #handles, labels = ax.get_legend_handles_labels()     
        #ax.get_legend().remove()
        i += 1
    #fig.legend(handles, labels, bbox_to_anchor=(.65, 1), ncol=4, title=None)
    plt.tight_layout()
    plt.subplots_adjust(top=0.75)
    fig.savefig("out/simulations/validation_" + provider + "_" + instance_to_fname(instance) + ".pdf", format='pdf', dpi=100)
    plt.clf()

def plot_validation_pingpong(orig, provider):
    #print(df[(df["Provider"] == provider) & (df["Instance Type"] == instance) & (df["Collective"] == "pingpong") & (df['Noise'] == "os+net") & (df["Message Size"] == 16777216)])
    if provider == "Azure":
        instance = "HPC (200 Gb/s)"
    elif provider == "GCP":
        instance = "HPC"
    else:
        instance = "HPC (Metal)"    
    
    rows = 1
    cols = 2
    fig, axes = plt.subplots(rows, cols, figsize=(10, 2.5), sharex=False, sharey=False)
    idx = 0
    for placement in ["Same Rack", "Different Racks"]:
        df = orig.copy()
        df["Time (us)"] /= 2.0 # RTT
        loggp_us = []
        loggp_bw = []
        msg_sizes = []
        for i in range(0, 25):
            msg_size = 2**i
            msg_sizes += [msg_size]
            suffix = "x1"
            #if (provider == "AWS" or provider == "GCP") and int(msg_size) > 65536:
            #    suffix = "y16"
            #elif provider == "Azure" and instance == "Normal" and int(msg_size) > 65536:
            #    suffix = "y2"
            (L, o, g, G, S) = get_loggp_params(provider, instance, suffix, placement)
            
            if msg_size <= S:   
                us = 2*o + L + (msg_size - 1)*G
            else:
                us = 2*o + 3*L + (msg_size - 1)*G
            loggp_us += [us]
            loggp_bw += [(msg_size*8) / (us*1000)]

        loggp = {}    
        loggp["Time (us)"] = loggp_us    
        loggp["Message Size"] = msg_sizes
        loggp["Bandwidth (Gb/s)"] = loggp_bw
        loggp["Type"] = "Model"
        loggp["Provider"] = provider
        loggp["Instance Type"] = instance
        loggp["Collective"] = "pingpong"
        loggp["Noise"] = "os+net"
        loggp["Placement"] = placement
        df = pd.concat([df, pd.DataFrame.from_dict(loggp)])
        #print(df)    

        k = (provider, instance, placement, "Day")
        if k in paths:
            vpath = paths[k]
        filename = vpath + "/ng_one_one_mpi_stripe1.out"
        print(filename)
        if os.path.exists(filename):
            data_real = pd.read_csv(filename, sep="\t", names=["Message Size", "Time (us)"], header=1)
            data_real["Type"] = "Real"
            data_real["Provider"] = provider
            data_real["Instance Type"] = instance
            data_real["Collective"] = "pingpong"
            data_real["Noise"] = "os+net"     
            data_real["Placement"] = placement   
            data_real = data_real.loc[:, ~data_real.columns.str.contains('^Unnamed')]
            df = pd.concat([df, data_real])
        df.reset_index(drop=True, inplace=True)
        df["Time (us)"] = df["Time (us)"].astype(float)
        df["Bandwidth (Gb/s)"] = ((df["Message Size"]*8) / (df["Time (us)"]*1000.0)).astype(float)
        df["Message Size"] = df["Message Size"].astype(str)
        df["Time (ms)"] = df["Time (us)"] / 1000.0    
        ax = axes[idx]
        ax = sns.lineplot(data=df[(df["Provider"] == provider) & (df["Instance Type"] == instance) & \
                                 (df["Collective"] == "pingpong") & (df['Noise'] == "os+net") & (df['Placement'] == placement)], \
                            x="Message Size", y="Bandwidth (Gb/s)", hue="Type", style="Type", \
                            markers=True, dashes=True, ax=ax,  ci=90, estimator=np.mean)
        ax.set(ylim=(0,None))
        ax.xaxis.set_major_locator(ticker.MultipleLocator(4))
        if placement == "Same Rack":
            handles, labels = ax.get_legend_handles_labels()     
        ax.get_legend().remove()
        if True:
            innerpars = [0.1, 0.5, 0.45, 0.45]
            axins = ax.inset_axes(innerpars)
            # Draw inner plot
            ax = sns.lineplot(data=df[(df["Provider"] == provider) & (df["Instance Type"] == instance) & \
                                      (df["Collective"] == "pingpong") & (df['Noise'] == "os+net") & (df['Placement'] == placement)], \
                            x="Message Size", y="Time (us)", hue="Type", style="Type", \
                            markers=True, dashes=True, ax=axins,  ci=90, estimator=np.min)

            axins.set(xlim=(0, 16))
            axins.xaxis.set_major_locator(ticker.MultipleLocator(4))
            axins.set(ylim=(0, 10))
            axins.tick_params(axis='x', labelsize=6)
            axins.tick_params(axis='y', labelsize=6)
            axins.set_xlabel("")
            axins.set_ylabel("Time (us)", fontsize=6)
            axins.get_legend().remove()
        idx += 1

    fig.legend(handles, labels, bbox_to_anchor=(.65, 1), ncol=4, title=None)
    plt.tight_layout()
    plt.subplots_adjust(top=0.75)
    fig.savefig("out/simulations/validation_pp_" + provider + ".pdf", format='pdf', dpi=100)
    plt.clf()

def collective_to_real(collective):
    if "nwaydissemination_nocompute" in collective:
        return "nwaydissemination_nocompute"
    elif "pipelinedring" in collective:
        return "pipelinedring"

def plot_validation_relative(sim):
    df2 = sim.copy()
    df2["Collective"] += "_test"
    sim = pd.concat([sim, df2])
    df2 = sim.copy()
    df2["Collective"] += "_nbsend"
    sim = pd.concat([sim, df2])
    tot = pd.DataFrame()    
    #sim = sim[sim["Time (us)"] < 10000]
    
    show_all = False
    collectives_all = ["nwaydissemination_nocompute", "pipelinedring", \
                   "nwaydissemination_nocompute_test", "pipelinedring_test", \
                   "nwaydissemination_nocompute_nbsend", "pipelinedring_nbsend"]
    if show_all:
        collectives_all_real = collectives_all
    else:
        collectives_all_real = ["nwaydissemination_nocompute", "pipelinedring"]
    
    # Real time
    for provider in ["Daint", "Alps", "DEEP-EST", "Azure", "AWS", "GCP", "Oracle"]:
        instances = []
        if provider == "Azure":
            instances = ["HPC", "HPC (200 Gb/s)"]
        elif provider == "GCP":
            instances = ["HPC"]
        else:
            instances = ["HPC (Metal)"]
        for instance in instances:
            collectives = {}
            if show_all:
                collectives["Alps"] = collectives_all
                collectives["Azure"] = collectives_all
                collectives["Daint"] = collectives_all
                collectives["DEEP-EST"] = collectives_all
                collectives["AWS"] = collectives_all
                collectives["Oracle"] = collectives_all
            else:
                collectives["Alps"] = ["nwaydissemination_nocompute_test", "pipelinedring"]
                if instance == "HPC":
                    collectives["Azure"] = ["nwaydissemination_nocompute_test", "pipelinedring_nbsend"]
                else:
                    collectives["Azure"] = ["nwaydissemination_nocompute_nbsend", "pipelinedring_nbsend"]
                collectives["Daint"] = ["nwaydissemination_nocompute", "pipelinedring_nbsend"]
                collectives["DEEP-EST"] = ["nwaydissemination_nocompute_test", "pipelinedring_nbsend"]
                collectives["AWS"] = ["nwaydissemination_nocompute_test", "pipelinedring_nbsend"]
                collectives["GCP"] = ["nwaydissemination_nocompute_test", "pipelinedring_nbsend"]
                collectives["Oracle"] = ["nwaydissemination_nocompute_test", "pipelinedring_nbsend"]
            nodes_validation = get_nodes_validation(provider, instance)
            for nodes in nodes_validation:
                for collective in collectives[provider]:
                    if "nwaydissemination" in collective:
                        msgsize = 16
                    else:
                        msgsize = 16777216

                    placement = "Different Racks"
                    #placement = ""
                    #if provider == "Azure":
                    #    placement = "Same Rack"
                    #else:
                    #    placement = "Different Racks"

                    k = (provider, instance, "Collectives", "")
                    if k in paths:
                        vpath = paths[k]
                    filename = vpath + "/" + collective + "_" + str(nodes) + "_" + str(msgsize) + ".csv"
                    if os.path.exists(filename):
                        print(filename)
                        data_real = pd.read_csv(filename, sep=" ")                    
                        if len(data_real) == 0:
                            continue
                        data_real = data_real.loc[:, ~data_real.columns.str.contains('^Unnamed')]
                        colnames_ranks = []
                        for r in range(nodes):
                            colnames_ranks += ["Rank" + str(r) + "Time(us)"]
                        data_real["Time (us)"] = data_real[colnames_ranks].max(axis=1)
                        data_real["Placement"] = placement
                        #data_real = data_real.tail(data_real.shape[0]-20) # Drop first 20 samples (warmup)
                        tmp = sim[(sim["Provider"] == provider) & (sim["Instance Type"] == instance) & (sim["Collective"] == collective) & \
                                (sim["Message Size"] == msgsize) & (sim['Nodes'] == nodes) & (sim['Noise'] == "os+net") & \
                                (sim['Placement'] == placement)]
                        
                        #abs_err = (tmp["Time (us)"].mean() - data_real["Time (us)"].mean())
                        #rel_err = (abs_err / data_real["Time (us)"].mean())*100.0                                                                        
                        abs_err = (tmp["Time (us)"].mean() - data_real["Time (us)"].mean())
                        rel_err = abs(abs_err / data_real["Time (us)"].mean())*100.0
                        if show_all:
                            ctf = collective
                        else:
                            ctf = collective_to_real(collective)
                        tmp2 = pd.DataFrame([[provider, instance, ctf, msgsize, nodes, rel_err, abs_err]], \
                                            columns = ["Provider", "Instance Type", "Collective", "Message Size", "Nodes", "Relative Error (%)", "Absolute Error"])  
                        tot = pd.concat([tot, tmp2])
                    
    tot.reset_index(drop=True, inplace=True)
    tot["Provider"] += " - " + tot["Instance Type"]
    if show_all:
        rows = 3
        cols = 2
        fig, axes = plt.subplots(rows, cols, figsize=(10,5), sharex=False, sharey=True)
    else:
        rows = 1
        cols = 2
        fig, axes = plt.subplots(rows, cols, figsize=(8,2.5), sharex=False, sharey=True)
    i = 0
    for collective in collectives_all_real:
        if "nwaydissemination" in collective:
            msgsize = 16
        else:
            msgsize = 16777216
        if show_all:
            ax = axes[int(i / cols)][i % cols]
        else:
            ax = axes[i]
        y = "Relative Error (%)"
        #y = "Absolute Error"
        #ax = sns.lineplot(data=tot[(tot["Collective"] == collective) & (tot["Message Size"] == msgsize)], \
        #                    x="Nodes", y=y, hue="Provider", style="Provider", \
        #                    markers=True, dashes=True, ax=ax, lw=2, markersize=10)
        #tot = tot[tot["Nodes"] >= 16]
        ax = sns.barplot(data=tot[(tot["Collective"] == collective) & (tot["Message Size"] == msgsize)], \
                         x="Nodes", y=y, hue="Provider", ax=ax)
        #ax.set(ylim=(0,50))
        real_title = ""
        if collective == "binomialtreebcast":
            real_title = "Broadcast (Binomial Tree)"
        elif "nwaydissemination" in collective:
            real_title = "Dissemination"
        elif "pipelinedring" in collective:
            real_title = "Ring"
        ax.set_title(real_title)
        #ticks = [4,8,16,32,64,128]
        #ax.set_xticks(ticks)
        #ax.set_xticklabels(ticks)
        handles, labels = ax.get_legend_handles_labels()     
        ax.get_legend().remove()
        #ax.set_xscale("log2")
        i += 1
    if show_all:
        fig.legend(handles, labels, bbox_to_anchor=(.65, 1), ncol=5, title=None)
        plt.tight_layout()
        plt.subplots_adjust(top=0.75)
    else:
        fig.legend(handles, labels, bbox_to_anchor=(.92, 1), ncol=3, title=None)
        plt.tight_layout()
        plt.subplots_adjust(top=0.7)
    fig.savefig("out/simulations/validation_relative.pdf", format='pdf', dpi=100)
    plt.clf()


def plot_validation_relative_short(sim, num_nodes):
    df2 = sim.copy()
    df2["Collective"] += "_test"
    sim = pd.concat([sim, df2])
    df2 = sim.copy()
    df2["Collective"] += "_nbsend"
    sim = pd.concat([sim, df2])
    tot = pd.DataFrame()    
    #sim = sim[sim["Time (us)"] < 10000]
    
    show_all = False
    collectives_all = ["nwaydissemination_nocompute", "pipelinedring", \
                   "nwaydissemination_nocompute_test", "pipelinedring_test", \
                   "nwaydissemination_nocompute_nbsend", "pipelinedring_nbsend"]
    if show_all:
        collectives_all_real = collectives_all
    else:
        collectives_all_real = ["nwaydissemination_nocompute", "pipelinedring"]
    
    # Real time
    for provider in ["Daint", "Alps", "DEEP-EST", "Azure", "AWS", "GCP", "Oracle"]:
        instances = []
        if provider == "Azure":
            instances = ["HPC", "HPC (200 Gb/s)"]
        elif provider == "GCP":
            instances = ["HPC"]
        else:
            instances = ["HPC (Metal)"]
        for instance in instances:
            collectives = {}
            if show_all:
                collectives["Alps"] = collectives_all
                collectives["Azure"] = collectives_all
                collectives["Daint"] = collectives_all
                collectives["DEEP-EST"] = collectives_all
                collectives["AWS"] = collectives_all
                collectives["Oracle"] = collectives_all
            else:
                collectives["Alps"] = ["nwaydissemination_nocompute_test", "pipelinedring"]
                if instance == "HPC":
                    collectives["Azure"] = ["nwaydissemination_nocompute_test", "pipelinedring_nbsend"]
                else:
                    collectives["Azure"] = ["nwaydissemination_nocompute_nbsend", "pipelinedring_nbsend"]
                collectives["Daint"] = ["nwaydissemination_nocompute", "pipelinedring_nbsend"]
                collectives["DEEP-EST"] = ["nwaydissemination_nocompute_test", "pipelinedring_nbsend"]
                collectives["AWS"] = ["nwaydissemination_nocompute_test", "pipelinedring_nbsend"]
                collectives["GCP"] = ["nwaydissemination_nocompute_test", "pipelinedring_nbsend"]
                collectives["Oracle"] = ["nwaydissemination_nocompute_test", "pipelinedring_nbsend"]
            nodes_validation = get_nodes_validation(provider, instance)
            for nodes in nodes_validation:
                for collective in collectives[provider]:
                    if "nwaydissemination" in collective:
                        msgsize = 16
                    else:
                        msgsize = 16777216

                    placement = "Different Racks"
                    #placement = ""
                    #if provider == "Azure":
                    #    placement = "Same Rack"
                    #else:
                    #    placement = "Different Racks"

                    k = (provider, instance, "Collectives", "")
                    if k in paths:
                        vpath = paths[k]
                    filename = vpath + "/" + collective + "_" + str(nodes) + "_" + str(msgsize) + ".csv"
                    if os.path.exists(filename):
                        print(filename)
                        data_real = pd.read_csv(filename, sep=" ")                    
                        if len(data_real) == 0:
                            continue
                        data_real = data_real.loc[:, ~data_real.columns.str.contains('^Unnamed')]
                        colnames_ranks = []
                        for r in range(nodes):
                            colnames_ranks += ["Rank" + str(r) + "Time(us)"]
                        data_real["Time (us)"] = data_real[colnames_ranks].max(axis=1)
                        data_real["Placement"] = placement
                        #data_real = data_real.tail(data_real.shape[0]-20) # Drop first 20 samples (warmup)
                        tmp = sim[(sim["Provider"] == provider) & (sim["Instance Type"] == instance) & (sim["Collective"] == collective) & \
                                (sim["Message Size"] == msgsize) & (sim['Nodes'] == nodes) & (sim['Noise'] == "os+net") & \
                                (sim['Placement'] == placement)]
                        
                        if provider == "Azure" and instance == "HPC (200 Gb/s)":
                            provider_t = provider + "\n(200 Gb/s)"
                        else:
                            provider_t = provider
                        abs_err = (tmp["Time (us)"].mean() - data_real["Time (us)"].mean())                        
                        rel_err = abs(abs_err / data_real["Time (us)"].mean())*100.0  
                        #abs_err = (tmp["Time (us)"] - data_real["Time (us)"].mean())                        
                        #rel_err = abs(abs_err / data_real["Time (us)"].mean())*100.0  
                        #print(abs_err)      
                        #print(rel_err)               
                        if show_all:
                            ctf = collective
                        else:
                            ctf = collective_to_real(collective)
                        #tmp2 = pd.DataFrame([[provider_t, instance, ctf, msgsize, nodes, rel_err, abs_err]], \
                        #                    columns = ["Provider", "Instance Type", "Collective", "Message Size", "Nodes", "Relative Error (%)", "Absolute Error"])  
                        tmp2 = pd.DataFrame()
                        tmp2["Time (us)"] = tmp["Time (us)"]
                        tmp2["Time Type"] = "Simulated"
                        tmp2["Relative Error (%)"] = rel_err
                        tmp2["Absolute Error"] = abs_err
                        tmp2["Provider"] = provider_t
                        tmp2["Instance Type"] = instance
                        tmp2["Collective"] = ctf
                        tmp2["Message Size"] = msgsize
                        tmp2["Nodes"] = nodes
                        tot = pd.concat([tot, tmp2])
                        tmp3 = pd.DataFrame()
                        tmp3["Time (us)"] = data_real["Time (us)"]
                        tmp3["Time Type"] = "Real"
                        tmp3["Relative Error (%)"] = rel_err
                        tmp3["Absolute Error"] = abs_err
                        tmp3["Provider"] = provider_t
                        tmp3["Instance Type"] = instance
                        tmp3["Collective"] = ctf
                        tmp3["Message Size"] = msgsize
                        tmp3["Nodes"] = nodes
                        tot = pd.concat([tot, tmp3])
                    
    tot.reset_index(drop=True, inplace=True)
    #tot["Provider"] += "\n" + tot["Instance Type"]
    if show_all:
        rows = 3
        cols = 2
        fig, axes = plt.subplots(rows, cols, figsize=(10,5), sharex=False, sharey=False)
    else:
        rows = 1
        cols = 2
        fig, axes = plt.subplots(rows, cols, figsize=(11,3), sharex=False, sharey=False)
    i = 0
    for collective in collectives_all_real:
        if "nwaydissemination" in collective:
            msgsize = 16
        else:
            msgsize = 16777216
        if show_all:
            ax = axes[int(i / cols)][i % cols]
        else:
            ax = axes[i]
        y = "Relative Error (%)"
        #y = "Absolute Error"
        #ax = sns.lineplot(data=tot[(tot["Collective"] == collective) & (tot["Message Size"] == msgsize)], \
        #                    x="Nodes", y=y, hue="Provider", style="Provider", \
        #                    markers=True, dashes=True, ax=ax, lw=2, markersize=10)
        tot = tot[tot["Nodes"] == num_nodes]
        #ax = sns.boxplot(data=tot[(tot["Collective"] == collective) & (tot["Message Size"] == msgsize)], x="Provider", y=y, ax=ax, showfliers=False)
        #ax = sns.boxplot(data=tot[(tot["Collective"] == collective) & (tot["Message Size"] == msgsize)], x="Provider", y="Time (us)", hue="Time Type", ax=ax, showfliers=False, notch=True)        
        ax = sns.barplot(data=tot[(tot["Collective"] == collective) & (tot["Message Size"] == msgsize)], x="Provider", y="Time (us)", hue="Time Type", ax=ax)
        # Define some hatches
        hatches = ["---", "///"]
        # Loop over the bars
        for q,thisbar in enumerate(ax.patches):
            # Set a different hatch for each bar
            if q < len(ax.patches) / 2:
                thisbar.set_hatch(hatches[0])
            else:
                thisbar.set_hatch(hatches[1])
        ax.legend()
        ax.legend_.set_title(None)
        #ax.set(ylim=(0,50))
        real_title = ""
        if collective == "binomialtreebcast":
            real_title = "Broadcast (Binomial Tree)"
        elif "nwaydissemination" in collective:
            real_title = "Dissemination"
        elif "pipelinedring" in collective:
            real_title = "Ring"
        ax.set_title(real_title)
        ax.set_xlabel("")
        #ticks = [4,8,16,32,64,128]
        #ax.set_xticks(ticks)
        #ax.set_xticklabels(ticks)
        handles, labels = ax.get_legend_handles_labels()     
        #ax.get_legend().remove()
        #ax.set_xscale("log2")
        #ax.set_xticklabels(ax.get_xticklabels(), rotation = 90)
        i += 1
    if show_all:
        #fig.legend(handles, labels, bbox_to_anchor=(.65, 1), ncol=5, title=None)
        plt.tight_layout()
        #plt.subplots_adjust(top=0.75)
    else:
        #fig.legend(handles, labels, bbox_to_anchor=(.92, 1), ncol=3, title=None)
        plt.tight_layout()
        #plt.subplots_adjust(top=0.7)
    fig.savefig("out/simulations/validation_relative_short_" + str(num_nodes) + ".pdf", format='pdf', dpi=100)
    plt.clf()


def hr_nodes(nodes):
    if nodes < 1024:
        return str(nodes)
    elif nodes < 1024*1024:
        return str(int(nodes / 1024)) + "K"
    else:
        sys.exit("Too large size: " + str(nodes))

def plot_scalability(df, collectives):
    # Lot of dimensions!:
    #   - Provider (one per subplot col -- only for cloud and Daint on a sep. plot?)
    #   - Instance type (one per subplot row -- only HPC v. non-HPC)
    #   - Collective (each on a different plot)
    #   - Node count (X-axis)
    #   - Time (Y-axis)
    #   - With/without the different type of noises (hue)
    handles = None
    labels = None 
    for collective in collectives:
        msgsizes = []                   
        xticklabels = [] 
        rows = 0
        cols = 0
        figsize = (0, 0)
        provinst = []
        nnodes = []
        if collective == "nwaydissemination_nocompute" or collective == "nwaydissemination":
            nnodes = [4, 64, 1024, 16384]
            xticklabels = ["4", "64", "1K", "16K"]
            msgsizes = [16]
            rows = 2
            cols = 4
            figsize = (12, 6)
            provinst = [("AWS", "HPC (Metal)"),  ("Azure", "HPC"), ("Azure", "HPC (200 Gb/s)"), ("GCP", "HPC"), \
                        ("Oracle", "HPC (Metal)"), ("Alps", "HPC (Metal)"), ("Daint", "HPC (Metal)"), ("DEEP-EST", "HPC (Metal)")]
            xanchor = .77
            tadj = .88
            sharex=False
            sharey=False
        elif collective == "pipelinedring":
            nnodes = [4, 16, 64, 256, 1024]
            xticklabels = ["4", "16", "64", "256", "1K"]
            msgsizes = [536870912]            
            rows = 2
            cols = 4
            figsize = (12, 6)
            provinst = [("AWS", "HPC (Metal)"),  ("Azure", "HPC"), ("Azure", "HPC (200 Gb/s)"), ("GCP", "HPC"), \
                        ("Oracle", "HPC (Metal)"), ("Alps", "HPC (Metal)"), ("Daint", "HPC (Metal)"), ("DEEP-EST", "HPC (Metal)")]
            xanchor = .77
            tadj = .88
            sharex=False
            sharey=False
        else:
            sys.exit("Unknown collective " + collective)

        for msgsize in msgsizes:
            i = 0
            fig, axes = plt.subplots(rows, cols, figsize=figsize, sharex=sharex, sharey=sharey)
            fig = plt.figure(constrained_layout=True, figsize=figsize)
            gs0 = fig.add_gridspec(2, 1)

            gs00 = gs0[0].subgridspec(1, 4)
            gs01 = gs0[1].subgridspec(1, 4)
            for a in range(1):
                for b in range(4):
                    fig.add_subplot(gs00[a, b])
            for a in range(1):
                for b in range(4):
                    fig.add_subplot(gs01[a, b])
            axes = fig.get_axes()
            for (provider, instance) in provinst:                
                #ax = axes[int(i / cols)][i % cols]         
                ax = axes[i]
                #with pd.option_context('display.max_rows', None, 'display.max_columns', None):  # more options can be specified also
                #    print(df[(df["Provider"] == provider) & (df["Instance Type"] == instance) & (df["Collective"] == collective) & \
                #                (df["Message Size"] == msgsize) & (df["Type"] == "Simulated")])
                filtered_data = df[(df["Provider"] == provider) & (df["Instance Type"] == instance) & (df["Collective"] == collective) & \
                                (df["Message Size"] == msgsize) & (df["Type"] == "Simulated") & (df["Nodes"].isin(nnodes))].copy()           
                if collective == "pipelinedring":
                    filtered_data["Time (us)"] *= 2 #Ring allreduce
                filtered_data["Time (ms)"] = filtered_data["Time (us)"] / 1000.0
                #if provider == "AWS" and instance =="HPC (Metal)" and collective == "pipelinedring":
                #    print(filtered_data[filtered_data["Nodes"] == 4])
                #print(provider)
                #print(instance)
                #print(collective)
                #print(msgsize)
                #print(filtered_data[filtered_data["Noise"] == "none"]["Nodes"])
                ax = sns.pointplot(data=filtered_data[filtered_data["Noise"] == "none"], x="Nodes", y="Time (ms)", \
                                ax=ax, hue="Noise", style="Noise", scale=.5) 
                flierprops = dict(markersize=1, linestyle='none')
                ax = sns.boxplot(data=filtered_data[filtered_data["Noise"] != "none"], x="Nodes", y="Time (ms)", \
                                hue="Noise", notch=True, showmeans=True, \
                                meanprops={"marker":"s","markerfacecolor":"white", "markeredgecolor":"black", "markersize":"4"}, \
                                flierprops=flierprops, \
                                ax=ax, linewidth=.1, hue_order=["os", "net", "os+net"])
                if collective == "nwaydissemination_nocompute":
                    if i < cols:
                        ax.set_xlabel(None)
                    if provider == "Oracle":
                        ax.set(ylim=(0,.3))
                        #ax.set(ylim=(0,None))
                    else:
                        ax.set(ylim=(0,None))
                if (i % 4):
                    ax.set_ylabel(None)
                #elif collective == "pipelinedring":
                #    ax.set(ylim=(80, 280))
                #    if i:
                #        ax.set_ylabel(None)
                ax.set_title(provider + " - " + instance)         
                handles, labels = ax.get_legend_handles_labels()     
                ax.get_legend().remove()   
                if xticklabels != None:
                    ax.set_xticklabels(xticklabels)
                i += 1        
            #labels = ["No Noise", "OS Noise", "Network Noise", "OS+Network Noise"]
            labels = []
            oldhandles, oldlabels = ax.get_legend_handles_labels()     
            for t in oldlabels:
                longlabel = ""
                if t == "none":
                    longlabel = "No Noise"
                elif t == "os":
                    longlabel = "OS Noise"
                elif t == "net":
                    longlabel = "Network Noise"
                elif t == "os+net":
                    longlabel = "OS+Network Noise"
                else:
                    sys.exit("Unknown label " + t)
                labels += [longlabel]
            #if collective == "nwaydissemination_nocompute":
            #    labels[1], labels[2] = labels[2], labels[1]
            #    oldhandles[1], oldhandles[2] = oldhandles[2], oldhandles[1]
            #    labels[2], labels[3] = labels[3], labels[2]
            #    oldhandles[2], oldhandles[3] = oldhandles[3], oldhandles[2]
            fig.legend(oldhandles, labels, bbox_to_anchor=(xanchor, 1), ncol=4, title=None)
            plt.tight_layout()
            plt.subplots_adjust(top=tadj)
            fig.savefig("out/simulations/scalability_" + collective + "_" + str(msgsize) + ".pdf", format='pdf', dpi=100)
            plt.clf()

def plot_cost_3(origdf, collectives, cost_type):
    # Lot of dimensions!:
    #   - Provider (one per subplot col -- only for cloud and Daint on a sep. plot?)
    #   - Instance type (one per subplot row -- only HPC v. non-HPC)
    #   - Collective (each on a different plot)
    #   - Node count (fixed to 1024)
    #   - Comp/comm ratio (X-axis)
    #   - Perf/Dollars (Y-axis)
    #   - With/without the different type of noises (hue)
    #for scale in [None, "log"]:
    for scale in [None]:
        scalestr = ""
        if scale == "log":
            scalestr = "_log"
        for collective in collectives:
            mm_sizes = [128]
            if collective == "pipelinedring":
                mm_sizes = [8192]
                nnodes = [4, 16, 64, 256, 1024]
                xticks = [4, 16, 64, 256, 1024]
                xticklabels = ["4", "16", "64", "256", "1K"]
            else:
                mm_sizes = [128]
                #nnodes = [4, 16, 64, 256, 1024, 4096, 16384]
                nnodes = [4, 64, 1024, 16384]
                xticks = nnodes
                xticklabels = ["4", "64", "1K", "16K"]
                #xticks = [1024, 4096, 16384]
                #xticklabels = ["1K", "4K", "16K"]
            for matrix_size in mm_sizes:
                i = 0
                rows = 2
                cols = 2
                #fig, axes = plt.subplots(rows, cols, figsize=(10, 5), sharex=False, sharey=False)
                fig = plt.figure(constrained_layout=True, figsize=(10, 5))
                gs0 = fig.add_gridspec(2, 1)

                gs00 = gs0[0].subgridspec(1, 2)
                gs01 = gs0[1].subgridspec(1, 3)
                for a in range(1):
                    for b in range(2):
                        fig.add_subplot(gs00[a, b])
                for a in range(1):
                    for b in range(3):
                        fig.add_subplot(gs01[a, b])
                axes = fig.get_axes()
                #for provider in ["AWS", "Azure", "GCP", "Alps", "Daint", "DEEP-EST"]:
                for provider in ["AWS", "Azure", "GCP", "Oracle", "Daint"]:
                    df = pd.DataFrame()
                    #ax = axes[int(i / cols)][i % cols]
                    ax = axes[i]                    
                    allreduce_size = matrix_size*matrix_size*8                                 
                    if provider == "Daint" or provider == "Alps" or provider == "AWS" or provider == "DEEP-EST" or provider == "Oracle":
                        instances = ["HPC (Metal)"]
                    else:
                        instances = ["HPC"]
                    for instance in instances:
                        for noise in ["none", "os", "net", "os+net"]:
                            copy = origdf.copy()
                            copy = copy[(copy["Instance Type"] == instance) & (copy["Provider"] == provider) & (copy["Noise"] == noise) & \
                                        (copy["Collective"] == collective) & (copy["Message Size"] == allreduce_size) & \
                                        (copy["Type"] == "Simulated") & (copy["Nodes"].isin(nnodes))]                            
                            (time, gflops) = load_gemm_times(matrix_size, provider, instance)
                            bytes_matrix = matrix_size*matrix_size*8
                            if collective == "pipelinedring":
                                copy["Time (us)"] *= 2 # Two rings for the allreduce
                            copy["Total Time (us)"] = (copy["Time (us)"]) + time
                            #print("Memes " + str((time/copy["Total Time (us)"].mean())*100.0))
                            #print(provider)
                            #print(instance)
                            #print(time)
                            #print(copy["Time (us)"].mean())
                            #if collective == "pipelinedring":
                            #    print("Comm frac: " + str((copy["Time (us)"] / copy["Total Time (us)"]).mean()))                
                            copy["Total Time (s)"] = copy["Total Time (us)"] / 1000000.0
                            copy["Total Time (h)"] = copy["Total Time (s)"] / 3600
                            copy["Iterations x Hour"] = (3600*1000000) / (copy["Total Time (us)"])
                            copy["Hourly Cost"] = (copy["Nodes"]*costs[(provider, instance, cost_type)])                            
                            copy["Matrix Size"] = matrix_size
                            copy["Name"] = noise
                            copy["USD"] = copy["Total Time (h)"]*copy["Hourly Cost"]
                            copy["USD per Iteration"] = copy["Hourly Cost"] * copy["Total Time (h)"]
                            copy["Iterations per USD"] = 1 / copy["USD per Iteration"]
                            df = pd.concat([df, copy])
                
                    df.reset_index(inplace=True, drop=True)                    
                    for nn in nnodes:
                        cost_none = float(df[(df["Noise"] == "none") & (df["Nodes"] == nn)]["USD per Iteration"].mean())
                        df.loc[df['Nodes'] == nn, 'Cost Increase (%)'] = ((df[df["Nodes"] == nn]["USD per Iteration"] - cost_none) / cost_none)*100.0
                    #print(df[["USD per Iteration", "Cost Increase (%)", "Noise"]])

                    # Normalize per node
                    df["Normalized Cost per Iteration"] = 0
                    norm = {}
                    for node in nodes_total:
                        norm[node] = df[df["Nodes"] == node]["USD per Iteration"].min()

                    for index, row in df.iterrows():            
                        df.at[index, "Normalized Cost per Iteration"] = row["USD per Iteration"] / norm[row["Nodes"]]

                    #y = "Iterations per USD"
                    #y = "USD"
                    y = "USD per Iteration"
                    y = "Cost Increase (%)"
                    filtered_data = df
                    if len(filtered_data) == 0:
                        continue
                    filtered_data["Time (ms)"] = filtered_data["Time (us)"] / 1000.0
                    filtered_data = filtered_data[filtered_data["Noise"] != "none"]
                    #ax = sns.lineplot(data=filtered_data, x="Nodes", y=y, ax=ax, hue="Name", style="Name", markers=True, dashes=True, ci="sd") 
                    ax = sns.barplot(data=filtered_data, x="Nodes", y=y, ax=ax, hue="Name") 
                    # Define some hatches
                    hatches = ["---", "///", "xxx"]
                    # Loop over the bars
                    for q,thisbar in enumerate(ax.patches):
                        # Set a different hatch for each bar
                        if collective == "pipelinedring":
                            thisbar.set_hatch(hatches[int(q / 5)])
                        else:
                            thisbar.set_hatch(hatches[int(q / 4)])
                    #ax.legend()
                    ax.set_title(provider + " " + instance)
                    ax.legend_.set_title(None)
                    handles, labels = ax.get_legend_handles_labels()     
                    ax.get_legend().remove()
                    labels = []
                    oldhandles, oldlabels = ax.get_legend_handles_labels()     
                    for t in oldlabels:
                        longlabel = ""
                        if t == "none":
                            longlabel = "No Noise"
                        elif t == "os":
                            longlabel = "OS Noise"
                        elif t == "net":
                            longlabel = "Network Noise"
                        elif t == "os+net":
                            longlabel = "OS+Network Noise"
                        else:
                            sys.exit("Unknown label " + t)
                        labels += [longlabel]

                    #labels = ["No Noise", "OS+Network Noise"]
                    #ax.legend_.set_labels(labels)
                    #for t, l in zip(ax.flat[0].get_legend().texts, labels):
                    #    t.set_text(l)

                    if scale is not None:
                        ax.set_xscale(scale)
                        ax.set_yscale(scale)
                    #ax.set_xticklabels(xticklabels)
                    #ax.set_xticks(xticks)
                    if (i != 0) and (i != 2):
                        ax.set_ylabel(None)
                    i += 1
                fig.legend(handles, labels, bbox_to_anchor=(.75, 1), ncol=3, title=None)
                plt.tight_layout()
                plt.subplots_adjust(top=0.85)
                fig.savefig("out/simulations/cost_" + cost_type.lower() + "_" + collective + "_" + str(matrix_size) + scalestr + "_new.pdf", format='pdf', dpi=100)
                plt.clf()

def main():
    # Load paths
    with open("../data/description.csv", mode='r') as infile:
        reader = csv.reader(infile)    
        global paths
        paths = {(rows[0],rows[1],rows[2],rows[3]):"../data/" + rows[4] for rows in reader}

    df = pd.DataFrame()
    for filename in os.scandir(simulation_data_folder):            
        if filename.is_file() and filename.path.endswith(".csv"):
            print("Loading " + filename.path)
            df = pd.concat([df, pd.read_csv(filename.path, comment=",", names=["Index","Noise","Type","Collective","Provider","Instance Type","Placement", "Nodes","Scenario","Time (us)","Message Size"])])
            print(df)
    df = df.dropna()
    df.reset_index(inplace=True, drop=True)
    plot_scalability(df.copy(), ["nwaydissemination_nocompute"]) 
    plot_scalability(df.copy(), ["pipelinedring"])       
    plot_validation_f = True
    if plot_validation_f:
        plot_validation_relative(df.copy())
        for num_nodes in [4, 8, 16, 32]:
            plot_validation_relative_short(df.copy(), num_nodes)
        for provider in ["GCP", "DEEP-EST", "Daint", "Azure", "AWS", "Alps", "Oracle"]:
            plot_validation_pingpong(df.copy(), provider)    
            if provider == "Azure":
                plot_validation(df.copy(), provider, "HPC")    
                plot_validation(df.copy(), provider, "HPC (200 Gb/s)")    
            elif provider == "GCP":
                plot_validation(df.copy(), provider, "HPC")    
            else:
                plot_validation(df.copy(), provider, "HPC (Metal)")      
    plot_cost_3(df.copy(), ["pipelinedring"], "On-Demand") 
    plot_cost_3(df.copy(), ["nwaydissemination_nocompute"], "On-Demand") 
    plot_cost_3(df.copy(), ["nwaydissemination_nocompute", "pipelinedring"], "On-Demand") 
    plot_cost_3(df.copy(), ["nwaydissemination_nocompute", "pipelinedring"], "Upfront")     


if __name__ == "__main__":
    main()
