MPIRUN="mpirun" # Command for running MPI applications
MPIRUN_MAP_BY_NODE_FLAG="-perhost 1" # Flag to force ranks to be mapped by node
MPIRUN_HOSTFILE_FLAG="--hostfile conf/gcp_hostfile" # Flag for specifying the hostfile
MPIRUN_HOSTFILE_LONG_FLAG="--hostfile conf/gcp_hostfile_long"
MPIRUN_ADDITIONAL_FLAGS=""    # Any additional flag that must be used by mpirun
INTERFACE_MASK="10.142.0.0/24" # Interface address + mask size of the two nodes
RUN_IB=false # Shall we run IB tests?
RUN_IBV=false # Shall we run IBV tests?
NET_NOISE_CONC=8 # How many concurrent connections to run to measure bandwidth network noise
BW_SATURATING_SIZE=4194304  # How many bytes to send to get max bw
MPI_COMPILER="mpicc" # MPI Compiler
NG_CONFIGURE_FLAGS="HRT_ARCH=6"
export I_MPI_PIN=on 
