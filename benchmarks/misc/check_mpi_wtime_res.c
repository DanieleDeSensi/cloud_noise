#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv){
  MPI_Init(&argc, &argv);
    double res_nsec = MPI_Wtick()*1000000000;
    printf("MPI_Wtime resolution is %f nanoseconds.\n", res_nsec);
    MPI_Finalize();
    return 0;
}
