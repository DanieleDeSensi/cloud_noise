export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib64/mpich-3.2/lib/
export PATH=$PATH:/usr/lib64/mpich-3.2/bin/
MPIRUN="mpirun" # Command for running MPI applications
MPIRUN_MAP_BY_NODE_FLAG="-bind-to core" # Flag to force ranks to be mapped by node
MPIRUN_HOSTFILE_FLAG="" # Flag for specifying the hostfile (2 hosts)
MPIRUN_HOSTFILE_LONG_FLAG="" # Flag for specifying the hostfile (16 hosts)
MPIRUN_ADDITIONAL_FLAGS=""    # Any additional flag that must be used by mpirun
INTERFACE_MASK="10.0.0.0/24" # Interface address + mask size of the two nodes
RUN_IB=true # Shall we run IB tests?
RUN_IBV=true # Shall we run IBV tests?
NET_NOISE_CONC=16 # How many concurrent connections to run to measure bandwidth network noise
BW_SATURATING_SIZE=16777216 # How many bytes to send to get max bw
MPI_COMPILER=mpicc # MPI Compiler
NG_CONFIGURE_FLAGS="HRT_ARCH=6 LDFLAGS=-pthread"
