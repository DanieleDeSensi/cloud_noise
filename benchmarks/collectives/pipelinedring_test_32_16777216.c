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
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 31, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 1, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 1, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 1:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 0, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 2, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 2, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 2:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 1, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 3, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 3, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 3:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 2, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 4, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 4, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 4:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 3, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 5, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 5, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 5:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 4, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 6, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 6, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 6:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 5, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 7, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 7, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 7:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 6, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 8, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 8, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 8:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 7, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 9, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 9, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 9:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 8, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 10, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 10, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 10:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 9, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 11, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 11, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 11:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 10, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 12, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 12, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 12:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 11, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 13, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 13, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 13:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 12, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 14, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 14, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 14:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 13, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 15, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 15, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 15:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 14, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 16, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 16, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 16:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 15, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 17, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 17, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 17:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 16, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 18, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 18, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 18:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 17, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 19, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 19, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 19:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 18, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 20, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 20, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 20:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 19, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 21, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 21, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 21:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 20, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 22, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 22, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 22:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 21, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 23, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 23, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 23:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 22, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 24, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 24, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 24:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 23, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 25, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 25, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 25:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 24, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 26, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 26, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 26:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 25, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 27, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 27, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 27:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 26, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 28, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 28, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 28:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 27, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 29, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 29, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 29:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 28, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 30, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 30, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 30:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 29, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 31, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 31, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
        if(i >= 0){
            samples[i] = ((MPI_Wtime() - start_time)*1000000.0);
        }
        break;
        }
        case 31:{
        MPI_Request mpi_reqs[65];
        int flags[65];
        int completed[65];
        memset(flags, 0, sizeof(flags));
        memset(completed, 0, sizeof(completed));
        int completed_tot = 0;
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 0, MPI_COMM_WORLD, &(mpi_reqs[1]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 1, MPI_COMM_WORLD, &(mpi_reqs[3]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 2, MPI_COMM_WORLD, &(mpi_reqs[5]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 3, MPI_COMM_WORLD, &(mpi_reqs[7]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 4, MPI_COMM_WORLD, &(mpi_reqs[9]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 5, MPI_COMM_WORLD, &(mpi_reqs[11]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 6, MPI_COMM_WORLD, &(mpi_reqs[13]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 7, MPI_COMM_WORLD, &(mpi_reqs[15]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 8, MPI_COMM_WORLD, &(mpi_reqs[17]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 9, MPI_COMM_WORLD, &(mpi_reqs[19]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 10, MPI_COMM_WORLD, &(mpi_reqs[21]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 11, MPI_COMM_WORLD, &(mpi_reqs[23]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 12, MPI_COMM_WORLD, &(mpi_reqs[25]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 13, MPI_COMM_WORLD, &(mpi_reqs[27]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 14, MPI_COMM_WORLD, &(mpi_reqs[29]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 15, MPI_COMM_WORLD, &(mpi_reqs[31]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 16, MPI_COMM_WORLD, &(mpi_reqs[33]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 17, MPI_COMM_WORLD, &(mpi_reqs[35]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 18, MPI_COMM_WORLD, &(mpi_reqs[37]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 19, MPI_COMM_WORLD, &(mpi_reqs[39]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 20, MPI_COMM_WORLD, &(mpi_reqs[41]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 21, MPI_COMM_WORLD, &(mpi_reqs[43]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 22, MPI_COMM_WORLD, &(mpi_reqs[45]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 23, MPI_COMM_WORLD, &(mpi_reqs[47]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 24, MPI_COMM_WORLD, &(mpi_reqs[49]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 25, MPI_COMM_WORLD, &(mpi_reqs[51]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 26, MPI_COMM_WORLD, &(mpi_reqs[53]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 27, MPI_COMM_WORLD, &(mpi_reqs[55]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 28, MPI_COMM_WORLD, &(mpi_reqs[57]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 29, MPI_COMM_WORLD, &(mpi_reqs[59]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 30, MPI_COMM_WORLD, &(mpi_reqs[61]));
        MPI_Irecv(buffer, 524288, MPI_BYTE, 30, 31, MPI_COMM_WORLD, &(mpi_reqs[63]));
        MPI_Send(buffer, 524288, MPI_BYTE, 0, 0, MPI_COMM_WORLD);
        do{
            if(completed[1] == 0){
                MPI_Test(&(mpi_reqs[1]), &(flags[1]), MPI_STATUS_IGNORE);
                if(flags[1] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 1, MPI_COMM_WORLD);
                    completed[1] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[3] == 0){
                MPI_Test(&(mpi_reqs[3]), &(flags[3]), MPI_STATUS_IGNORE);
                if(flags[3] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 2, MPI_COMM_WORLD);
                    completed[3] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[5] == 0){
                MPI_Test(&(mpi_reqs[5]), &(flags[5]), MPI_STATUS_IGNORE);
                if(flags[5] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 3, MPI_COMM_WORLD);
                    completed[5] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[7] == 0){
                MPI_Test(&(mpi_reqs[7]), &(flags[7]), MPI_STATUS_IGNORE);
                if(flags[7] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 4, MPI_COMM_WORLD);
                    completed[7] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[9] == 0){
                MPI_Test(&(mpi_reqs[9]), &(flags[9]), MPI_STATUS_IGNORE);
                if(flags[9] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 5, MPI_COMM_WORLD);
                    completed[9] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[11] == 0){
                MPI_Test(&(mpi_reqs[11]), &(flags[11]), MPI_STATUS_IGNORE);
                if(flags[11] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 6, MPI_COMM_WORLD);
                    completed[11] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[13] == 0){
                MPI_Test(&(mpi_reqs[13]), &(flags[13]), MPI_STATUS_IGNORE);
                if(flags[13] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 7, MPI_COMM_WORLD);
                    completed[13] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[15] == 0){
                MPI_Test(&(mpi_reqs[15]), &(flags[15]), MPI_STATUS_IGNORE);
                if(flags[15] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 8, MPI_COMM_WORLD);
                    completed[15] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[17] == 0){
                MPI_Test(&(mpi_reqs[17]), &(flags[17]), MPI_STATUS_IGNORE);
                if(flags[17] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 9, MPI_COMM_WORLD);
                    completed[17] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[19] == 0){
                MPI_Test(&(mpi_reqs[19]), &(flags[19]), MPI_STATUS_IGNORE);
                if(flags[19] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 10, MPI_COMM_WORLD);
                    completed[19] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[21] == 0){
                MPI_Test(&(mpi_reqs[21]), &(flags[21]), MPI_STATUS_IGNORE);
                if(flags[21] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 11, MPI_COMM_WORLD);
                    completed[21] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[23] == 0){
                MPI_Test(&(mpi_reqs[23]), &(flags[23]), MPI_STATUS_IGNORE);
                if(flags[23] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 12, MPI_COMM_WORLD);
                    completed[23] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[25] == 0){
                MPI_Test(&(mpi_reqs[25]), &(flags[25]), MPI_STATUS_IGNORE);
                if(flags[25] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 13, MPI_COMM_WORLD);
                    completed[25] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[27] == 0){
                MPI_Test(&(mpi_reqs[27]), &(flags[27]), MPI_STATUS_IGNORE);
                if(flags[27] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 14, MPI_COMM_WORLD);
                    completed[27] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[29] == 0){
                MPI_Test(&(mpi_reqs[29]), &(flags[29]), MPI_STATUS_IGNORE);
                if(flags[29] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 15, MPI_COMM_WORLD);
                    completed[29] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[31] == 0){
                MPI_Test(&(mpi_reqs[31]), &(flags[31]), MPI_STATUS_IGNORE);
                if(flags[31] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 16, MPI_COMM_WORLD);
                    completed[31] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[33] == 0){
                MPI_Test(&(mpi_reqs[33]), &(flags[33]), MPI_STATUS_IGNORE);
                if(flags[33] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 17, MPI_COMM_WORLD);
                    completed[33] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[35] == 0){
                MPI_Test(&(mpi_reqs[35]), &(flags[35]), MPI_STATUS_IGNORE);
                if(flags[35] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 18, MPI_COMM_WORLD);
                    completed[35] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[37] == 0){
                MPI_Test(&(mpi_reqs[37]), &(flags[37]), MPI_STATUS_IGNORE);
                if(flags[37] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 19, MPI_COMM_WORLD);
                    completed[37] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[39] == 0){
                MPI_Test(&(mpi_reqs[39]), &(flags[39]), MPI_STATUS_IGNORE);
                if(flags[39] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 20, MPI_COMM_WORLD);
                    completed[39] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[41] == 0){
                MPI_Test(&(mpi_reqs[41]), &(flags[41]), MPI_STATUS_IGNORE);
                if(flags[41] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 21, MPI_COMM_WORLD);
                    completed[41] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[43] == 0){
                MPI_Test(&(mpi_reqs[43]), &(flags[43]), MPI_STATUS_IGNORE);
                if(flags[43] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 22, MPI_COMM_WORLD);
                    completed[43] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[45] == 0){
                MPI_Test(&(mpi_reqs[45]), &(flags[45]), MPI_STATUS_IGNORE);
                if(flags[45] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 23, MPI_COMM_WORLD);
                    completed[45] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[47] == 0){
                MPI_Test(&(mpi_reqs[47]), &(flags[47]), MPI_STATUS_IGNORE);
                if(flags[47] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 24, MPI_COMM_WORLD);
                    completed[47] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[49] == 0){
                MPI_Test(&(mpi_reqs[49]), &(flags[49]), MPI_STATUS_IGNORE);
                if(flags[49] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 25, MPI_COMM_WORLD);
                    completed[49] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[51] == 0){
                MPI_Test(&(mpi_reqs[51]), &(flags[51]), MPI_STATUS_IGNORE);
                if(flags[51] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 26, MPI_COMM_WORLD);
                    completed[51] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[53] == 0){
                MPI_Test(&(mpi_reqs[53]), &(flags[53]), MPI_STATUS_IGNORE);
                if(flags[53] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 27, MPI_COMM_WORLD);
                    completed[53] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[55] == 0){
                MPI_Test(&(mpi_reqs[55]), &(flags[55]), MPI_STATUS_IGNORE);
                if(flags[55] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 28, MPI_COMM_WORLD);
                    completed[55] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[57] == 0){
                MPI_Test(&(mpi_reqs[57]), &(flags[57]), MPI_STATUS_IGNORE);
                if(flags[57] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 29, MPI_COMM_WORLD);
                    completed[57] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[59] == 0){
                MPI_Test(&(mpi_reqs[59]), &(flags[59]), MPI_STATUS_IGNORE);
                if(flags[59] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 30, MPI_COMM_WORLD);
                    completed[59] = 1;
                    completed_tot += 1;
                }
            }
            if(completed[61] == 0){
                MPI_Test(&(mpi_reqs[61]), &(flags[61]), MPI_STATUS_IGNORE);
                if(flags[61] == 1){
                    MPI_Send(buffer, 524288, MPI_BYTE, 0, 31, MPI_COMM_WORLD);
                    completed[61] = 1;
                    completed_tot += 1;
                }
            }
        }while(completed_tot < 31);
        MPI_Wait(&(mpi_reqs[63]), MPI_STATUS_IGNORE);
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
