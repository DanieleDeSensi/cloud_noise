# Introduction
This repository contains instructions on how to reproduce the results in the paper:

*Noise in the Clouds: Influence of Network Performance Variability on Application Scalability*
by Daniele De Sensi, Tiziano De Matteis, Konstantin Taranov, Salvatore Di Girolamo, Tobias Rahn, Torsten Hoefler
In *Proceedings of the ACM on Measurement and Analysis of Computing Systems, Volume 6, Issue 3*
https://arxiv.org/abs/2210.15315
 
It is composed by three main parts, each discussed in a different section of this document:
1. The benchmarks to be run on the real systems to gather performance and noise data 
   (`benchmarks` folder, [Benchmarks](#benchmarks) section).
2. The code that simulates performance at scale (`simulations` folder, [Simulations](#simulations) section).
3. The scripts for plotting all the figures in the paper (`plots` folder, [Plots](#plots) section).

The first part ([Benchmarks](#benchmarks)) is not supposed to be run in a container, to avoid performance variability 
introduced by the container (e.g., see: https://arxiv.org/pdf/1708.01388.pdf).
For the last two parts a container is provided instead.

In the following, all the commands assume you are in the root of the repository.

# Benchmarks
This section describes how to run the benchmarks to collect performance and noise data.
The following steps are supposed to be executed on the compute nodes of each different 
cloud provider, for each of the different instance types. For creating a small cluster 
on each of the cloud providers, please refer to the documentation of each of those. 
Information on the instance types we used can be found in Table 1 of the paper. 

**If for any reason it is not possible to get access to some of those systems, download 
and decompress the artifact containing the data we already collected (the process will take 
around 10 minutes). To do so:**

1. Install `xz-utils`. E.g., on Ubuntu:
```
$ sudo apt-get install xz-utils
```

2. Download and decompress the data:
```
$ pushd data
$ ./get_data.sh
$ popd
```

Then, any data you collect in the following steps will ovewrite the downloaded data.
E.g., if you only have access to GCP, the data you collect for GCP will ovewrite
the downloaded GCP data. The scripts will use for GCP the data you collected,
and for the other systems the downloaded data.

## System configuration
We here provide some detailed information on how we created the clusters
on each of the providers. Detailed information on OS and MPI versions used 
can be found in the paper.

### Azure
Clusters have been created by using the *Azure CycleCloud* tool (`v8.2` in our experiments).  
We host this tool on a general-purpose VM (having at least 2 vCPUs and 8 GB of RAM).
Then, we created a cluster managed with Slurm. Please note that you need to have enough 
compute quota to create the cluster (check in `Azure -> Quota`). At the cluster startup, 
the schedule node is created. The user can ssh into it and allocate nodes (by using 
`salloc`) and launch experiments.

### AWS
Clusters have been created by using the *AWS ParallelCluster* tool (`v3`). We enabled 
EFA for 100 Gb/s instances. We used a `t2.micro` instance as the head node, and 
allocated the compute nodes with Slurm. Please note that you need to have enough 
compute quota to create the cluster.

### GCP
All virtual machines (VMs) have been created by using the beta *Google Cloud SDK* 
(`v377.0.0` in our experiments). To enable 100 Gb/s networking between VMs, 
they have been deployed with `TIER1` bandwidth configuration, Google virtual NIC 
(gVNIC) network driver, and gVNIC-compatible OS (we used `hpc-centos-7` image from the 
`cloud-hpc-image-public` project). Please note that you need to have enough global and 
region compute quotas to create the VMs (check in `GCP -> Quotas`).

### Daint
Tests have been executed with the `mc` constraint (`-C mc` in Slurm) using the default 
system configuration.

### Alps
Tests have been executed with the `mc` constraint (`-C mc` in Slurm) using the default 
system configuration.

### DEEP-EST
Tests have been executed on the `cluster` partition (`-p dp-cn`) using the default system
configuration.

## Preparation
1. Install `coreutils`. E.g., on Ubuntu:
```
$ sudo apt-get install coreutils
```

2. Install/load MPI. We used the MPI libraries suggested by each provider.
Specifically:
- On Azure: HPC-X v2.8.3 on HPC instances, OpenMPI v4.1.2 on normal instances
- On AWS: OpenMPI v4.1.1
- On GCP: IntelMPI v2018.4.274
- On Oracle: MPICH v3.2
- On Daint: Cray MPICH v7.7.18
- On Alps: Cray MPICH v8.1.12
- On DEEP-EST: OpenMPI v4.1.3

3. Set the variable `SYSTEM` in the file `./benchmarks/conf.sh` to the name of 
the system (one of `aws-hpc`/`aws-normal`/`gcp`/`azure`/`daint`/`alps`/`deep-est`).

4. If needed (e.g., Slurm is not used), modify the MPI hostnames 
file `./benchmarks/conf/${SYSTEM}_hostfile`  (ATTENTION: please specify 
only two nodes, with 16 slots each!).

5. If on Intel systems, install the Intel C compiler `icc`. If for any reason you 
cannot install `icc`, have a look at the instructions in `./benchmarks/gemm/Makefile` 
on how to switch from `icc` to `gcc`.

6. Install the MKL (Math Kernel Library) library if on an Intel system, 
or the BLISS library if on an ADM system. Please refer to the respective manuals
for information on how to install those.

## Compile the code
To compile the code:
```
$ pushd benchmarks/
$ ./compile.sh
$ popd
```

Please check very carefully any error message print by the script at the end of
the execution.

## Run the code
To run the benchmarks:

1. Get an allocation with two nodes and 16 tasks per node. E.g., on Slurm:
```
$ salloc --ntasks-per-node 16 -N 2
```

2. Run the point to point benchmarks (it should take around 90 minutes):
```
$ pushd benchmarks/
$ ./run.sh -k "X,Y,Same Rack,Z"
$ popd
```

Where:
- X is the system. One among `AWS`, `GCP`, `Azure`, `Daint`, `Alps`, `DEEP-EST`.
- Y is the instance type. One among `Normal` (for normal instances), `HPC` (for HPC non bare metal instances), 
`HPC (Metal)` (for HPC bare metal instances), `HPC (200 Gb/s)` (for HPC 200 Gb/s instances).
- Z is the local time of the system. One among `Day`, `Night`. In the paper we consider 5pm as day, and 5am as night.

This will generate a `.tar.xz` archive in the `./data/${SYSTEM}/${TIMESTAMP}` folder containing the measured data.
An entry will be added to the `./data/description.csv` file associating the generated data with the value specified
in the `-k` flag of the `run.sh` script.

Ideally this should be run once at day and once at night for each provider and instance type.

3. If running on Azure 100 Gb/s HPC instances, run the collective benchmarks:
```
$ pushd benchmarks/
$ ./run_collectives.sh -k "Azure,HPC (Metal),Collectives,"
$ popd
```

# Simulations
In this section we describe how to simulate performance at scale starting from the data collected
in the [benchmarks](#benchmarks) phase. 

We provide a container for running simulations and for plotting the results. For building and running it, 
please run the following commands:
```
$ docker build -t cloud_noise/cloud_noise:v0.1 .
$ docker run -it --rm --name=cloud_noise --hostname=cloud_noise --mount type=bind,source=${PWD},target=/home/user/cloud_noise cloud_noise/cloud_noise:v0.1 bash
```

Now you can compile and run the simulations. Running
the simulations takes a few hours. If you want to reduce the number
of samples collected for each experiment (`1000` by default), please
modify the `TESTS` variable in the `cloud_noise/simulations/simulate.py` 
script. It is worth remarking that lowering the number of samples might lead
to slightly different results compared to those reported in the paper (due 
to the higher variability).
To compile and run the simulations:
```
user@cloud_noise:~$ pushd cloud_noise/simulations
user@cloud_noise:~$ ./compile.sh
user@cloud_noise:~$ ./run.sh
user@cloud_noise:~$ popd
```

# Plots
In this section we describe how to reproduce the plots shown in the paper starting
from the data collected in the [benchmarks](#benchmarks) and [simulations](#simulations)
phases. 

After running the container, run:
```
user@cloud_noise:~$ pushd cloud_noise/plots
user@cloud_noise:~$ ./run.sh
user@cloud_noise:~$ popd
```

The plots will be generated in the `cloud_noise/plots/out/paper/` folder.