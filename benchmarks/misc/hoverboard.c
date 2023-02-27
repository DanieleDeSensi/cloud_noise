#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#define add_time(now, expected, s, ns)           \
    {                                            \
        expected.tv_sec = now.tv_sec + add_s;    \
        expected.tv_nsec = now.tv_nsec + add_ns; \
    }
#define cmp_time_leq(time1, time2) (time1.tv_sec < time2.tv_sec ? 1 : (time1.tv_sec == time2.tv_sec && time1.tv_nsec < time2.tv_nsec ? 1 : 0))

void runner(long int message_size, int repetitions, long sleep_time_ns, FILE *datafile);

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("Usage: %s msg_size repetitions sleep_time_ns outfile\n", argv[0]);
        exit(0);
    }

    // parse arguments
    long int msg_size = atoi(argv[1]);
    int repetitions = atoi(argv[2]);
    long sleep_time_ns = atol(argv[3]);
    char *datafile_name = argv[4];

    FILE *datafile = fopen(datafile_name, "w");
    runner(msg_size, repetitions, sleep_time_ns, datafile);
    fclose(datafile);
    return 0;
}

/**
 * Runs the Hoverboard Test (MPI send/recv loop)
 * 
 * @param message_size [bytes]
 * @param repetitions for how many times we send the message before we sleep
 * @param sleep_time_ns for how long to sleep
 * @param datafile file to write output to (opened as write file)
 */
void runner(long int message_size, int repetitions, long sleep_time_ns, FILE *datafile)
{
    int my_rank, num_procs;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Status stat;
    // check if we have two processes
    if (num_procs != 2)
    {
        if (my_rank == 0)
        {
            printf("We need two processes\n");
        }
        MPI_Finalize();
        exit(0);
    }

    // allocate buffer
    uint8_t *s_buf = (uint8_t *)malloc(message_size * sizeof(*s_buf));
    uint8_t *r_buf = (uint8_t *)malloc(message_size * sizeof(*r_buf));

    // set values in buffer to zero
    memset(s_buf, 0, sizeof(uint8_t)*message_size);
    memset(r_buf, 0, sizeof(uint8_t)*message_size);

    //write header
    if (my_rank == 0)
    {
        fprintf(datafile, "# Hoverboard test (%ld %d %ld)\n", message_size, repetitions, sleep_time_ns);
        fprintf(datafile, "# time(ns),sleep_time(ns),repetitions\n");
        fflush(datafile);
    }

    double start, end, total_start, total_end, tmp;
    long add_s, add_ns, measured_time;
    struct timespec now, expected;

    total_start = MPI_Wtime();
    // For each sleep time we execute 30 iterations of the inner loop. In the inner loop we execute #repetition many iterations of senc/recv
    //printf("rank: %d, sleep time: %.9f\n", my_rank, sleep_time);
    fflush(stdout);
    int i, j;
    for (i = 0; i < 30; i++)
    {
        start = MPI_Wtime();
        for (j = 0; j < repetitions; j++)
        {
            if (my_rank == 0)
            {
                MPI_Send(s_buf, message_size * sizeof(*s_buf), MPI_UINT8_T, 1, 0, MPI_COMM_WORLD);
                MPI_Recv(r_buf, message_size * sizeof(*r_buf), MPI_UINT8_T, 1, 0, MPI_COMM_WORLD, &stat);
            }
            else
            { // rank == 1
                MPI_Recv(r_buf, message_size * sizeof(*r_buf), MPI_UINT8_T, 0, 0, MPI_COMM_WORLD, &stat);
                MPI_Send(s_buf, message_size * sizeof(*s_buf), MPI_UINT8_T, 0, 0, MPI_COMM_WORLD);
            }
        }
        end = MPI_Wtime();
        // write the results to the output file
        if (my_rank == 0)
        {
            measured_time = (long) ((end - start)*1e9);
            fprintf(datafile, "%ld,%ld,%d\n", measured_time, sleep_time_ns, repetitions);

            // busy waiting
            if (sleep_time_ns >= 1e9)
            {
                add_s = sleep_time_ns / 1e9;
                add_ns = (long)sleep_time_ns % (long)1e9;
            }
            else
            {
                add_s = 0;
                add_ns = sleep_time_ns;
            }

            clock_gettime(CLOCK_REALTIME, &now);
            add_time(now, expected, add_s, add_ns);
            while (cmp_time_leq(now, expected))
            {
                clock_gettime(CLOCK_REALTIME, &now);
            }
        }
    }

    total_end = MPI_Wtime();

    // print the total time it took to complete the test into the output file
    if (my_rank == 0)
    {
        //printf("Total time needed to run the test: %.2f seconds\n", total_end - total_start);
    }

    free(s_buf);
    free(r_buf);
    MPI_Finalize();
}