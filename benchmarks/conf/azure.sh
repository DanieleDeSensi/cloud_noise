MPIRUN="mpirun" # Command for running MPI applications
MPIRUN_MAP_BY_NODE_FLAG="--map-by node" # Flag to force ranks to be mapped by node
MPIRUN_HOSTFILE_FLAG="--hostfile conf/azure_hostfile" # Flag for specifying the hostfile (2 hosts)
MPIRUN_HOSTFILE_LONG_FLAG="--hostfile conf/azure_hostfile_long" # Flag for specifying the hostfile (16 hosts)
MPIRUN_ADDITIONAL_FLAGS="-x LD_LIBRARY_PATH=/opt/gcc-9.2.0/lib64"    # Any additional flag that must be used by mpirun
INTERFACE_MASK="10.0.0.0/24" # Interface address + mask size of the two nodes
RUN_IB=true # Shall we run IB tests?
RUN_IBV=true # Shall we run IBV tests?
NET_NOISE_CONC=1 # How many concurrent connections to run to measure bandwidth network noise
BW_SATURATING_SIZE=16777216 # How many bytes to send to get max bw
MPI_COMPILER=mpicc # MPI Compiler
NG_CONFIGURE_FLAGS="HRT_ARCH=6"