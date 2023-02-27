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
sys.path.append('../simulations/')
from loggp_params import get_loggp_params

def patch_violinplot(palette, n):
    from matplotlib.collections import PolyCollection
    ax = plt.gca()
    violins = [art for art in ax.get_children() if isinstance(art, PolyCollection)]
    colors = sns.color_palette(palette, n_colors=n) * (len(violins)//n)
    for i in range(len(violins)):
        violins[i].set_edgecolor(colors[i])

sns.set_style("whitegrid")

plot_ci = "sd"

providers = ["AWS", "Azure", "GCP", "Oracle", "Alps", "Daint", "DEEP-EST"]
instances = ["Normal", "HPC", "HPC (Metal)", "HPC (200 Gb/s)"]
placements = ["Same Rack", "Different Racks"]
times = ["Night", "Day"]

# Optimal stuff
instance_type_t = {}
instance_type_t["GCP"] = "HPC"
instance_type_t["AWS"] = "HPC (Metal)"
instance_type_t["Azure"] = "HPC"
instance_type_t["Oracle"] = "HPC (Metal)"
instance_type_t["Daint"] = "HPC (Metal)"
instance_type_t["Alps"] = "HPC (Metal)"
instance_type_t["DEEP-EST"] = "HPC (Metal)"

placement_t = {}
placement_t["GCP"] = "Same Rack"
placement_t["AWS"] = "Same Rack"
placement_t["Azure"] = "Same Rack"
placement_t["Oracle"] = "Same Rack"
placement_t["Daint"] = "Same Rack"
placement_t["Alps"] = "Same Rack"
placement_t["DEEP-EST"] = "Same Rack"

time_t = {}
time_t["GCP"] = "Day"
time_t["AWS"] = "Day"
time_t["Azure"] = "Day"
time_t["Oracle"] = "Day"
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
    elif name == "Oracle":
        return "oracle"
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

def plot_noise_single(df, ax, data_type, data_type_human, hue, plottype, showfliers=False):
    if len(df) == 0:
        return
    if plottype == "violin":
        ax = sns.violinplot(data=df, x="Provider", y=data_type_human, hue=hue, saturation=1, cut=0, ax=ax)    
    elif plottype == "box":
        ax = sns.boxplot(data=df, x="Provider", y=data_type_human, hue=hue, saturation=1, showfliers=showfliers, ax=ax)    
        
    #if data_type == "os_noise":
    #    ax.set(ylim=(0, 50000))
    #elif data_type == "noise_lat":
    #    ax.set(ylim=(0, 20))
    #if data_type == "noise_bw":
    #    ax.set(ylim=(0, 100))

def plot_noise(data_type, data_type_human, showfliers=False):
    plottype = "box"
    filename = 'out/noise/' + data_type + '_' + plottype + '.pdf'
    print("Plotting " + filename + " ...")    
    # On a violinplot we can plot lat/bw as a function of two variables (three if we do 1D subplots, four if we do 2D subplots)
    # E.g., we can have 2x2 subplots (different cols = different placements, different rows = different time)
    # Each subplot has the x for the provider, and the hue for the instance type    
    
    # Get data
    df = load_all(data_type)           

    # Create sub frames
    df_day = filter_time(df, "Day")
    df_night = filter_time(df, "Night")
    df_same_rack_day = filter_placement(df_day, "Same Rack")
    df_different_rack_day = filter_placement(df_day, "Different Racks")
    df_same_rack_night = filter_placement(df_night, "Same Rack")
    df_different_rack_night = filter_placement(df_night, "Different Racks")

    ###########
    # Latency #
    ###########
    fig, axes = plt.subplots(2, 2, figsize=(10,5), sharex=False, sharey=True)
    plot_noise_single(df_same_rack_day, axes[0][0], data_type, data_type_human, "Instance", plottype, showfliers)
    axes[0][0].set_title("Same Rack - Day")
    axes[0][0].set_xlabel("")

    plot_noise_single(df_different_rack_day, axes[0][1], data_type, data_type_human, "Instance", plottype, showfliers)
    axes[0][1].set_title("Different Racks - Day")
    axes[0][1].set_xlabel("")

    plot_noise_single(df_same_rack_night, axes[1][0], data_type, data_type_human, "Instance", plottype, showfliers)
    axes[1][0].set_title("Same Rack - Night")
    axes[1][0].set_xlabel("")

    plot_noise_single(df_different_rack_night, axes[1][1], data_type, data_type_human, "Instance", plottype, showfliers)
    axes[1][1].set_title("Different Racks - Night")    
    axes[1][1].set_xlabel("")

    plt.tight_layout()
    fig.savefig(filename, format='pdf', dpi=100)
    plt.clf()

def plot_noise_long(data_type, data_type_human):
    filename = 'out/noise/' + data_type + '_long.pdf'
    print("Plotting " + filename + " ...")    
    fig, axes = plt.subplots(1, 1, figsize=(10,5))
    df = pd.DataFrame()
    x_col = ""
    for provider in providers:
        if data_type == "os_noise":
            df_tmp = get_data(provider, instance_type_t[provider], "Same Rack", "Day", data_type)
            x_col = "Time (s)"
        else:
            df_tmp = get_data(provider, instance_type_t[provider], "Same Rack", "Long", data_type)
            x_col = "Sample"
        df = pd.concat([df, df_tmp])
    df.reset_index(inplace=True, drop=True)             
    df["Latency (us)"] = df["RTT/2 (us)"]
    ax = sns.scatterplot(data=df, x=x_col, y=data_type_human, hue="Provider", style="Provider")
    if "Latency" in data_type_human and data_type != "os_noise":
        ax.set(ylim=(1, 30))
    plt.tight_layout()
    ax.figure.savefig(filename, format='pdf', dpi=100)
    plt.clf()

def plot_size_vs_lat_bw(df, ax, data_type, data_type_human, style, provider, xlim=None, ylim=None, innerpars_dt = None, innerpars=None, innerxlim=None, innerylim=None, palette=None, tick_spacing=0, markers=None, dashes=None, innertick_spacing=None, innerfontsize=6):
    if tick_spacing == 0:
        tick_spacing = 4
    if innertick_spacing == None:
        innertick_spacing = tick_spacing
    if palette is not None:
        ax = sns.lineplot(data=df, x="Message Size", y=data_type_human, style=style, \
                hue=style, markers=markers, dashes=dashes, ci=plot_ci, sort=False, palette=palette, ax=ax)    
    else:
        ax = sns.lineplot(data=df, x="Message Size", y=data_type_human, style=style, \
                      hue=style, markers=True, dashes=True, ci=plot_ci, sort=False, ax=ax)    
    #ax.legend(title=None, ncol=3)
    ax.legend(ncol=3, fontsize=8, title_fontsize=8, title=style)
    ax.xaxis.set_major_locator(ticker.MultipleLocator(tick_spacing))
    if xlim != None:
        ax.set(xlim=xlim) 
    if ylim != None:
        ax.set(ylim=ylim) 
   
    # inset axes....
    if innerpars != None:
        axins = ax.inset_axes(innerpars)
        # Draw inner plot
        if palette is not None:
            sns.lineplot(data=df, x="Message Size", y=innerpars_dt, style=style, \
                    hue=style, markers=markers, dashes=dashes, ci=plot_ci, sort=False, legend=False, palette=palette, ax=axins)
        else:            
            sns.lineplot(data=df, x="Message Size", y=innerpars_dt, style=style, \
                    hue=style, markers=True, dashes=True, ci=plot_ci, sort=False, legend=False, ax=axins)
        axins.set(xlim=innerxlim)
        axins.xaxis.set_major_locator(ticker.MultipleLocator(innertick_spacing))
        axins.set(ylim=innerylim)
        #axins.set_xticklabels([])
        #axins.set_yticklabels([])
        axins.tick_params(axis='x', labelsize=innerfontsize)
        axins.tick_params(axis='y', labelsize=innerfontsize)
        axins.set_xlabel("")
        axins.set_ylabel(innerpars_dt, fontsize=innerfontsize)
        #ax.indicate_inset_zoom(axins, edgecolor="black")

    #if "lat" in data_type:
    #    ax.set_yscale("log")    

def plot_lat_bw(data_type, data_type_human, time, placement):
    filename = 'out/lat_bw/' + data_type + '_' + fname(time) + '_' + fname(placement) + '.pdf'
    print("Plotting " + filename + " ...")
    # On a lineplot we can plot lat/bw as a function of two variables (three if we do 1D subplots, four if we do 2D subplots)
    # E.g., we can have 2x2 subplots (different cols = different placements, different rows = different time)
    # However we have 5 dimensions (the 4 as above + the message size)
    # Each subplot has the x for the msg size, the y for the lat/bw, the hue for the instance type. Then 4 subplots (one for each provider)
    # We fix day/night and placement
    
    rows = 2
    cols = 3
    fig, axes = plt.subplots(rows, cols, figsize=(10,5), sharex=False, sharey=True)
    i = 0    
    for provider in providers:
        # Get data
        suffix = ""
        if provider == "AWS":
            suffix = "x16" # For AWS we show the data with 16 stripes
        else:
            suffix = "x1"
        placement_real = placement
        time_real = time
        if placement == "any":
            placement_real = "Same Rack"
        if time == "any":
            if provider == "AWS":
                time_real = "Night"
            else:
                time_real = "Day"

        df = load_all(data_type + suffix)
        df = filter_placement(df, placement_real)
        df = filter_time(df, time_real)
        df = filter_provider(df, provider)
        ax = axes[int(i / cols)][i % cols]
        plot_size_vs_lat_bw(df, ax, data_type, data_type_human, "Instance", provider)
        ax.set_title(provider)
        if "bw" in data_type:
            ax.set(ylim=(0.0, 100.0))        
        i += 1

    plt.tight_layout()
    fig.savefig(filename, format='pdf', dpi=100)
    plt.clf()

def plot_lat_bw_conc(data_type, data_type_human, time, placement, instance_type, conc_or_stripe):
    filename = 'out/lat_bw_' + conc_or_stripe + '/' + data_type + '_' + fname(instance_type) + '_' + fname(time) + '_' + fname(placement) + '.pdf'
    print("Plotting " + filename + " ...")
    # On a lineplot we can plot lat/bw as a function of two variables (three if we do 1D subplots, four if we do 2D subplots)
    # E.g., we can have 2x2 subplots (different cols = different placements, different rows = different time)
    # However we have 6 dimensions (the 5 as above + the concurrent messages)
    # Each subplot has the x for the msg size, the y for the lat/bw, the hue for the concurrency level. Then 4 subplots (one for each provider)
    # We fix placement, day/night, and instance type
    
    rows = 2
    cols = 3
    fig, axes = plt.subplots(rows, cols, figsize=(10,5), sharex=False, sharey=True)
    i = 0
    hue = ""
    if conc_or_stripe == "stripe":
        hue = "Stripes"
    else:
        hue = "Concurrent Connection"

    for provider in providers:
        # Get data
        df = pd.DataFrame()
        for conc in [1, 2, 4, 8, 16]:
            if conc_or_stripe == "stripe":
                suffix = "x" + str(conc)
            else:
                suffix = "y" + str(conc)

            instance_type_real = instance_type
            placement_real = placement
            time_real = time
            if instance_type == "any":
                instance_type_real = "HPC (Metal)"            
            if placement == "any":
                placement_real = "Same Rack"
            if time == "any":
                if provider == "AWS":
                    time_real = "Night"
                else:
                    time_real = "Day"

            dfc = load_all(data_type + suffix)
            dfc = filter_instance(dfc, instance_type_real)
            dfc = filter_placement(dfc, placement_real)
            dfc = filter_time(dfc, time_real)
            dfc[hue] = str(conc)
            df = pd.concat([df, filter_provider(dfc, provider)])
        df.reset_index(inplace=True, drop=True)             
        ax = axes[int(i / cols)][i % cols]
        plot_size_vs_lat_bw(df, ax, data_type, data_type_human, hue, provider)
        ax.set_title(provider)        
        if "bw" in data_type:
            ax.set(ylim=(0.0, 100.0))
        i += 1

    plt.tight_layout()
    fig.savefig(filename, format='pdf', dpi=100)
    plt.clf()

def plot_lat_bw_sw(data_type, data_type_human, time, placement, instance_type):
    filename = 'out/lat_bw_sw/' + data_type + '_' + fname(instance_type) + '_' + fname(time) + '_' + fname(placement) + '.pdf'
    print("Plotting " + filename + " ...")
    # On a lineplot we can plot lat/bw as a function of two variables (three if we do 1D subplots, four if we do 2D subplots)
    # E.g., we can have 2x2 subplots (different cols = different placements, different rows = different time)
    # However we have 6 dimensions (the 5 as lat_bw + sw stack)
    # Each subplot has the x for the msg size, the y for the lat/bw, the hue for the sw stack. Then 4 subplots (one for each provider)
    # We fix placement, day/night, and instance type

    rows = 2
    cols = 3
    fig, axes = plt.subplots(rows, cols, figsize=(10,5), sharex=False, sharey=True)
    i = 0
    for provider in providers:        
        # Get data
        df = pd.DataFrame()
        for sw in ["mpi", "tcp", "udp", "ib", "ibv"]:
            suffix = "_" + sw 
            if provider == "AWS":
                suffix += "_conc1"
                
            dfc = load_all(data_type + suffix)
            dfc = filter_instance(dfc, instance_type)
            dfc = filter_placement(dfc, placement)
            dfc = filter_time(dfc, time)
            dfc["Sw"] = sw
            df = pd.concat([df, filter_provider(dfc, provider)])
        df.reset_index(inplace=True, drop=True)             
        ax = axes[int(i / cols)][i % cols]
        plot_size_vs_lat_bw(df, ax, data_type, data_type_human, "Sw", provider)
        ax.set_title(provider)
        if "bw" in data_type:
            ax.set(ylim=(0.0, 100.0))
        i += 1

    plt.tight_layout()
    fig.savefig(filename, format='pdf', dpi=100)
    plt.clf()

def plot_paper_striping(stripe_or_conc="stripe"):
    # Plot striping effects (linesplot):
    #   - Y axis: latency or bw
    #   - X axis: message size
    #   - hue: striping factor
    #   - one sublot for each provider/instance type
    #   - Fixed time (Night) and allocation (Same Rack)
    for metric in ["unidirectional_bw"]:
        filename = 'out/paper_pre/' + metric + '_' + stripe_or_conc + '.pdf'
        print("Plotting " + filename + " ...")
        rows = 1
        cols = 2
        fig, axes = plt.subplots(rows, cols, figsize=(8,2.5), sharex=False, sharey=True)
        i = 0
        handles = None
        labels = None
        for provider in ["AWS", "GCP"]:
            # Get data
            df = pd.DataFrame()
            for conc in [1, 2, 4, 8, 16]:
                if stripe_or_conc == "stripe" or conc == 1:
                    suffix = "x" + str(conc)
                else:
                    suffix = "y" + str(conc)
                dfc = load_all(metric + suffix)
                dfc = filter_instance(dfc, instance_type_t[provider])
                dfc = filter_placement(dfc, placement_t[provider])
                dfc = filter_time(dfc, time_t[provider])
                dfc["Stripes"] = str(conc)
                df = pd.concat([df, filter_provider(dfc, provider)])
            df.reset_index(inplace=True, drop=True)             
            #ax = axes[int(i / cols)][i % cols]
            ax = axes[i]
            innerxlim=None
            innerylim=None
            innerpars = None
            xlim = None
            ylim = None
            if "lat" in metric: # Lat
                innerxlim=(0, 16)
                innerylim=(20, 50)
                innerpars = [0.15, 0.45, 0.45, 0.45]
                innerpars_dt = "RTT/2 (us)"
            else: # Bw
                innerxlim=(0, 16)
                innerylim=(0, 50)
                ylim=(0,100)
                innerpars = [0.15, 0.45, 0.45, 0.45]
                innerpars_dt = "RTT/2 (us)"

            plot_size_vs_lat_bw(df, ax, metric, metric_human[metric], "Stripes", provider, xlim=xlim, ylim=ylim, innerpars_dt=innerpars_dt, innerpars=innerpars, innerxlim=innerxlim, innerylim=innerylim)
            ax.set_title(provider)   
            handles, labels = ax.get_legend_handles_labels()     
            ax.get_legend().remove()
            i += 1

        if stripe_or_conc == "stripe":
            title = "Striping Factor"
        else:
            title = "Concurrent Communications"
        fig.legend(handles, labels, bbox_to_anchor=(.72, 1.02), ncol=5, title=title, fontsize=8, title_fontsize=8)
        plt.tight_layout()
        plt.subplots_adjust(top=0.8)
        fig.savefig(filename, format='pdf', dpi=100)
        plt.clf()

def plot_paper_lat_bw():
    # Plot lat and bw (linesplot):
    #   - Y axis: latency or bw
    #   - X axis: message size
    #   - hue: provider
    #   - one sublot for each lat and one for bandwidth
    #   - Fixed time (Night), allocation (Same Rack), and instance types (HPC)
    filename = 'out/paper_pre/lat_bw.pdf'
    print("Plotting " + filename + " ...")
    rows = 1
    cols = 1
    fig, axes = plt.subplots(rows, cols, figsize=(8,3), sharex=False, sharey=False)
    i = 0
    for metric in ["unidirectional_bw"]:        
        handles = None
        labels = None
        df = pd.DataFrame()            
        for provider in providers:
            stripes = [1]
            if provider == "AWS" or provider == "GCP" or provider == "Oracle":
                stripes = [1, 16]
            
            # Get data
            for stripe in stripes:
                suffix = "x" + str(stripe)
                if (provider == "GCP" or provider == "AWS" or provider == "Oracle") and stripe != 1:
                    suffix = "y" + str(stripe)
                dfc = load_all(metric + suffix)            
                dfc = filter_instance(dfc, instance_type_t[provider])            
                dfc = filter_placement(dfc, placement_t[provider])            
                dfc = filter_time(dfc, time_t[provider])
                dfc = filter_provider(dfc, provider)
                if provider == "AWS" or provider == "GCP" or provider == "Oracle":
                    small_msgs = ["1B", "2B", "4B", "8B", "16B", "32B", "64B", "128B", "256B"]
                    if stripe == 1:
                         dfc = dfc[dfc['Message Size'].isin(small_msgs)]
                    elif stripe == 16:
                         dfc = dfc[~dfc['Message Size'].isin(small_msgs)]
                df = pd.concat([df, dfc])
        df.reset_index(inplace=True, drop=True)   
        #ax = axes[int(i / cols)][i % cols]
        ax = axes
        innerxlim=None
        innerylim=None
        innerpars = None
        xlim = None
        ylim = None
        if "lat" in metric: # Lat
            innerxlim=(0, 8)
            innerylim=(0, 30)
            innerpars = [0.15, 0.4, 0.45, 0.45]
            innerpars_dt = "RTT/2 (us)"
        else: # Bw
            innerxlim=(0, 8)
            innerylim=(0, 30)
            ylim=(0,100)
            innerpars = [0.07, 0.35, 0.44, 0.55]
            innerpars_dt = "RTT/2 (us)"

        plot_size_vs_lat_bw(df, ax, metric, metric_human[metric], "Provider", None, xlim=xlim, ylim=ylim, innerpars_dt=innerpars_dt, innerpars=innerpars, innerxlim=innerxlim, innerylim=innerylim, innerfontsize=8)
        ax.set_title(None)   
        handles, labels = ax.get_legend_handles_labels()     
        ax.get_legend().remove()
        i += 1

    fig.legend(handles, labels, bbox_to_anchor=(.97, .95), ncol=7, fontsize=10, title_fontsize=10)
    plt.tight_layout()
    plt.subplots_adjust(top=0.8)
    fig.savefig(filename, format='pdf', dpi=100)
    plt.clf()

def plot_paper_lat_bw_instances(metric):
    # Plot lat and bw (linesplot):
    #   - Y axis: latency or bw
    #   - X axis: message size
    #   - hue: instance type
    #   - one sublot for each provider
    #   - Fixed time (Night), allocation (Same Rack)
    filename = 'out/paper_pre/' + metric + '_instances.pdf'
    print("Plotting " + filename + " ...")
    rows = 2
    cols = 2
    fig, axes = plt.subplots(rows, cols, figsize=(8,5), sharex=False, sharey=False)
    i = 0
    palette_dict = {}
    legend_elements = []
    markers = {"Normal" : 'o', "HPC" : 'D', "HPC (Metal)" : 's', "HPC (200 Gb/s)" : '^'}
    #dashes = {"Normal" : '-', "HPC" : '--', "HPC (Metal)" : '-.', "HPC (200 Gb/s)" : ':'}
    for instance in instances:
        palette_dict[instance] = sns.color_palette()[i]
        legend_elements += [Line2D([0], [0], marker=markers[instance], lw=1, color=sns.color_palette()[i], label=instance)]
        i += 1
    i = 0
    for provider in providers:
        if provider == "Daint" or provider == "Alps" or provider == "DEEP-EST":
            continue
        handles = None
        labels = None
        df = pd.DataFrame()            
        for instance in instances:      
            stripes = [1]
            if provider == "AWS" or provider == "GCP" or provider == "Oracle":
                stripes = [1, 16]
            elif (provider == "Azure" and instance == "Normal"):
                stripes = [1, 2]
            
            # Get data
            for stripe in stripes:
                if stripe == 1:
                    suffix = "x" + str(stripe)
                else:
                    suffix = "y" + str(stripe)
                dfc = load_all(metric + suffix)            
                dfc = filter_instance(dfc, instance)            
                dfc = filter_placement(dfc, placement_t[provider])            
                dfc = filter_time(dfc, time_t[provider])
                dfc = filter_provider(dfc, provider)

                if provider == "AWS" or provider == "GCP" or ((provider == "Azure" or provider == "Oracle") and instance == "Normal"):
                    small_msgs = ["1B", "2B", "4B", "8B", "16B", "32B", "64B", "128B", "256B"]
                    if stripe == 1:
                         dfc = dfc[dfc['Message Size'].isin(small_msgs)]
                    else:
                         dfc = dfc[~dfc['Message Size'].isin(small_msgs)]
                         

                #if len(stripes) > 1:
                #    dfc["Provider"] = dfc["Provider"] + " (SF=" + str(stripe) + ")"
                df = pd.concat([df, dfc])
        df.reset_index(inplace=True, drop=True)   
        ax = axes[int(i / cols)][i % cols]
        #ax = axes[i]
        innerxlim=None
        innerylim=None
        innerpars = None
        xlim = None
        ylim = None
        if "lat" in metric: # Lat
            innerxlim=(0, 8)
            innerylim=(0, 40)
            innerpars = [0.1, 0.4, 0.45, 0.45]
            innerpars_dt = "RTT/2 (us)"
        else: # Bw
            innerxlim=(0, 8)
            if provider == "AWS":
                innerylim=(15, 30)
            elif provider == "GCP":
                innerylim=(10, 25)
            else:
                innerylim=(0, 40)
            #ylim=(0,200)
            if provider == "AWS":
                innerpars = [0.18, 0.4, 0.45, 0.45]
            elif provider == "GCP":
                innerpars = [0.15, 0.4, 0.41, 0.45]
            elif provider == "Oracle":
                innerpars = [0.12, 0.5, 0.41, 0.45]
            else:
                innerpars = [0.15, 0.4, 0.45, 0.45]
            innerpars_dt = "RTT/2 (us)"

        plot_size_vs_lat_bw(df, ax, metric, metric_human[metric], "Instance", None, xlim=xlim, ylim=ylim, innerpars_dt=innerpars_dt, innerpars=innerpars, innerxlim=innerxlim, innerylim=innerylim, palette=palette_dict, tick_spacing=8, markers=markers, dashes=None, innertick_spacing=4)
        ax.set_title(provider)   
        ax.get_legend().remove()
        i += 1

    fig.legend(handles=legend_elements, bbox_to_anchor=(.82, 1), ncol=len(instances), fontsize=10, title_fontsize=10)
    plt.tight_layout()
    plt.subplots_adjust(top=0.88)
    fig.savefig(filename, format='pdf', dpi=100)
    plt.clf()



def plot_paper_bibw():
    # Plot bibw (linesplot):
    #   - Y axis: bibw
    #   - X axis: message size
    #   - hue: provider
    #   - one sublot for each lat and one for bandwidth
    #   - Fixed time (Night), allocation (Same Rack), and instance types (HPC)
    filename = 'out/paper_pre/bibw.pdf'
    print("Plotting " + filename + " ...")
    rows = 1
    cols = 1
    fig, axes = plt.subplots(rows, cols, figsize=(5,2.5), sharex=False, sharey=False)
    i = 0
    for metric in ["bidirectional_bw"]:        
        handles = None
        labels = None
        df = pd.DataFrame()            
        for provider in providers:
            if provider == "GCP" or provider == "Azure":
                instance_type = "HPC"
            else:
                instance_type = "HPC (Metal)"

            stripes = [1]
            if provider == "GCP" or provider == "AWS":
                stripes = [1, 16]
            
            if provider == "GCP":
                placement = "Different Racks"
                time = "Night"
            else:
                placement = "Same Rack"
                if provider == "Daint":
                    time = "Night"
                else:
                    time = "Day"
            # Get data
            for stripe in stripes:
                suffix = "x" + str(stripe)
                dfc = load_all(metric + suffix)            
                dfc = filter_instance(dfc, instance_type)            
                dfc = filter_placement(dfc, placement)            
                dfc = filter_time(dfc, time)
                dfc = filter_provider(dfc, provider)
                if len(stripes) > 1:
                    dfc["Provider"] = dfc["Provider"] + " (SF=" + str(stripe) + ")"
                df = pd.concat([df, dfc])
        df.reset_index(inplace=True, drop=True)   
        #ax = axes[int(i / cols)][i % cols]
        ax = axes
        innerxlim=None
        innerylim=None
        innerpars = None
        xlim = None
        ylim = None
        if "lat" in metric: # Lat
            innerxlim=(0, 20)
            innerylim=(0, 100)
            innerpars = [0.1, 0.4, 0.45, 0.45]
            innerpars_dt = "RTT/2 (us)"
        else: # Bw
            innerxlim=(0, 20)
            innerylim=(0, 100)
            ylim=(0,100)
            innerpars = [0.1, 0.5, 0.45, 0.45]
            innerpars_dt = "RTT/2 (us)"

        plot_size_vs_lat_bw(df, ax, metric, metric_human[metric], "Provider", None, xlim=xlim, ylim=ylim, innerpars_dt=innerpars_dt, innerpars=innerpars, innerxlim=innerxlim, innerylim=innerylim)
        ax.set_title(None)   
        handles, labels = ax.get_legend_handles_labels()     
        ax.get_legend().remove()
        i += 1

    fig.legend(handles, labels, bbox_to_anchor=(1, 1), ncol=6, fontsize=8, title_fontsize=8)
    plt.tight_layout()
    plt.subplots_adjust(top=0.85)
    fig.savefig(filename, format='pdf', dpi=100)
    plt.clf()


def plot_paper_netnoise():
    # Plot network noise (boxplot):
    #   - Y axis: latency or bw
    #   - X axis: provider
    #   - hue: instance type
    #   - subplots: Latency and bandwidth
    #   - Fixed time (Day) and allocation (Different Racks)
    filename = 'out/paper_pre/netnoise.pdf'
    print("Plotting " + filename + " ...")
    rows = 1
    cols = 2
    fig, axes = plt.subplots(rows, cols, figsize=(10,2.5), sharex=False, sharey=False)
    i = 0
    
    for metric in ["noise_lat", "noise_bw"]:    
        # Create sub frames
        df = load_all(metric)
        df = filter_time(df, "Day")
        df = filter_placement(df, "Same Rack")
        plot_noise_single(df, axes[i], metric, metric_human[metric], "Instance", "box")
        #axes[0][0].set_title(metric_human[metric])
        #axes[0][0].set_xlabel("")
        #axes[i].get_legend().remove()
        i += 1

    fig.legend(bbox_to_anchor=(1.3, 0.6))

    fig.tight_layout()
    fig.savefig(filename, format='pdf', dpi=100)
    plt.clf()

def plot_paper_hoverboard(provider):
    # Plot hoverboard:
    #   - Y axis: latency or bw
    #   - X axis: provider
    #   - hue: instance type
    #   - subplots: Latency and bandwidth
    #   - Fixed time (Day) and allocation (Different Racks)
    filename = 'out/paper_pre/hoverboard_' + provider + '.pdf'
    print("Plotting " + filename + " ...")

    hoverboard_file =  "hoverboard_reps_1.out"

    warmup_iterations = 10
    iterations_per_run = 30

    df_global = pd.DataFrame()
    fig, axes = plt.subplots(1, 1, figsize=(5,2), sharex=False, sharey=False)

    instance = ""
    nviolins = 0
    if provider == "Azure" or provider == "GCP":
        instance = "HPC"
    else:
        instance = "HPC (Metal)"
    
    if provider == "Azure":
        nviolins = 3
    elif provider == "GCP":
        nviolins = 6
    elif provider == "Oracle":
        nviolins = 6
    elif provider == "AWS":
        nviolins = 6

    infile = paths[(provider, instance, "Same Rack", "Day")] + "/" + hoverboard_file
    df = pd.read_csv(infile, comment="#", names=["RTT (ns)", "Sleep Time (ns)", "Repetitions"])        
    df = df[df.index % iterations_per_run > warmup_iterations] # Exclude warmup iterations
    df.reset_index(inplace=True, drop=True)
    df["Provider"] = provider
    df["Iteration"] = df.index
    if "_100.out" in infile:
        df["RTT (ns)"] /= 100    
    df["RTT (us)"] = df["RTT (ns)"] / 1000.0
    df["RTT (ms)"] = df["RTT (ns)"] / 1000000.0
    df["RTT/2 (ms)"] = df["RTT (ms)"] / 2.0
    df["Sleep Time (ms)"] = df["Sleep Time (ns)"] / 1000000
    df["Inter-Message Interval"] = df.apply(lambda x: sleep_time(x["Sleep Time (ns)"]), axis=1)
    df = df[~df["Inter-Message Interval"].str.contains("Post") & ~df["Inter-Message Interval"].str.contains("Skip")]
    df_global = pd.concat([df, df_global])
    df_global.reset_index(inplace=True, drop=True)

    #ax = sns.lineplot(data=df_global, x=df_global["Iteration"], y=df_global["RTT (ms)"], hue="Provider", markers=True)
    #for jj in range(1, 10):
    #    plt.axvline(jj*20) 
    ax = sns.violinplot(data=df_global, x="Inter-Message Interval", y="RTT/2 (ms)", saturation=1, ax=axes)
    ax.set_ylabel("RTT/2 (1MiB msgs)")
    patch_violinplot(sns.color_palette(), nviolins)

    ax.figure.tight_layout()
    ax.figure.savefig(filename, format='pdf', dpi=100)
    plt.clf()

def plot_noise_net_alltime(lat_or_bw, plot_type):
    # Plot network latency noise (CDF):
    #   - Y axis: CDF
    #   - X axis: Latency
    #   - hue: Time (Day vs night)
    #   - subplots: providers
    #   - Fixed instance type (HPC) and allocation (Same Rack)
    filename = 'out/paper_pre/' + lat_or_bw + '_' + plot_type + '.pdf'
    print("Plotting " + filename + " ...")
    df_global = pd.DataFrame()
    for (time_tmp, placement_tmp) in [("Day", "Same Rack"), ("Day", "Different Racks"), ("Night", "Same Rack"), ("Night", "Different Racks")]:
        if plot_type == "kde":
            rows = 2
            cols = 2
            figsize = (10,5)
        else:
            rows = 1
            cols = 1
            figsize = (5, 2.5)
        fig, axes = plt.subplots(rows, cols, figsize=figsize, sharex=True, sharey=True)
        i = 0
        hue = None
        lat_or_bw_long = ""
        if lat_or_bw == "noise_lat":
            lat_or_bw_long = "Latency (us)"
        else:
            lat_or_bw_long = "Bandwidth (Gb/s)"

        #for provider in providers:    
        for provider in ["AWS", "Azure", "Daint"]:    
            # Create sub frames
            df = load_all(lat_or_bw)
            df = filter_provider(df, provider)
            df = filter_instance(df, instance_type_t[provider])            
            df = filter_placement(df, placement_tmp)
            df = filter_time(df, time_tmp)
            df["Type"] = df["Time"] + " - " + df["Placement"]
            
            if plot_type == "kde":
                ax = axes[int(i / cols)][i % cols]
                ax.set_title(provider)
                if lat_or_bw == "noise_lat":
                    ax.set_xscale("log")
                sns.kdeplot(data=df, x=lat_or_bw_long, hue=hue, ax=ax)
            df_global = pd.concat([df, df_global])
            i += 1

    if plot_type == "kde":
        fig.legend(bbox_to_anchor=(1.3, 0.6))
    elif plot_type == "violin":
        ax = sns.violinplot(data=df_global, x="Provider", y=lat_or_bw_long, hue="Type")
        if lat_or_bw == "noise_lat":
            ax.set_yscale("log")
        fig = ax.figure
    elif plot_type == "box":
        ax = sns.boxplot(data=df_global, x="Provider", y=lat_or_bw_long, hue="Type")
        fig = ax.figure

    fig.tight_layout()
    fig.savefig(filename, format='pdf', dpi=100)
    plt.clf()

def plot_paper_uni_vs_bi():
    # Plot unidirectional vs bidirectional bandwidth:
    #   - Y axis: Bandwidth
    #   - X axis: Provider
    #   - hue: Uni- vs Bi-directional
    #   - Fixed instance type (HPC), allocation (Same Rack), and time (Day)
    filename = 'out/paper_pre/uni_vs_bi.pdf'
    print("Plotting " + filename + " ...")
    df = pd.DataFrame()
    for metric in ["unidirectional_bw", "bidirectional_bw"]:        
        handles = None
        labels = None
       
        stripes = {}
        stripes["GCP"] = 16
        stripes["AWS"] = 16
        stripes["Azure"] = 1
        stripes["Oracle"] = 1
        stripes["Daint"] = 1
        stripes["Alps"] = 1
        stripes["DEEP-EST"] = 1

        opt_msg_size_uni = {}
        opt_msg_size_uni["GCP"] = "16MiB"
        opt_msg_size_uni["AWS"] = "16MiB"
        opt_msg_size_uni["Azure"] = "16MiB"
        opt_msg_size_uni["Oracle"] = "16MiB"
        opt_msg_size_uni["Daint"] = "16MiB"
        opt_msg_size_uni["Alps"] = "16MiB"
        opt_msg_size_uni["DEEP-EST"] = "16MiB"
        
        opt_msg_size_bi = {}
        opt_msg_size_bi["GCP"] = "16MiB"
        opt_msg_size_bi["AWS"] = "16MiB"
        opt_msg_size_bi["Azure"] = "16MiB"
        opt_msg_size_bi["Oracle"] = "16MiB"
        opt_msg_size_bi["Daint"] = "16MiB"        
        opt_msg_size_bi["Alps"] = "16MiB"        
        opt_msg_size_bi["DEEP-EST"] = "16MiB"    

        for provider in providers:
            # Get data 
            if stripes[provider] == 1:
                suffix = "x1"
            else:           
                suffix = "y" + str(stripes[provider])
            dfc = load_all(metric + suffix)
            dfc = filter_instance(dfc, instance_type_t[provider])            
            dfc = filter_placement(dfc, placement_t[provider])            
            dfc = filter_time(dfc, time_t[provider])
            dfc = filter_provider(dfc, provider)            
            if "unidirectional" in metric:
                dfc = dfc[dfc["Message Size"] == opt_msg_size_uni[provider]]
                dfc["Type"] = "Unidirectional"
            else:
                dfc = dfc[dfc["Message Size"] == opt_msg_size_bi[provider]]
                dfc["Type"] = "Bidirectional"
            df = pd.concat([df, dfc])

    df.reset_index(inplace=True, drop=True)           
    fig, axes = plt.subplots(1, 1, figsize=(5, 2), sharex=True, sharey=True)
    ax = sns.violinplot(data=df, x="Provider", y="Bandwidth (Gb/s)", hue="Type", saturation=1)    
    patch_violinplot(sns.color_palette(), df["Type"].nunique())
    ax.legend_.set_title(None)
    ax.set_xlabel(None)
    fig.tight_layout()
    fig.savefig(filename, format='pdf', dpi=100)
    plt.clf()

def get_noise_single(provider, instance_type, placement, time, data_type, ax, j, kde):
    df_tmp = get_data(provider, instance_type, placement, time, data_type)
    if df_tmp is not None:
        df_tmp["Time (min)"] = (df_tmp["Sample"] / len(df_tmp)) * 60.0 # * 1e9                
        if kde:
            cut_mean = 0.0001
        else:
            cut_mean = 0.2
        if "lat" in data_type:
            df_tmp["Normalized Latency"] = df_tmp["RTT/2 (us)"] / df_tmp["RTT/2 (us)"].min()
            df_tmp["Latency (us)"] = df_tmp["RTT/2 (us)"]
            #df_tmp = df_tmp[df_tmp["Normalized Latency"] > 1 + cut_mean]
        elif "bw" in data_type:
            df_tmp["Normalized Bandwidth"] = df_tmp["Bandwidth (Gb/s)"] / df_tmp["Bandwidth (Gb/s)"].max()
            #df_tmp = df_tmp[df_tmp["Normalized Bandwidth"] < 1 - cut_mean]                                      
        df_tmp.reset_index(inplace=True, drop=True)
        
        top_net = 0.001
        top_os = 0.01
        if "lat" in data_type:
            drop_noisy_perc = .999 # Percentage of noisy samples to drop [0, 1]
            #df_dropper = df_tmp[df_tmp["Normalized Latency"] < 4]
            df_dropper = df_tmp
            drop_indices = np.random.choice(df_dropper.index, int(len(df_dropper)*drop_noisy_perc), replace=False)
            #df_tmp = df_tmp.drop(drop_indices)
            df_tmp = df_tmp.nlargest(int(len(df_tmp)*top_net), 'Normalized Latency')

            #drop_noisy_perc = .99 # Percentage of noisy samples to drop [0, 1]
            #df_dropper = df_tmp[df_tmp["Normalized Latency"] >= 4]
            #drop_indices = np.random.choice(df_dropper.index, int(len(df_dropper)*drop_noisy_perc), replace=False)
            #df_tmp = df_tmp.drop(drop_indices)
        elif "bw" in data_type:
            drop_noisy_perc = .99
            #df_dropper = df_tmp[df_tmp["Normalized Bandwidth"] > 0]
            df_dropper = df_tmp
            drop_indices = np.random.choice(df_dropper.index, int(len(df_dropper)*drop_noisy_perc), replace=False)
            #df_tmp = df_tmp.drop(drop_indices)
            df_tmp = df_tmp.nsmallest(int(len(df_tmp)*top_net), 'Normalized Bandwidth')
        else:
            drop_noisy_perc = .99
            # Drop only those < 10^2
            #df_dropper = df_tmp[df_tmp["Detour (us)"] < 100]
            df_dropper = df_tmp
            drop_indices = np.random.choice(df_dropper.index, int(len(df_dropper)*drop_noisy_perc), replace=False)
            #df_tmp = df_tmp.drop(drop_indices)
            df_tmp = df_tmp.nlargest(int(len(df_tmp)*top_os), 'Detour (us)')
        
        #if not "os" in data_type and not kde:
        #    ax.axhline(mean, color=sns.color_palette()[j])
    return df_tmp

def plot_paper_noise_long_instance_type(data_type, data_type_human):
    kde = False
    if kde:
        filename = 'out/paper_pre/' + data_type + '_instance_type_long_kde.pdf'
    else:
        filename = 'out/paper_pre/' + data_type + '_instance_type_long.pdf'
    print("Plotting " + filename + " ...")   
    if "os" in data_type: 
        #rows = 3
        #cols = 3
        #fig, axes = plt.subplots(rows, cols, figsize=(8, 6), sharex=True, sharey=True)
        fig = plt.figure(constrained_layout=True, figsize=(9,4))
        gs0 = fig.add_gridspec(2, 1)

        gs00 = gs0[0].subgridspec(1, 4)
        gs01 = gs0[1].subgridspec(1, 3)

        for a in range(1):
            for b in range(4):
                fig.add_subplot(gs00[a, b])
        for a in range(1):
            for b in range(3):
                fig.add_subplot(gs01[a, b])
        axes = fig.get_axes()
    else:
        rows = 1
        cols = 4
        fig, axes = plt.subplots(rows, cols, figsize=(8, 2.5), sharex=True, sharey=True)
    if "os" in data_type:
        x_col = "Time (s)"
    else:
        x_col = "Time (min)"
    i = 0
    palette_dict = {}
    legend_elements = []
    markers = {"Normal" : 'o', "HPC" : 'D', "HPC (Metal)" : 's', "HPC (200 Gb/s)" : '^'}
    for instance in instances:
        palette_dict[instance] = sns.color_palette()[i]
        legend_elements += [Line2D([0], [0], marker=markers[instance], lw=0, color=sns.color_palette()[i], label=instance)]
        i += 1
    i = 0
    providers_iterate = providers
    if not "os" in data_type:
        providers_iterate = ["AWS", "Azure", "GCP", "Oracle"]
    for provider in providers_iterate:
        df = pd.DataFrame()
        j = 0
        if "os" in data_type:
            ax = axes[i]
        else:
            ax = axes[i]
        ax.set_title(provider)
        for instance in instances:                
            df_tmp = get_noise_single(provider, instance, placement_t[provider], time_t[provider], data_type, ax, j, kde)
            if df_tmp is not None:
                df = pd.concat([df, df_tmp])
            j += 1
        if len(df):            
            df.reset_index(inplace=True, drop=True)
            df = df.reindex(np.random.permutation(df.index)) # To improve overlapping issues
            if kde:
                ax = sns.kdeplot(data=df, x=data_type_human, hue="Instance", palette=palette_dict, ax=ax)    
            else:
                ax = sns.scatterplot(data=df, x=x_col, y=data_type_human, hue="Instance", style="Instance", \
                                     palette=palette_dict, markers=markers, ax=ax, linewidth=0, s=30) #, s=15)    
                if "lat" in data_type:
                    ax.set_yscale("log")
                    ys = [2,8,32,128,512,2048]
                    ax.set(yticks=ys, yticklabels=ys)
                    ax.set(ylim=(1, 512))
            if data_type == "os_noise":                
                ax.set_yscale("log")
                ax.set(ylim=(10,1000), xlim=(0,5), xticks=[0,1,2,3,4,5], xticklabels=[0,1,2,3,4,5])
                if i != 0 and i != 4:
                    ax.set_ylabel(None)
                    ax.set(yticklabels=[])
            if "bw" in data_type:
                ax.set(ylim=(0, 1))
            ax.get_legend().remove()
        i += 1
    if "os" in data_type:
        fig.legend(handles=legend_elements, bbox_to_anchor=(.8, 1), ncol=len(instances), title=None)
    else:
        fig.legend(handles=legend_elements, bbox_to_anchor=(.87, 1), ncol=len(instances), title=None)
    plt.tight_layout()
    if "os" in data_type:
        plt.subplots_adjust(top=0.83)
    else:
        plt.subplots_adjust(top=0.78)
    fig.savefig(filename, format='pdf', dpi=100)
    plt.clf()



def plot_paper_noise_long_time_alloc(data_type, data_type_human):
    kde = False
    if kde:
        filename = 'out/paper_pre/' + data_type + '_time_alloc_long_kde.pdf'
    else:
        filename = 'out/paper_pre/' + data_type + '_time_alloc_long.pdf'    
    print("Plotting " + filename + " ...")    
    rows = 1
    cols = 2
    fig, axes = plt.subplots(rows, cols, figsize=(8,2.5), sharex=True, sharey=True)
    if "os" in data_type:
        x_col = "Time (min)"
    else:
        x_col = "Time (min)"
    i = 0
    palette_dict = {}
    legend_elements = []
    markers = {"GCP" : 'o', "AWS" : 'D', "Daint" : 's', "Azure" : '^', "Alps" : "P", "DEEP-EST" : 'X', "Oracle" : 'p'}
    for provider in providers:
        palette_dict[provider] = sns.color_palette()[i]    
        legend_elements += [Line2D([0], [0], marker=markers[provider], lw=0, color=sns.color_palette()[i], label=provider)]
        i += 1
    i = 0
    for placement in ["Same Rack", "Different Racks"]:
        for time in ["Day"]:
            df = pd.DataFrame()
            j = 0
            #ax = axes[int(i / cols)][i % cols]
            ax = axes[i]
            ax.set_title(placement)
            for provider in [ "GCP", "AWS", "Daint", "DEEP-EST", "Azure", "Alps", "Oracle"]:
                df_tmp = get_noise_single(provider, instance_type_t[provider], placement, time, data_type, ax, j, kde)
                if df_tmp is not None:
                    df = pd.concat([df, df_tmp])
                j += 1            
            df.reset_index(inplace=True, drop=True)
            df = df.reindex(np.random.permutation(df.index)) # To improve overlapping issues
            if kde:
                ax = sns.kdeplot(data=df, x=data_type_human, hue="Provider", palette=palette_dict, ax=ax)    
            else:       
                ax = sns.scatterplot(data=df, x=x_col, y=data_type_human, hue="Provider", style="Provider", \
                                     palette=palette_dict, markers=markers, ax=ax, linewidth=0, s=20)#, s=15)    
                if "lat" in data_type:               
                    ax.set_yscale("log")     
                    ys = [2,8,32,128,512,2048]
                    ax.set(yticks=ys, yticklabels=ys)                    
                    ax.set(ylim=(1, 512))
            ax.get_legend().remove()
            i += 1
    fig.legend(handles=legend_elements, bbox_to_anchor=(.98, 1), ncol=len(providers), title=None)
    plt.tight_layout()
    plt.subplots_adjust(top=0.75)
    fig.savefig(filename, format='pdf', dpi=100)
    plt.clf()

def plot_logGP():
    filename = 'out/paper_pre/logGP.pdf'    
    
    provider = "DEEP-EST"
    instance = "HPC (Metal)"
    placement = "Same Rack"
    suffix = "x1"

    if suffix == "x1":
        starti = 0
    elif suffix == "y2":
        starti = 1
    elif suffix == "y16":
        starti = 4
    else:
        sys.exit("Unknown suffix.")

    print("Plotting " + filename + " ...")  
    metric = "unidirectional_bw" 
    df = load_all(metric + suffix)
    df = filter_placement(df, placement)
    df = filter_time(df, "Day")
    df = filter_instance(df, instance)
    df = filter_provider(df, provider)
    df["SimOrReal"] = "Real"

    loggp_us = []
    loggp_bw = []
    msg_sizes = []
    msg_sizes_h = []
    for i in range(starti, 25):
        msg_size = 2**i
        msg_sizes += [msg_size]
        msg_sizes_h += [hr_size(msg_size)]
        (L, o, g, G, S) = get_loggp_params(provider, instance, suffix, placement)
        
        if msg_size <= S:   
            us = 2*o + L + (msg_size - 1)*G
        else:
            us = 2*o + 3*L + (msg_size - 1)*G
        loggp_us += [us]
        loggp_bw += [(msg_size*8) / (us*1000)]

    loggp = {}    
    loggp["RTT/2 (us)"] = loggp_us    
    loggp["Message Size"] = msg_sizes_h
    loggp["Bandwidth (Gb/s)"] = loggp_bw
    loggp["SimOrReal"] = "Sim"
    df = pd.concat([df, pd.DataFrame.from_dict(loggp)])
    df.reset_index(inplace=True, drop=True)

    fig, axes = plt.subplots(1, 1, figsize=(5,2.5), sharex=True, sharey=True)
    innerxlim=(0, 20)
    innerylim=None
    if provider == "Azure":
        innerylim=(0, 50)
    else:
        innerylim=(0, 30)
    #ylim=(0,100)
    ylim=None
    innerpars = [0.1, 0.5, 0.45, 0.45]
    innerpars_dt = "RTT/2 (us)"
    plot_size_vs_lat_bw(df, axes, metric, metric_human[metric], "SimOrReal", None, xlim=None, ylim=ylim, innerpars_dt=innerpars_dt, innerpars=innerpars, innerxlim=innerxlim, innerylim=innerylim)
    #fig.legend(handles=legend_elements, bbox_to_anchor=(.75, 1), ncol=len(instances), title=None)
    plt.tight_layout()
    plt.subplots_adjust(top=0.85)
    fig.savefig(filename, format='pdf', dpi=100)
    plt.clf()

def main():         
    parser = argparse.ArgumentParser(description='Plots data.')
    parser.add_argument('--full', help='Plots all the data. If false, plots only the data shown in the paper.', default=False)
    args = parser.parse_args()   

    # Load paths
    with open("../data/description.csv", mode='r') as infile:
        reader = csv.reader(infile)    
        global paths
        paths = {(rows[0],rows[1],rows[2],rows[3]):"../data/" + rows[4] for rows in reader}

    if args.full:
        plot_noise("noise_lat", "Latency (us)")
        plot_noise("noise_bw", "Bandwidth (Gb/s)")
        plot_noise("os_noise", "Detour (us)")
        plot_noise_long("noise_lat", "Latency (us)")
        plot_noise_long("noise_bw", "Bandwidth (Gb/s)")    
        plot_noise_long("os_noise", "Detour (us)")    

        for metric in ["unidirectional_lat", "unidirectional_bw", "bidirectional_lat", "bidirectional_bw"]:
            plot_lat_bw(metric, metric_human[metric], "any", "any")
            if "unidirectional" in metric:
                for what in ["stripe", "conc"]:
                    plot_lat_bw_conc(metric, metric_human[metric], "any", "any", "any", what)

        for time in times:
            for placement in placements:
                plot_lat_bw("unidirectional_lat", "RTT/2 (us)", time, placement)    
                plot_lat_bw("unidirectional_bw", "Bandwidth (Gb/s)", time, placement)
                plot_lat_bw("bidirectional_lat", "RTT/2 (us)", time, placement)    
                plot_lat_bw("bidirectional_bw", "Bandwidth (Gb/s)", time, placement)
                for instance_type in instances:
                    plot_lat_bw_conc("unidirectional_lat", "RTT/2 (us)", time, placement, instance_type, "conc")    
                    plot_lat_bw_conc("unidirectional_bw", "Bandwidth (Gb/s)", time, placement, instance_type, "conc")
                    plot_lat_bw_conc("unidirectional_lat", "RTT/2 (us)", time, placement, instance_type, "stripe")    
                    plot_lat_bw_conc("unidirectional_bw", "Bandwidth (Gb/s)", time, placement, instance_type, "stripe")
                    #plot_lat_bw_sw("unidirectional_lat", "RTT/2 (us)", time, placement, instance_type)
                    #plot_lat_bw_sw("unidirectional_bw", "Bandwidth (Gb/s)", time, placement, instance_type)                
    else:
        #plot_noise_long("noise_lat", "Latency (us)")
        #plot_noise_long("noise_bw", "Bandwidth (Gb/s)")            
        #for bol in ["noise_bw", "noise_lat"]:
        #    plot_noise_net_alltime(bol, "violin")
        #    #plot_noise_net_alltime(bol, "box")        
        #plot_paper_netnoise()                
        #plot_paper_noise_long_time_alloc("os_noise", "Detour (us)") # OK but not shown in the paper


        # Plots used in the paper     
        #for provider in ["AWS", "Azure", "GCP", "Oracle"]:
        #    plot_paper_hoverboard(provider) # OK        
        plot_paper_noise_long_instance_type("os_noise", "Detour (us)") # OK        
        plot_paper_noise_long_time_alloc("noise_bw", "Normalized Bandwidth") # OK                
        plot_paper_noise_long_instance_type("noise_bw", "Normalized Bandwidth") # OK                
        plot_paper_striping("stripe") # OK        
        plot_paper_striping("conc") # OK
        plot_paper_lat_bw_instances("unidirectional_bw") # OK
        plot_paper_uni_vs_bi() # OK
        plot_paper_noise_long_time_alloc("noise_lat", "Normalized Latency") # OK 
        plot_paper_noise_long_instance_type("noise_lat", "Normalized Latency") # OK        
        plot_paper_lat_bw() # OK
        #plot_logGP()
        #plot_paper_noise_long_time_alloc("noise_lat", "Latency (us)") 
        #plot_paper_noise_long_time_alloc("noise_bw", "Bandwidth (Gb/s)")

if __name__ == "__main__":
    main()


# Notes
# - osu_bw on GCP HPC instances:
#   # OSU MPI Bandwidth Test v5.9
#   # Size      Bandwidth (MB/s)
#   1                       0.68
#   2                       1.37
#   4                       2.77
#   8                       5.61
#   16                     11.72
#   32                     21.07
#   64                     42.99
#   128                    83.94
#   256                   148.56
#   512                   218.05
#   1024                  275.57
#   2048                  481.64
#   4096                  849.27
#   8192                 1331.90
#   16384                1899.97
#   32768                2493.93
#   65536                2851.43
#   131072               3441.27
#   262144               3988.36
#   524288               4235.09
#   1048576              4106.00
#   2097152              3865.17
#   4194304              3934.70
#
# - osu_bw on Azure Normal instances:
#   ## OSU MPI Bandwidth Test v5.9
#   # Size      Bandwidth (MB/s)
#   1                       0.31
#   2                       0.64
#   4                       1.26
#   8                       2.59
#   16                      5.13
#   32                     10.32
#   64                     19.55
#   128                    40.51
#   256                    79.75
#   512                   144.95
#   1024                  251.17
#   2048                  437.43
#   4096                  551.49
#   8192                 1302.09
#   16384                1851.28
#   32768                1966.13
#   65536                1858.07
#   131072               2494.07
#   262144               2110.88
#   524288               2256.79
#   1048576              3276.07
#   2097152              3298.61
#   4194304              3298.61