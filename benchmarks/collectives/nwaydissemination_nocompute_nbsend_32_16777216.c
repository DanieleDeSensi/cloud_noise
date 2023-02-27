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
    char* buffer = (char*) malloc(sizeof(char)*16777216);
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
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 31, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 30, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 28, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 24, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 16, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 2, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 4, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 8, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 16, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 1:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 31, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 29, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 25, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 17, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 2, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 3, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 5, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 9, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 17, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 2:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 30, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 26, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 18, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 3, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 4, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 6, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 10, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 18, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 3:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 2, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 31, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 27, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 19, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 4, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 5, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 7, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 11, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 19, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 4:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 3, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 2, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 28, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 20, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 5, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 6, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 8, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 12, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 20, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 5:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 4, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 3, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 29, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 21, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 6, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 7, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 9, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 13, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 21, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 6:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 5, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 4, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 2, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 30, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 22, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 7, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 8, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 10, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 14, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 22, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 7:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 6, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 5, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 3, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 31, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 23, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 8, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 9, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 11, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 15, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 23, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 8:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 7, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 6, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 4, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 24, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 9, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 10, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 12, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 16, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 24, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 9:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 8, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 7, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 5, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 25, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 10, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 11, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 13, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 17, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 25, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 10:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 9, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 8, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 6, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 2, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 26, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 11, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 12, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 14, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 18, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 26, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 11:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 10, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 9, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 7, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 3, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 27, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 12, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 13, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 15, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 19, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 27, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 12:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 11, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 10, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 8, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 4, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 28, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 13, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 14, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 16, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 20, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 28, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 13:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 12, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 11, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 9, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 5, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 29, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 14, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 15, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 17, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 21, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 29, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 14:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 13, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 12, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 10, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 6, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 30, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 15, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 16, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 18, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 22, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 30, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 15:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 14, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 13, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 11, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 7, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 31, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 16, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 17, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 19, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 23, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 31, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 16:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 15, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 14, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 12, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 8, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 17, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 18, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 20, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 24, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 17:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 16, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 15, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 13, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 9, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 18, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 19, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 21, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 25, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 18:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 17, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 16, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 14, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 10, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 2, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 19, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 20, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 22, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 26, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 2, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 19:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 18, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 17, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 15, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 11, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 3, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 20, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 21, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 23, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 27, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 3, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 20:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 19, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 18, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 16, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 12, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 4, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 21, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 22, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 24, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 28, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 4, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 21:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 20, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 19, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 17, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 13, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 5, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 22, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 23, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 25, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 29, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 5, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 22:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 21, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 20, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 18, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 14, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 6, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 23, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 24, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 26, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 30, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 6, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 23:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 22, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 21, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 19, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 15, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 7, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 24, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 25, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 27, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 31, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 7, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 24:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 23, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 22, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 20, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 16, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 8, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 25, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 26, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 28, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 8, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 25:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 24, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 23, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 21, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 17, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 9, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 26, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 27, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 29, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 9, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 26:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 25, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 24, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 22, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 18, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 10, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 27, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 28, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 30, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 2, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 10, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 27:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 26, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 25, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 23, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 19, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 11, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 28, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 29, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 31, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 3, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 11, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 28:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 27, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 26, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 24, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 20, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 12, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 29, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 30, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 4, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 12, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 29:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 28, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 27, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 25, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 21, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 13, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 30, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 31, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 5, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 13, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 30:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 29, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 28, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 26, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 22, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 14, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 31, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 2, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 6, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 14, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 31:{
        MPI_Request mpi_reqs[15];
        int flags[15];
        int completed[15];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 30, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 29, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 27, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 23, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16777216, MPI_BYTE, 15, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Isend(buffer, 16777216, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        do{
        MPI_Wait(&(mpi_reqs[2]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Wait(&(mpi_reqs[5]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 3, 0, MPI_COMM_WORLD, &(mpi_reqs[6]));
        MPI_Wait(&(mpi_reqs[8]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 7, 0, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Wait(&(mpi_reqs[11]), MPI_STATUS_IGNORE);
        MPI_Isend(buffer, 16777216, MPI_BYTE, 15, 0, MPI_COMM_WORLD, &(mpi_reqs[12]));
        }while(completed_tot < 0);
        MPI_Wait(&(mpi_reqs[14]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[1]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[3]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[6]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[9]), MPI_STATUS_IGNORE);
        MPI_Wait(&(mpi_reqs[12]), MPI_STATUS_IGNORE);
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
            printf("%d ", 16777216);
            for(r = 0; r < comm_size; r++){
               printf("%f ", samples_all[r*10000 + i]);
            }
            printf("\n");
        }
    }
    MPI_Finalize();
    return 0;
}
