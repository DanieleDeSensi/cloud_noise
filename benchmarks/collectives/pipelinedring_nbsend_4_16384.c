#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#define add_time(now, expected, s, ns){expected.tv_sec = now.tv_sec + add_s; expected.tv_nsec = now.tv_nsec + add_ns;}
#define cmp_time_leq(time1, time2) (time1.tv_sec < time2.tv_sec ? 1 : (time1.tv_sec == time2.tv_sec && time1.tv_nsec < time2.tv_nsec ? 1 : 0))
void my_nanosleep(int sleep_time_ns){
    long add_s, add_ns, measured_time;
    struct timespec now, expected;
    // busy waiting
    if (sleep_time_ns >= 1e9){
        add_s = sleep_time_ns / 1e9;
        add_ns = (long)sleep_time_ns % (long)1e9;
    }else{
        add_s = 0;
        add_ns = sleep_time_ns;
    }

    clock_gettime(CLOCK_REALTIME, &now);
    add_time(now, expected, add_s, add_ns);
    while (cmp_time_leq(now, expected)){
        clock_gettime(CLOCK_REALTIME, &now);
    }
}
int main(int argc, char** argv){
    char* buffer = (char*) malloc(sizeof(char)*16384);
    double* samples = (double*) malloc(sizeof(double)*10000);
    double* samples_all;
    long i, r;
    MPI_Init(&argc, &argv);
    int rank, comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank == 0){
        samples_all = (double*) malloc(sizeof(double)*comm_size*10000);
    }
    for(i = -10; i < 10000; i++){
        usleep(1);
        switch(rank){
        case 0:{
        MPI_Request mpi_reqs[9];
        int flags[9];
        int completed[9];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 4096, MPI_BYTE, 3, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 4096, MPI_BYTE, 3, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 4096, MPI_BYTE, 3, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 4096, MPI_BYTE, 3, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Isend(buffer, 4096, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        do{
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 4096, MPI_BYTE, 1, 1, MPI_COMM_WORLD, &(mpi_reqs[4]));
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 4096, MPI_BYTE, 1, 2, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 4096, MPI_BYTE, 1, 3, MPI_COMM_WORLD, &(mpi_reqs[8]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[7]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[4]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 1:{
        MPI_Request mpi_reqs[9];
        int flags[9];
        int completed[9];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 4096, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 4096, MPI_BYTE, 0, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 4096, MPI_BYTE, 0, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 4096, MPI_BYTE, 0, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Isend(buffer, 4096, MPI_BYTE, 2, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        do{
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 4096, MPI_BYTE, 2, 1, MPI_COMM_WORLD, &(mpi_reqs[4]));
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 4096, MPI_BYTE, 2, 2, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 4096, MPI_BYTE, 2, 3, MPI_COMM_WORLD, &(mpi_reqs[8]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[7]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[4]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 2:{
        MPI_Request mpi_reqs[9];
        int flags[9];
        int completed[9];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 4096, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 4096, MPI_BYTE, 1, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 4096, MPI_BYTE, 1, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 4096, MPI_BYTE, 1, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Isend(buffer, 4096, MPI_BYTE, 3, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        do{
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 4096, MPI_BYTE, 3, 1, MPI_COMM_WORLD, &(mpi_reqs[4]));
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 4096, MPI_BYTE, 3, 2, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 4096, MPI_BYTE, 3, 3, MPI_COMM_WORLD, &(mpi_reqs[8]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[7]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[4]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 3:{
        MPI_Request mpi_reqs[9];
        int flags[9];
        int completed[9];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 4096, MPI_BYTE, 2, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 4096, MPI_BYTE, 2, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 4096, MPI_BYTE, 2, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 4096, MPI_BYTE, 2, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Isend(buffer, 4096, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        do{
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 4096, MPI_BYTE, 0, 1, MPI_COMM_WORLD, &(mpi_reqs[4]));
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 4096, MPI_BYTE, 0, 2, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 4096, MPI_BYTE, 0, 3, MPI_COMM_WORLD, &(mpi_reqs[8]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[7]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[4]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        }
    }
    MPI_Gather(samples, 10000, MPI_DOUBLE, samples_all, 10000, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    if(rank == 0){
        printf("#MessageSize ");
        for(r = 0; r < comm_size; r++){
            printf("Rank%ldTime(us) ", r);
        }
        printf("\n");
        for(i = 0; i < 10000; i++){
            printf("%d ", 16384);
            for(r = 0; r < comm_size; r++){
               printf("%f ", samples_all[r*10000 + i]);
            }
            printf("\n");
        }
    }
    MPI_Finalize();
    return 0;
}
