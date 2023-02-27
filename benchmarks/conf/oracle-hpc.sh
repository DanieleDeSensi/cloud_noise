module load hpcx/hpcx-ompi
MPIRUN="mpirun" # Command for running MPI applications
MPIRUN_MAP_BY_NODE_FLAG="--map-by node" # Flag to force ranks to be mapped by node
MPIRUN_HOSTFILE_FLAG="" # Flag for specifying the hostfile (2 hosts)
MPIRUN_HOSTFILE_LONG_FLAG="" # Flag for specifying the hostfile (16 hosts)
MPIRUN_ADDITIONAL_FLAGS="-mca pml ucx -x UCX_NET_DEVICES=mlx5_2:1 -x UCX_IB_TRAFFIC_CLASS=105 -x UCX_IB_GID_INDEX=3 -x HCOLL_ENABLE_MCAST_ALL=0 -x coll_hcoll_enable=0"    # Any additional flag that must be used by mpirun
INTERFACE_MASK="10.0.0.0/24" # Interface address + mask size of the two nodes
RUN_IB=true # Shall we run IB tests?
RUN_IBV=true # Shall we run IBV tests?
NET_NOISE_CONC=16 # How many concurrent connections to run to measure bandwidth network noise
BW_SATURATING_SIZE=16777216 # How many bytes to send to get max bw
MPI_COMPILER=mpicc # MPI Compiler
NG_CONFIGURE_FLAGS="HRT_ARCH=6 LDFLAGS=-pthread"
