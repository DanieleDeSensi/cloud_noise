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
    char* buffer = (char*) malloc(sizeof(char)*16);
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
        MPI_Request mpi_reqs[33];
        int flags[33];
        int completed[33];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 1, MPI_BYTE, 15, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 15, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 15, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 15, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 15, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 15, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 15, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 15, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 15, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 15, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 15, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 15, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 15, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 15, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 15, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 15, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Send(buffer, 1, MPI_BYTE, 1, 0, MPI_COMM_WORLD);
        do{
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 1, 1, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 1, 2, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 1, 3, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[7]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 1, 4, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 1, 5, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 1, 6, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[13]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 1, 7, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[15]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 1, 8, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[17]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 1, 9, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[19]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 1, 10, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[21]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 1, 11, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[23]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 1, 12, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[25]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 1, 13, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[27]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 1, 14, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[29]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 1, 15, MPI_COMM_WORLD);
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[31]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 1:{
        MPI_Request mpi_reqs[33];
        int flags[33];
        int completed[33];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 1, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 0, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 0, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 0, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 0, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 0, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 0, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 0, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 0, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 0, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 0, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 0, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 0, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 0, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 0, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 0, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Send(buffer, 1, MPI_BYTE, 2, 0, MPI_COMM_WORLD);
        do{
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 2, 1, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 2, 2, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 2, 3, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[7]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 2, 4, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 2, 5, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 2, 6, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[13]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 2, 7, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[15]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 2, 8, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[17]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 2, 9, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[19]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 2, 10, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[21]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 2, 11, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[23]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 2, 12, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[25]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 2, 13, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[27]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 2, 14, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[29]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 2, 15, MPI_COMM_WORLD);
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[31]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 2:{
        MPI_Request mpi_reqs[33];
        int flags[33];
        int completed[33];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 1, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 1, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 1, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 1, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 1, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 1, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 1, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 1, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 1, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 1, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 1, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 1, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 1, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 1, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 1, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 1, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Send(buffer, 1, MPI_BYTE, 3, 0, MPI_COMM_WORLD);
        do{
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 3, 1, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 3, 2, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 3, 3, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[7]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 3, 4, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 3, 5, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 3, 6, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[13]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 3, 7, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[15]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 3, 8, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[17]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 3, 9, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[19]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 3, 10, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[21]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 3, 11, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[23]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 3, 12, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[25]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 3, 13, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[27]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 3, 14, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[29]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 3, 15, MPI_COMM_WORLD);
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[31]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 3:{
        MPI_Request mpi_reqs[33];
        int flags[33];
        int completed[33];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 1, MPI_BYTE, 2, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 2, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 2, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 2, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 2, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 2, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 2, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 2, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 2, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 2, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 2, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 2, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 2, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 2, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 2, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 2, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Send(buffer, 1, MPI_BYTE, 4, 0, MPI_COMM_WORLD);
        do{
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 4, 1, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 4, 2, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 4, 3, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[7]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 4, 4, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 4, 5, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 4, 6, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[13]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 4, 7, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[15]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 4, 8, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[17]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 4, 9, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[19]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 4, 10, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[21]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 4, 11, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[23]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 4, 12, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[25]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 4, 13, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[27]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 4, 14, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[29]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 4, 15, MPI_COMM_WORLD);
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[31]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 4:{
        MPI_Request mpi_reqs[33];
        int flags[33];
        int completed[33];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 1, MPI_BYTE, 3, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 3, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 3, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 3, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 3, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 3, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 3, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 3, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 3, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 3, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 3, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 3, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 3, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 3, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 3, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 3, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Send(buffer, 1, MPI_BYTE, 5, 0, MPI_COMM_WORLD);
        do{
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 5, 1, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 5, 2, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 5, 3, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[7]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 5, 4, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 5, 5, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 5, 6, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[13]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 5, 7, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[15]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 5, 8, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[17]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 5, 9, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[19]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 5, 10, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[21]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 5, 11, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[23]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 5, 12, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[25]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 5, 13, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[27]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 5, 14, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[29]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 5, 15, MPI_COMM_WORLD);
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[31]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 5:{
        MPI_Request mpi_reqs[33];
        int flags[33];
        int completed[33];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 1, MPI_BYTE, 4, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 4, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 4, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 4, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 4, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 4, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 4, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 4, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 4, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 4, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 4, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 4, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 4, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 4, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 4, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 4, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Send(buffer, 1, MPI_BYTE, 6, 0, MPI_COMM_WORLD);
        do{
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 6, 1, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 6, 2, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 6, 3, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[7]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 6, 4, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 6, 5, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 6, 6, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[13]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 6, 7, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[15]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 6, 8, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[17]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 6, 9, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[19]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 6, 10, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[21]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 6, 11, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[23]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 6, 12, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[25]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 6, 13, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[27]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 6, 14, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[29]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 6, 15, MPI_COMM_WORLD);
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[31]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 6:{
        MPI_Request mpi_reqs[33];
        int flags[33];
        int completed[33];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 1, MPI_BYTE, 5, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 5, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 5, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 5, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 5, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 5, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 5, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 5, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 5, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 5, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 5, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 5, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 5, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 5, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 5, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 5, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Send(buffer, 1, MPI_BYTE, 7, 0, MPI_COMM_WORLD);
        do{
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 7, 1, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 7, 2, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 7, 3, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[7]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 7, 4, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 7, 5, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 7, 6, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[13]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 7, 7, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[15]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 7, 8, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[17]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 7, 9, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[19]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 7, 10, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[21]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 7, 11, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[23]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 7, 12, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[25]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 7, 13, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[27]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 7, 14, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[29]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 7, 15, MPI_COMM_WORLD);
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[31]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 7:{
        MPI_Request mpi_reqs[33];
        int flags[33];
        int completed[33];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 1, MPI_BYTE, 6, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 6, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 6, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 6, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 6, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 6, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 6, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 6, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 6, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 6, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 6, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 6, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 6, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 6, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 6, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 6, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Send(buffer, 1, MPI_BYTE, 8, 0, MPI_COMM_WORLD);
        do{
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 8, 1, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 8, 2, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 8, 3, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[7]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 8, 4, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 8, 5, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 8, 6, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[13]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 8, 7, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[15]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 8, 8, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[17]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 8, 9, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[19]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 8, 10, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[21]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 8, 11, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[23]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 8, 12, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[25]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 8, 13, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[27]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 8, 14, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[29]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 8, 15, MPI_COMM_WORLD);
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[31]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 8:{
        MPI_Request mpi_reqs[33];
        int flags[33];
        int completed[33];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 1, MPI_BYTE, 7, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 7, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 7, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 7, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 7, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 7, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 7, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 7, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 7, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 7, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 7, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 7, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 7, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 7, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 7, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 7, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Send(buffer, 1, MPI_BYTE, 9, 0, MPI_COMM_WORLD);
        do{
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 9, 1, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 9, 2, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 9, 3, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[7]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 9, 4, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 9, 5, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 9, 6, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[13]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 9, 7, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[15]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 9, 8, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[17]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 9, 9, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[19]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 9, 10, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[21]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 9, 11, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[23]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 9, 12, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[25]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 9, 13, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[27]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 9, 14, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[29]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 9, 15, MPI_COMM_WORLD);
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[31]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 9:{
        MPI_Request mpi_reqs[33];
        int flags[33];
        int completed[33];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 1, MPI_BYTE, 8, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 8, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 8, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 8, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 8, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 8, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 8, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 8, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 8, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 8, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 8, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 8, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 8, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 8, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 8, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 8, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Send(buffer, 1, MPI_BYTE, 10, 0, MPI_COMM_WORLD);
        do{
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 10, 1, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 10, 2, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 10, 3, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[7]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 10, 4, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 10, 5, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 10, 6, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[13]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 10, 7, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[15]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 10, 8, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[17]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 10, 9, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[19]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 10, 10, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[21]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 10, 11, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[23]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 10, 12, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[25]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 10, 13, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[27]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 10, 14, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[29]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 10, 15, MPI_COMM_WORLD);
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[31]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 10:{
        MPI_Request mpi_reqs[33];
        int flags[33];
        int completed[33];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 1, MPI_BYTE, 9, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 9, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 9, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 9, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 9, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 9, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 9, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 9, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 9, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 9, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 9, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 9, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 9, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 9, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 9, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 9, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Send(buffer, 1, MPI_BYTE, 11, 0, MPI_COMM_WORLD);
        do{
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 11, 1, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 11, 2, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 11, 3, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[7]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 11, 4, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 11, 5, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 11, 6, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[13]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 11, 7, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[15]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 11, 8, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[17]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 11, 9, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[19]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 11, 10, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[21]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 11, 11, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[23]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 11, 12, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[25]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 11, 13, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[27]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 11, 14, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[29]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 11, 15, MPI_COMM_WORLD);
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[31]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 11:{
        MPI_Request mpi_reqs[33];
        int flags[33];
        int completed[33];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 1, MPI_BYTE, 10, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 10, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 10, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 10, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 10, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 10, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 10, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 10, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 10, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 10, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 10, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 10, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 10, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 10, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 10, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 10, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Send(buffer, 1, MPI_BYTE, 12, 0, MPI_COMM_WORLD);
        do{
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 12, 1, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 12, 2, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 12, 3, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[7]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 12, 4, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 12, 5, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 12, 6, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[13]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 12, 7, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[15]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 12, 8, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[17]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 12, 9, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[19]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 12, 10, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[21]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 12, 11, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[23]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 12, 12, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[25]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 12, 13, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[27]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 12, 14, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[29]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 12, 15, MPI_COMM_WORLD);
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[31]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 12:{
        MPI_Request mpi_reqs[33];
        int flags[33];
        int completed[33];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 1, MPI_BYTE, 11, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 11, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 11, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 11, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 11, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 11, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 11, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 11, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 11, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 11, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 11, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 11, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 11, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 11, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 11, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 11, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Send(buffer, 1, MPI_BYTE, 13, 0, MPI_COMM_WORLD);
        do{
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 13, 1, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 13, 2, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 13, 3, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[7]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 13, 4, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 13, 5, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 13, 6, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[13]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 13, 7, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[15]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 13, 8, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[17]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 13, 9, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[19]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 13, 10, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[21]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 13, 11, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[23]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 13, 12, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[25]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 13, 13, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[27]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 13, 14, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[29]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 13, 15, MPI_COMM_WORLD);
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[31]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 13:{
        MPI_Request mpi_reqs[33];
        int flags[33];
        int completed[33];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 1, MPI_BYTE, 12, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 12, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 12, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 12, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 12, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 12, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 12, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 12, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 12, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 12, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 12, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 12, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 12, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 12, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 12, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 12, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Send(buffer, 1, MPI_BYTE, 14, 0, MPI_COMM_WORLD);
        do{
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 14, 1, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 14, 2, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 14, 3, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[7]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 14, 4, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 14, 5, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 14, 6, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[13]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 14, 7, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[15]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 14, 8, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[17]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 14, 9, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[19]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 14, 10, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[21]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 14, 11, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[23]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 14, 12, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[25]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 14, 13, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[27]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 14, 14, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[29]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 14, 15, MPI_COMM_WORLD);
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[31]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 14:{
        MPI_Request mpi_reqs[33];
        int flags[33];
        int completed[33];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 1, MPI_BYTE, 13, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 13, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 13, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 13, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 13, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 13, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 13, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 13, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 13, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 13, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 13, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 13, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 13, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 13, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 13, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 13, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Send(buffer, 1, MPI_BYTE, 15, 0, MPI_COMM_WORLD);
        do{
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 15, 1, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 15, 2, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 15, 3, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[7]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 15, 4, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 15, 5, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 15, 6, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[13]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 15, 7, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[15]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 15, 8, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[17]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 15, 9, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[19]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 15, 10, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[21]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 15, 11, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[23]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 15, 12, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[25]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 15, 13, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[27]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 15, 14, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[29]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 15, 15, MPI_COMM_WORLD);
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[31]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 15:{
        MPI_Request mpi_reqs[33];
        int flags[33];
        int completed[33];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 1, MPI_BYTE, 14, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 14, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 14, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 14, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 14, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 14, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 14, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 14, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 14, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 14, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 14, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 14, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 14, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 14, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 14, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 1, MPI_BYTE, 14, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Send(buffer, 1, MPI_BYTE, 0, 0, MPI_COMM_WORLD);
        do{
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 0, 1, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 0, 2, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 0, 3, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[7]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 0, 4, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 0, 5, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 0, 6, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[13]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 0, 7, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[15]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 0, 8, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[17]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 0, 9, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[19]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 0, 10, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[21]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 0, 11, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[23]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 0, 12, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[25]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 0, 13, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[27]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 0, 14, MPI_COMM_WORLD);
        MPI_Wait(&(mpi_reqs[29]), MPI_STATUS_IGNORE);
        MPI_Send(buffer, 1, MPI_BYTE, 0, 15, MPI_COMM_WORLD);
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[31]), MPI_STATUS_IGNORE);
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
            printf("%d ", 16);
            for(r = 0; r < comm_size; r++){
               printf("%f ", samples_all[r*10000 + i]);
            }
            printf("\n");
        }
    }
    MPI_Finalize();
    return 0;
}