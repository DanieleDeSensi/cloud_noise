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
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 127, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 126, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 124, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 120, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 112, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 96, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 64, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 1, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 2, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 4, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 8, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 16, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 32, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 64, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 1:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 127, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 125, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 121, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 113, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 97, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 65, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 2, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 3, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 5, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 9, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 17, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 33, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 65, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 2:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 126, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 122, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 114, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 98, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 66, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 3, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 4, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 6, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 10, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 18, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 34, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 66, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 3:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 2, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 127, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 123, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 115, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 99, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 67, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 4, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 5, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 7, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 11, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 19, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 35, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 67, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 4:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 3, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 2, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 124, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 116, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 100, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 68, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 5, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 6, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 8, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 12, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 20, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 36, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 68, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 5:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 4, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 3, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 125, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 117, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 101, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 69, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 6, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 7, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 9, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 13, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 21, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 37, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 69, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 6:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 5, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 4, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 2, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 126, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 118, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 102, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 70, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 7, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 8, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 10, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 14, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 22, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 38, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 70, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 7:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 6, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 5, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 3, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 127, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 119, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 103, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 71, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 8, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 9, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 11, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 15, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 23, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 39, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 71, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 8:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 7, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 6, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 4, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 120, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 104, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 72, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 9, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 10, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 12, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 16, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 24, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 40, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 72, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 9:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 8, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 7, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 5, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 121, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 105, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 73, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 10, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 11, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 13, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 17, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 25, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 41, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 73, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 10:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 9, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 8, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 6, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 2, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 122, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 106, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 74, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 11, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 12, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 14, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 18, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 26, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 42, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 74, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 11:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 10, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 9, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 7, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 3, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 123, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 107, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 75, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 12, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 13, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 15, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 19, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 27, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 43, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 75, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 12:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 11, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 10, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 8, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 4, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 124, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 108, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 76, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 13, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 14, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 16, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 20, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 28, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 44, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 76, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 13:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 12, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 11, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 9, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 5, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 125, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 109, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 77, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 14, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 15, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 17, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 21, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 29, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 45, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 77, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 14:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 13, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 12, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 10, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 6, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 126, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 110, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 78, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 15, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 16, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 18, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 22, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 30, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 46, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 78, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 15:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 14, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 13, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 11, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 7, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 127, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 111, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 79, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 16, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 17, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 19, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 23, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 31, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 47, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 79, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 16:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 15, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 14, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 12, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 8, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 112, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 80, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 17, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 18, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 20, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 24, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 32, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 48, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 80, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 17:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 16, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 15, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 13, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 9, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 113, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 81, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 18, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 19, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 21, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 25, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 33, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 49, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 81, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 18:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 17, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 16, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 14, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 10, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 2, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 114, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 82, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 19, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 20, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 22, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 26, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 34, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 50, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 82, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 19:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 18, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 17, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 15, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 11, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 3, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 115, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 83, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 20, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 21, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 23, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 27, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 35, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 51, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 83, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 20:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 19, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 18, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 16, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 12, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 4, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 116, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 84, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 21, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 22, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 24, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 28, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 36, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 52, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 84, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 21:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 20, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 19, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 17, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 13, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 5, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 117, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 85, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 22, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 23, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 25, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 29, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 37, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 53, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 85, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 22:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 21, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 20, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 18, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 14, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 6, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 118, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 86, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 23, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 24, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 26, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 30, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 38, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 54, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 86, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 23:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 22, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 21, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 19, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 15, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 7, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 119, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 87, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 24, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 25, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 27, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 31, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 39, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 55, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 87, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 24:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 23, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 22, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 20, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 16, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 8, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 120, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 88, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 25, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 26, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 28, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 32, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 40, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 56, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 88, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 25:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 24, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 23, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 21, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 17, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 9, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 121, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 89, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 26, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 27, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 29, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 33, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 41, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 57, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 89, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 26:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 25, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 24, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 22, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 18, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 10, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 122, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 90, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 27, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 28, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 30, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 34, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 42, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 58, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 90, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 27:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 26, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 25, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 23, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 19, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 11, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 123, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 91, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 28, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 29, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 31, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 35, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 43, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 59, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 91, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 28:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 27, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 26, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 24, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 20, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 12, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 124, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 92, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 29, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 30, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 32, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 36, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 44, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 60, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 92, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 29:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 28, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 27, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 25, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 21, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 13, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 125, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 93, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 30, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 31, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 33, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 37, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 45, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 61, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 93, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 30:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 29, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 28, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 26, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 22, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 14, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 126, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 94, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 31, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 32, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 34, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 38, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 46, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 62, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 94, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 31:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 30, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 29, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 27, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 23, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 15, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 127, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 95, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 32, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 33, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 35, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 39, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 47, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 63, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 95, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 32:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 31, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 30, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 28, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 24, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 16, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 96, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 33, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 34, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 36, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 40, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 48, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 64, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 96, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 33:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 32, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 31, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 29, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 25, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 17, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 97, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 34, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 35, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 37, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 41, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 49, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 65, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 97, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 34:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 33, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 32, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 30, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 26, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 18, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 2, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 98, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 35, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 36, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 38, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 42, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 50, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 66, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 98, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 35:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 34, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 33, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 31, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 27, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 19, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 3, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 99, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 36, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 37, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 39, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 43, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 51, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 67, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 99, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 36:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 35, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 34, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 32, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 28, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 20, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 4, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 100, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 37, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 38, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 40, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 44, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 52, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 68, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 100, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 37:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 36, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 35, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 33, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 29, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 21, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 5, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 101, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 38, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 39, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 41, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 45, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 53, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 69, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 101, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 38:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 37, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 36, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 34, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 30, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 22, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 6, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 102, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 39, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 40, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 42, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 46, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 54, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 70, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 102, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 39:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 38, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 37, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 35, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 31, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 23, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 7, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 103, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 40, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 41, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 43, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 47, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 55, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 71, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 103, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 40:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 39, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 38, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 36, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 32, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 24, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 8, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 104, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 41, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 42, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 44, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 48, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 56, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 72, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 104, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 41:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 40, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 39, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 37, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 33, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 25, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 9, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 105, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 42, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 43, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 45, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 49, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 57, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 73, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 105, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 42:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 41, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 40, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 38, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 34, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 26, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 10, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 106, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 43, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 44, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 46, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 50, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 58, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 74, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 106, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 43:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 42, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 41, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 39, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 35, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 27, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 11, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 107, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 44, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 45, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 47, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 51, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 59, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 75, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 107, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 44:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 43, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 42, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 40, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 36, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 28, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 12, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 108, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 45, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 46, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 48, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 52, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 60, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 76, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 108, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 45:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 44, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 43, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 41, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 37, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 29, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 13, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 109, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 46, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 47, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 49, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 53, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 61, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 77, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 109, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 46:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 45, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 44, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 42, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 38, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 30, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 14, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 110, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 47, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 48, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 50, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 54, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 62, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 78, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 110, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 47:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 46, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 45, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 43, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 39, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 31, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 15, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 111, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 48, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 49, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 51, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 55, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 63, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 79, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 111, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 48:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 47, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 46, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 44, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 40, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 32, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 16, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 112, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 49, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 50, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 52, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 56, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 64, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 80, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 112, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 49:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 48, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 47, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 45, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 41, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 33, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 17, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 113, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 50, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 51, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 53, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 57, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 65, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 81, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 113, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 50:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 49, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 48, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 46, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 42, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 34, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 18, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 114, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 51, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 52, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 54, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 58, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 66, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 82, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 114, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 51:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 50, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 49, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 47, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 43, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 35, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 19, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 115, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 52, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 53, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 55, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 59, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 67, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 83, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 115, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 52:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 51, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 50, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 48, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 44, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 36, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 20, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 116, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 53, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 54, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 56, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 60, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 68, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 84, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 116, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 53:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 52, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 51, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 49, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 45, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 37, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 21, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 117, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 54, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 55, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 57, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 61, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 69, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 85, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 117, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 54:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 53, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 52, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 50, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 46, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 38, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 22, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 118, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 55, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 56, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 58, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 62, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 70, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 86, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 118, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 55:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 54, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 53, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 51, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 47, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 39, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 23, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 119, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 56, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 57, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 59, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 63, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 71, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 87, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 119, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 56:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 55, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 54, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 52, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 48, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 40, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 24, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 120, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 57, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 58, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 60, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 64, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 72, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 88, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 120, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 57:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 56, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 55, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 53, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 49, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 41, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 25, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 121, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 58, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 59, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 61, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 65, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 73, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 89, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 121, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 58:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 57, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 56, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 54, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 50, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 42, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 26, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 122, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 59, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 60, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 62, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 66, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 74, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 90, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 122, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 59:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 58, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 57, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 55, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 51, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 43, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 27, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 123, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 60, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 61, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 63, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 67, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 75, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 91, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 123, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 60:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 59, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 58, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 56, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 52, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 44, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 28, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 124, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 61, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 62, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 64, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 68, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 76, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 92, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 124, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 61:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 60, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 59, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 57, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 53, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 45, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 29, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 125, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 62, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 63, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 65, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 69, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 77, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 93, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 125, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 62:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 61, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 60, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 58, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 54, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 46, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 30, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 126, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 63, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 64, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 66, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 70, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 78, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 94, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 126, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 63:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 62, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 61, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 59, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 55, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 47, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 31, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 127, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 64, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 65, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 67, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 71, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 79, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 95, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 127, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 64:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 63, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 62, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 60, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 56, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 48, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 32, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 65, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 66, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 68, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 72, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 80, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 96, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 0, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 65:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 64, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 63, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 61, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 57, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 49, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 33, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 66, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 67, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 69, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 73, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 81, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 97, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 1, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 66:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 65, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 64, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 62, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 58, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 50, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 34, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 2, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 67, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 68, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 70, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 74, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 82, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 98, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 2, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 67:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 66, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 65, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 63, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 59, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 51, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 35, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 3, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 68, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 69, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 71, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 75, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 83, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 99, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 3, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 68:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 67, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 66, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 64, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 60, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 52, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 36, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 4, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 69, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 70, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 72, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 76, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 84, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 100, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 4, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 69:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 68, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 67, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 65, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 61, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 53, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 37, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 5, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 70, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 71, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 73, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 77, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 85, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 101, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 5, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 70:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 69, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 68, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 66, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 62, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 54, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 38, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 6, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 71, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 72, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 74, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 78, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 86, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 102, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 6, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 71:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 70, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 69, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 67, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 63, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 55, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 39, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 7, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 72, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 73, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 75, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 79, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 87, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 103, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 7, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 72:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 71, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 70, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 68, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 64, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 56, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 40, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 8, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 73, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 74, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 76, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 80, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 88, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 104, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 8, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 73:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 72, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 71, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 69, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 65, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 57, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 41, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 9, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 74, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 75, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 77, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 81, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 89, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 105, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 9, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 74:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 73, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 72, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 70, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 66, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 58, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 42, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 10, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 75, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 76, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 78, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 82, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 90, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 106, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 10, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 75:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 74, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 73, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 71, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 67, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 59, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 43, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 11, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 76, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 77, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 79, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 83, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 91, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 107, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 11, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 76:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 75, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 74, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 72, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 68, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 60, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 44, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 12, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 77, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 78, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 80, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 84, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 92, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 108, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 12, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 77:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 76, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 75, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 73, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 69, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 61, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 45, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 13, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 78, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 79, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 81, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 85, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 93, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 109, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 13, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 78:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 77, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 76, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 74, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 70, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 62, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 46, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 14, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 79, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 80, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 82, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 86, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 94, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 110, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 14, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 79:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 78, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 77, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 75, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 71, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 63, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 47, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 15, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 80, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 81, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 83, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 87, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 95, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 111, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 15, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 80:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 79, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 78, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 76, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 72, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 64, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 48, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 16, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 81, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 82, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 84, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 88, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 96, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 112, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 16, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 81:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 80, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 79, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 77, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 73, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 65, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 49, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 17, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 82, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 83, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 85, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 89, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 97, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 113, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 17, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 82:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 81, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 80, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 78, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 74, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 66, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 50, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 18, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 83, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 84, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 86, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 90, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 98, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 114, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 18, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 83:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 82, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 81, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 79, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 75, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 67, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 51, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 19, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 84, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 85, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 87, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 91, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 99, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 115, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 19, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 84:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 83, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 82, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 80, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 76, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 68, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 52, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 20, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 85, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 86, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 88, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 92, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 100, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 116, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 20, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 85:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 84, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 83, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 81, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 77, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 69, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 53, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 21, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 86, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 87, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 89, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 93, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 101, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 117, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 21, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 86:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 85, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 84, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 82, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 78, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 70, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 54, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 22, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 87, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 88, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 90, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 94, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 102, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 118, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 22, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 87:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 86, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 85, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 83, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 79, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 71, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 55, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 23, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 88, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 89, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 91, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 95, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 103, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 119, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 23, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 88:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 87, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 86, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 84, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 80, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 72, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 56, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 24, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 89, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 90, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 92, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 96, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 104, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 120, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 24, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 89:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 88, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 87, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 85, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 81, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 73, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 57, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 25, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 90, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 91, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 93, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 97, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 105, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 121, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 25, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 90:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 89, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 88, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 86, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 82, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 74, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 58, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 26, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 91, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 92, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 94, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 98, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 106, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 122, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 26, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 91:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 90, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 89, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 87, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 83, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 75, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 59, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 27, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 92, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 93, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 95, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 99, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 107, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 123, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 27, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 92:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 91, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 90, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 88, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 84, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 76, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 60, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 28, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 93, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 94, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 96, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 100, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 108, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 124, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 28, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 93:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 92, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 91, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 89, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 85, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 77, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 61, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 29, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 94, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 95, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 97, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 101, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 109, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 125, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 29, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 94:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 93, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 92, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 90, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 86, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 78, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 62, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 30, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 95, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 96, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 98, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 102, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 110, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 126, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 30, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 95:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 94, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 93, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 91, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 87, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 79, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 63, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 31, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 96, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 97, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 99, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 103, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 111, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 127, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 31, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 96:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 95, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 94, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 92, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 88, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 80, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 64, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 32, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 97, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 98, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 100, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 104, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 112, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 0, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 32, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 97:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 96, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 95, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 93, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 89, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 81, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 65, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 33, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 98, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 99, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 101, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 105, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 113, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 1, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 33, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 98:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 97, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 96, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 94, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 90, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 82, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 66, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 34, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 99, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 100, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 102, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 106, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 114, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 2, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 34, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 99:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 98, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 97, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 95, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 91, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 83, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 67, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 35, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 100, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 101, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 103, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 107, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 115, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 3, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 35, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 100:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 99, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 98, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 96, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 92, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 84, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 68, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 36, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 101, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 102, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 104, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 108, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 116, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 4, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 36, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 101:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 100, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 99, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 97, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 93, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 85, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 69, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 37, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 102, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 103, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 105, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 109, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 117, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 5, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 37, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 102:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 101, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 100, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 98, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 94, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 86, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 70, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 38, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 103, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 104, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 106, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 110, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 118, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 6, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 38, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 103:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 102, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 101, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 99, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 95, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 87, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 71, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 39, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 104, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 105, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 107, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 111, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 119, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 7, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 39, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 104:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 103, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 102, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 100, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 96, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 88, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 72, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 40, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 105, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 106, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 108, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 112, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 120, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 8, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 40, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 105:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 104, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 103, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 101, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 97, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 89, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 73, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 41, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 106, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 107, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 109, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 113, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 121, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 9, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 41, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 106:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 105, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 104, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 102, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 98, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 90, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 74, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 42, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 107, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 108, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 110, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 114, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 122, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 10, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 42, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 107:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 106, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 105, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 103, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 99, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 91, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 75, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 43, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 108, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 109, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 111, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 115, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 123, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 11, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 43, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 108:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 107, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 106, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 104, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 100, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 92, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 76, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 44, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 109, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 110, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 112, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 116, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 124, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 12, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 44, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 109:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 108, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 107, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 105, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 101, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 93, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 77, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 45, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 110, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 111, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 113, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 117, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 125, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 13, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 45, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 110:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 109, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 108, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 106, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 102, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 94, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 78, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 46, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 111, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 112, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 114, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 118, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 126, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 14, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 46, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 111:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 110, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 109, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 107, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 103, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 95, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 79, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 47, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 112, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 113, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 115, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 119, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 127, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 15, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 47, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 112:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 111, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 110, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 108, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 104, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 96, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 80, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 48, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 113, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 114, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 116, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 120, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 0, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 16, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 48, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 113:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 112, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 111, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 109, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 105, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 97, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 81, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 49, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 114, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 115, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 117, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 121, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 1, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 17, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 49, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 114:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 113, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 112, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 110, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 106, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 98, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 82, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 50, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 115, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 116, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 118, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 122, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 2, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 18, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 50, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 115:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 114, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 113, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 111, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 107, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 99, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 83, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 51, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 116, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 117, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 119, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 123, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 3, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 19, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 51, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 116:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 115, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 114, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 112, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 108, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 100, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 84, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 52, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 117, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 118, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 120, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 124, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 4, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 20, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 52, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 117:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 116, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 115, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 113, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 109, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 101, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 85, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 53, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 118, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 119, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 121, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 125, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 5, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 21, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 53, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 118:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 117, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 116, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 114, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 110, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 102, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 86, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 54, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 119, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 120, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 122, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 126, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 6, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 22, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 54, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 119:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 118, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 117, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 115, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 111, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 103, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 87, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 55, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 120, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 121, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 123, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 127, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 7, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 23, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 55, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 120:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 119, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 118, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 116, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 112, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 104, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 88, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 56, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 121, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 122, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 124, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 0, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 8, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 24, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 56, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 121:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 120, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 119, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 117, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 113, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 105, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 89, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 57, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 122, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 123, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 125, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 1, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 9, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 25, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 57, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 122:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 121, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 120, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 118, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 114, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 106, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 90, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 58, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 123, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 124, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 126, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 2, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 10, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 26, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 58, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 123:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 122, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 121, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 119, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 115, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 107, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 91, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 59, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 124, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 125, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 127, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 3, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 11, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 27, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 59, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 124:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 123, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 122, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 120, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 116, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 108, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 92, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 60, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 125, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 126, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 0, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 4, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 12, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 28, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 60, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 125:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 124, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 123, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 121, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 117, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 109, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 93, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 61, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 126, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 127, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 1, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 5, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 13, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 29, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 61, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 126:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 125, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 124, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 122, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 118, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 110, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 94, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 62, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 127, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 0, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 2, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 6, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 14, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 30, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 62, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 127:{
        MPI_Request mpi_reqs[21];
        int flags[21];
        int completed[21];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 16384, MPI_BYTE, 126, 0, MPI_COMM_WORLD, &(mpi_reqs[2]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 125, 0, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 123, 0, MPI_COMM_WORLD, &(mpi_reqs[8]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 119, 0, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 111, 0, MPI_COMM_WORLD, &(mpi_reqs[14]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 95, 0, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 16384, MPI_BYTE, 63, 0, MPI_COMM_WORLD, &(mpi_reqs[20]));
        MPI_Send(buffer, 16384, MPI_BYTE, 0, 0, MPI_COMM_WORLD);
        do{
            if(completed[2] == 0){
                MPI_Test(&(mpi_reqs[2]), &(flags[2]), MPI_STATUS_IGNORE);
                if(flags[2] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 1, 0, MPI_COMM_WORLD);
                    completed[2] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 3, 0, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[8] == 0){
                MPI_Test(&(mpi_reqs[8]), &(flags[8]), MPI_STATUS_IGNORE);
                if(flags[8] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 7, 0, MPI_COMM_WORLD);
                    completed[8] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 15, 0, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[14] == 0){
                MPI_Test(&(mpi_reqs[14]), &(flags[14]), MPI_STATUS_IGNORE);
                if(flags[14] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 31, 0, MPI_COMM_WORLD);
                    completed[14] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 16384, MPI_BYTE, 63, 0, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 6);
        MPI_Wait(&(mpi_reqs[20]), MPI_STATUS_IGNORE);
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
