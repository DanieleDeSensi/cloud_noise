MPIRUN="srun" # Command for running MPI applications
MPIRUN_MAP_BY_NODE_FLAG="-m plane=1" # Flag to force ranks to be mapped by node (srun)
MPIRUN_HOSTFILE_FLAG="" # Flag for specifying the hostfile
MPIRUN_HOSTFILE_LONG_FLAG="" # Flag for specifying the hostfile (16 hosts)
MPIRUN_ADDITIONAL_FLAGS=""    # Any additional flag that must be used by mpirun
INTERFACE_MASK="148.187.36.181/19" # Interface address + mask size of the two nodes
RUN_IB=false # Shall we run IB tests?
RUN_IBV=false # Shall we run IBV tests?
NET_NOISE_CONC=1 # How many concurrent connections to run to measure bandwidth network noise
BW_SATURATING_SIZE=16777216 # How many bytes to send to get max bw
MPI_COMPILER=mpicc # MPI Compiler
NG_CONFIGURE_FLAGS="HRT_ARCH=6"

module load intel-para/2021
export LD_LIBRARY_PATH=/usr/lib64:$LD_LIBRARY_PATH
export GOMP_CPU_AFFINITY="0-23"
module load mpi-settings/plain
