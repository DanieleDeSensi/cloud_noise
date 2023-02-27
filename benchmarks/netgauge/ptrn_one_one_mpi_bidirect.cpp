/*
 * Copyright (c) 2009 The Trustees of Indiana University and Indiana
 *                    University Research and Technology
 *                    Corporation.  All rights reserved.
 *
 * Author(s): Torsten Hoefler <htor@cs.indiana.edu>
 *
 */

#include "netgauge.h"
#if defined(NG_PTRN_ONE_ONE_MPI_BIDIRECT) && defined(NG_MPI)
#include "hrtimer/hrtimer.h"
#include <vector>
#include <time.h>
#include <algorithm>
#include "fullresult.h"
#include "statistics.h"
#include "ng_tools.hpp"


extern "C" {

extern struct ng_options g_options;

/* internal function prototypes */
static void one_one_mpi_bidirect_do_benchmarks(struct ng_module *module);

/**
 * comm. pattern description and function pointer table
 */
static struct ng_comm_pattern pattern_one_one_mpi_bidirect = {
   pattern_one_one_mpi_bidirect.name = "one_one_mpi_bidirect",
   pattern_one_one_mpi_bidirect.desc = "measures bidirectional ping-pong latency&bandwidth",
   pattern_one_one_mpi_bidirect.flags = 0,
   pattern_one_one_mpi_bidirect.do_benchmarks = one_one_mpi_bidirect_do_benchmarks
};

/**
 * register this comm. pattern for usage in main
 * program
 */
int register_pattern_one_one_mpi_bidirect() {
   ng_register_pattern(&pattern_one_one_mpi_bidirect);
   return 0;
}

static void one_one_mpi_bidirect_do_benchmarks(struct ng_module *module) {
  /** for collecting statistics */
  struct ng_statistics statistics;

  /** currently tested packet size and maximum */
  long data_size;

  /** number of times to test the current datasize */
  long test_count = g_options.testcount;

  /** counts up to test_count */
  int test_round = 0;

  /** how long does the test run? */
  time_t test_time, cur_test_time;

  /** number of tests run */
  int ovr_tests=0, ovr_bytes=0;

  long max_data_size = ng_min(g_options.max_datasize + module->headerlen, module->max_datasize);

  /* get needed data buffer memory */
  ng_info(NG_VLEV1, "Allocating %d bytes data buffer", max_data_size);
  char *sbuf, *rbuf; // = (char*)module->malloc(max_data_size);
  NG_MALLOC(module, char*, max_data_size, sbuf);
  NG_MALLOC(module, char*, max_data_size, rbuf);

  ng_info(NG_VLEV2, "Initializing data buffer (make sure it's really allocated)");
  for (int i = 0; i < max_data_size; i++) { sbuf[i] = 0xff; rbuf[i] = 0xff; }

  int rank = g_options.mpi_opts->worldrank;
  int p = g_options.mpi_opts->worldsize; 
  if(p % 2 != 0) {
    ng_abort("this pattern needs an even number of ranks\n");
  }
  if(rank % 2 == 0) g_options.mpi_opts->partner = rank+1;
  else g_options.mpi_opts->partner = rank-1;

	FILE *outputfd, *fulloutputfd;
  if(rank % 2 == 0) {
    char fname[1024];
    char fname_full[1024];
    strncpy(fname, g_options.output_file, 1023);
    if(g_options.full_output_file){
      strncpy(fname_full, g_options.full_output_file, 1023);
    }
    if(p > 2) {
      char suffix[512];
      snprintf(suffix, 511, ".%i", g_options.mpi_opts->worldrank);
      strncat(fname, suffix, 1023);
      //strncat(fname_full, suffix, 1023);
    }

    // TODO: should be done globally in netgauge.c
    ng_info(NG_VNORM, "writing data to %s", fname);
    outputfd = open_output_file(fname);
    write_host_information(outputfd);

    if(g_options.full_output_file){
      fulloutputfd = open_output_file(fname_full);
      fprintf(fulloutputfd, "%s", "#size\trtt\n");
    }
  }
  
  /* buffer for header ... */
  char* txtbuf = (char *)malloc(2048 * sizeof(char));
  if (txtbuf == NULL) {
    ng_error("Could not allocate 2048 byte for output buffer");
    ng_exit(10);
  }
  memset(txtbuf, '\0', 2048);

  /* header printing */
  if(rank % 2 == 0) {
    // if very verbose - long output
    snprintf(txtbuf, 2047,
	    "## Netgauge v%s - mode %s - %i processes\n"
	    "##\n"
      "## A...message size [byte]\n"
      "##\n"
      "## B...minimum send blocking time\n"
      "## C...average send blocking time\n"
      "## D...median send blocking time\n"
      "## E...maximum send blocking time\n"
      "## F...standard deviation for send blocking time (stddev)\n"
      "## G...number of send blocking time values, that were bigger than avg + 2 * stddev.\n"
      "##\n"
      "## H...minimum RTT/2\n"
      "## I...average RTT/2\n"
      "## J...median RTT/2\n"
      "## K...maximum RTT/2\n"
      "## L...standard deviation for RTT/2 (stddev)\n"
      "## M...number of RTT/2 values, that were bigger than avg + 2 * stddev.\n"
      "##\n"
      "## N...minimum throughput [Mbit/sec]\n"
      "## O...average throughput [Mbit/sec]\n"
      "## P...median throughput [Mbit/sec]\n"
      "## Q...maximum throughput [Mbit/sec]\n"
      "##\n"
      "## A  -  B  C  D  E  (F G) - H  I  J  K  (L M)  -  N  O  P  Q\n",
      NG_VERSION,
      g_options.mode, p);
    fprintf(outputfd, "%s", txtbuf);

    if(rank == 0) {
      if (NG_VLEV2 & g_options.verbose) {
        printf("%s", txtbuf);
      } else
      // if verbose - short output
      if (NG_VLEV1 & g_options.verbose) {
        snprintf(txtbuf, 2047,
          "## Netgauge v%s - mode %s - 2 processes\n"
          "##\n"
          "## A...message size [byte]\n"
          "##\n"
          "## B...minimum send blocking time\n"
          "## C...average send blocking time\n"
          "## D...median send blocking time\n"
          "## E...maximum send blocking time\n"
          "##\n"
          "## F...minimum RTT/2\n"
          "## G...average RTT/2\n"
          "## H...median RTT/2\n"
          "## I...maximum RTT/2\n"
          "##\n"
          "## J...minimum throughput [Mbit/sec]\n"
          "## K...average throughput [Mbit/sec]\n"
          "## L...median throughput [Mbit/sec]\n"
          "## M...maximum throughput [Mbit/sec]\n"
          "##\n"
          "## A  -  B  C  D  E - F  G  H  I - J  K  L  M\n",
          NG_VERSION,
          g_options.mode);

        printf("%s", txtbuf);
        
      } else { // if not verbose - short output
        // no header ...
      }
    }
  }
  
  /* Outer test loop
   * - geometrically increments data_size (i.e. data_size = data_size * 2)
   *  (- geometrically decrements test_count) not yet implemented
   */
  for (data_size = g_options.min_datasize; data_size > 0;
	    get_next_testparams(&data_size, &test_count, &g_options, module)) {
    if(data_size == -1) goto shutdown;
    
    ++test_round;

    // the benchmark results
    std::vector<double> tblock, trtt, mytrtt, startt, endt;
    
    ng_info(NG_VLEV1, "Round %d: testing %d times with %d bytes:", test_round, test_count, data_size);
    // if we print dots ...
    if ( (rank==0) && (NG_VLEV1 & g_options.verbose) ) {
      printf("# ");
    }
 
    //if (!g_options.server) ng_statistics_start_round(&statistics, data_size);

    /* Inner test loop
     * - run the requested number of tests for the current data size
     * - but only if testtime does not exceed the max. allowed test time
     *   (only if max. test time is not zero)
     */
    test_time = 0;

    unsigned long conc_chunk_size = 0;
    MPI_Request* reqs = (MPI_Request*) malloc(sizeof(MPI_Request)*g_options.concurrent);
    MPI_Request* reqs_2 = (MPI_Request*) malloc(sizeof(MPI_Request)*g_options.concurrent);
    MPI_Status* statuses = (MPI_Status*) malloc(sizeof(MPI_Status)*g_options.concurrent);
    if(g_options.concurrent > 1){
      conc_chunk_size = data_size / g_options.concurrent;
    }



    MPI_Comm senders;
    double *sendbuf_start, *sendbuf_end, *recvbuf_start, *recvbuf_end;
    if(p > 2){
      MPI_Comm_split(MPI_COMM_WORLD, rank % 2, rank, &senders);
      sendbuf_start = (double*) malloc(sizeof(double)*test_count);
      sendbuf_end = (double*) malloc(sizeof(double)*test_count);      
      recvbuf_start = (double*) malloc(sizeof(double)*test_count);
      recvbuf_end = (double*) malloc(sizeof(double)*test_count);
    }

HRT_TIMESTAMP_T genesis;
      if(p > 2){
        MPI_Barrier(MPI_COMM_WORLD);
          HRT_GET_TIMESTAMP(genesis);
      }

    for (int test = -1 /* 1 warmup test */; test < test_count; test++) {
	
	    /* first statement to prevent floating exception */
      /* TODO: add cool abstract dot interface ;) */
	    if ( rank == 0 && (NG_VLEV1 & g_options.verbose) && ( test_count < NG_DOT_COUNT || !(test % (int)(test_count / NG_DOT_COUNT)) )) {
	      printf(".");
	      fflush(stdout);
	    }
      if(p > 2) MPI_Barrier(MPI_COMM_WORLD);
	
	    /* call the appropriate client or server function */
	    if (rank % 2 == 1) {
	        cur_test_time = time(NULL);
          /* do the server stuff basically a simple receive and send to
           * mirror the data in a ping-pong fashion ... this is not in a
           * subfunction since this may be performance critical. The
           * send and receive functions are also macros */

          MPI_Sendrecv(sbuf, data_size, MPI_BYTE, g_options.mpi_opts->partner, 
              11, rbuf, data_size, MPI_BYTE, g_options.mpi_opts->partner, 
              11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          MPI_Sendrecv(sbuf, data_size, MPI_BYTE, g_options.mpi_opts->partner, 
              11, rbuf, data_size, MPI_BYTE, g_options.mpi_opts->partner, 
              11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  
	        test_time += time(NULL) - cur_test_time;
	    } else {
	        /* wait some time for the server to get ready */
	        usleep(10);
	        cur_test_time = time(NULL);

          /* do the client stuff ... take time, send message, wait for
           * reply and take time  ... simple ping-pong scheme */
          HRT_TIMESTAMP_T t[3];
          unsigned long long tibl, tirtt;
  
          /* init statistics (TODO: what does this do?) */
          ng_statistics_test_begin(&statistics);

          HRT_GET_TIMESTAMP(t[0]);

          MPI_Sendrecv(sbuf, data_size, MPI_BYTE, g_options.mpi_opts->partner, 
              11, rbuf, data_size, MPI_BYTE, g_options.mpi_opts->partner, 
              11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          MPI_Sendrecv(sbuf, data_size, MPI_BYTE, g_options.mpi_opts->partner, 
              11, rbuf, data_size, MPI_BYTE, g_options.mpi_opts->partner, 
              11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

          /* get after-sending time */
          //HRT_GET_TIMESTAMP(t[1]);
  
          HRT_GET_TIMESTAMP(t[2]);
          HRT_GET_ELAPSED_TICKS(t[0],t[0],&tibl); // no blocking time!
          HRT_GET_ELAPSED_TICKS(t[0],t[2],&tirtt);
                      
          /* TODO: check received data */
  
          /* calculate results */
  
          if(test >= 0) {

            trtt.push_back(HRT_GET_USEC(tirtt/2));
            tblock.push_back(HRT_GET_USEC(tibl));
            if(p > 2){
              unsigned long long startt_2, endt_2;
              HRT_GET_ELAPSED_TICKS(genesis, t[0], &startt_2);
              HRT_GET_ELAPSED_TICKS(genesis, t[2], &endt_2);
	      sendbuf_start[test] = HRT_GET_USEC(startt_2);
	      sendbuf_end[test] = HRT_GET_USEC(endt_2);
	      //printf("Rank %d pushed %f %f\n", rank, sendbuf_start[test], sendbuf_end[test]);
            }else{
              mytrtt.push_back(HRT_GET_USEC(tirtt)/2);
            }
          }
	        test_time += time(NULL) - cur_test_time;
	    }

	    /* calculate overall statistics */
	    ovr_tests++;
	    ovr_bytes += data_size;
	 
	    /* measure test time and quit test if 
	     * test time exceeds max. test time
	     * but not if the max. test time is zero
	    */
	    if ( (g_options.max_testtime > 0) && 
	         (test_time > g_options.max_testtime) ) {
	      ng_info(NG_VLEV2, "Round %d exceeds %d seconds (duration %d seconds)", test_round, g_options.max_testtime, test_time);
	      ng_info(NG_VLEV2, "Test stopped at %d tests", test);
	      break;
	    }
	 
    }	/* end inner test loop */
    
	  if (rank % 2 ==0) {
      /* add linebreak if we made dots ... */
      if ( (NG_VLEV1 & g_options.verbose) ) {
        ng_info(NG_VLEV1, "\n");
      }

      /* output statistics - blocking time */
      double tblock_avg = std::accumulate(tblock.begin(), tblock.end(), (double)0)/(double)tblock.size(); 
      double tblock_min = *min_element(tblock.begin(), tblock.end()); 
      double tblock_max = *max_element(tblock.begin(), tblock.end()); 
      std::vector<double>::iterator nthblock = tblock.begin()+tblock.size()/2;
      nth_element(tblock.begin(), nthblock, tblock.end());
      double tblock_med = *nthblock;
      double tblock_var = standard_deviation(tblock.begin(), tblock.end(), tblock_avg);
      int tblock_fail = count_range(tblock.begin(), tblock.end(), tblock_avg-tblock_var*2, tblock_avg+tblock_var*2);

      /* output statistics - rtt time */
      double trtt_avg = std::accumulate(trtt.begin(), trtt.end(), (double)0)/(double)trtt.size(); 
      double trtt_min = *min_element(trtt.begin(), trtt.end()); 
      double trtt_max = *max_element(trtt.begin(), trtt.end()); 
      std::vector<double>::iterator nthrtt = trtt.begin()+trtt.size()/2;
      std::nth_element(trtt.begin(), nthrtt, trtt.end());
      double trtt_med = *nthrtt;
      double trtt_var = standard_deviation(trtt.begin(), trtt.end(), trtt_avg);
      int trtt_fail = count_range(trtt.begin(), trtt.end(), trtt_avg-trtt_var*2, trtt_avg+trtt_var*2);

      // generate long output for output file
      memset(txtbuf, '\0', 2048);
      snprintf(txtbuf, 2047,
	      "%ld - %.2lf %.2lf %.2lf %.2lf (%.2lf %i) - %.2lf %.2lf %.2lf %.2lf (%.2lf %i) - %.2lf %.2lf %.2lf %.2lf\n",
        data_size, /* packet size */

        tblock_min, /* minimum send blocking time */
        tblock_avg, /* average send blocking time */
        tblock_med, /* median send blocking time */
        tblock_max, /* maximum send blocking time */ 

        tblock_var, /* standard deviation */
        tblock_fail, /* how many are bigger than twice the standard deviation? */
        
        trtt_min, /* minimum RTT time */
        trtt_avg, /* average RTT time */
        trtt_med, /* median RTT time */
        trtt_max, /* maximum RTT time */
        
        trtt_var, /* standard deviation */
        trtt_fail, /* how many are bigger than twice the standard deviation? */

        data_size/trtt_max*8, /* minimum bandwidth */
        data_size/trtt_avg*8, /* average bandwidth */
        data_size/trtt_med*8, /* median bandwidth */
        data_size/trtt_min*8 /* maximum bandwidth */
        );
      fprintf(outputfd, "%s", txtbuf);
        
      // printf output *only* on rank 0!
	    if (rank ==0) {
        // if very verbose - long output
        if (NG_VLEV2 & g_options.verbose) {
          printf("%s", txtbuf);
          
        } else
        // if verbose - short output
        if (NG_VLEV1 & g_options.verbose) {
          memset(txtbuf, '\0', 2048);
          snprintf(txtbuf, 2047,
            "%ld - %.2lf %.2lf %.2lf %.2lf - %.2lf %.2lf %.2lf %.2lf - %.2lf %.2lf %.2lf %.2lf\n",
            data_size, /* packet size */

            tblock_min, /* minimum send blocking time */
            tblock_avg, /* average send blocking time */
            tblock_med, /* median send blocking time */
            tblock_max, /* maximum send blocking time */ 
            
            trtt_min, /* minimum RTT time */
            trtt_avg, /* average RTT time */
            trtt_med, /* median RTT time */
            trtt_max, /* maximum RTT time */
            
            data_size/trtt_max*8, /* minimum bandwidth */
            data_size/trtt_avg*8, /* average bandwidth */
            data_size/trtt_med*8, /* median bandwidth */
            data_size/trtt_min*8 /* maximum bandwidth */
            );
          printf("%s", txtbuf);
          
        } else
        // if not verbose - short output
        {
          memset(txtbuf, '\0', 2048);
          snprintf(txtbuf, 2047,
            "%ld bytes \t -> %.2lf us \t == %.2lf Mbit/s\n",
            data_size, /* packet size */
            //trtt_med, /* median RTT time */
            trtt_min, /* minimum RTT time */
            data_size/trtt_med*8 /* median bandwidth */
            );
          printf("%s", txtbuf);
          
        }
      }

      // Full output
      if(g_options.full_output_file){

        if(p > 2 && rank % 2 == 0){
          MPI_Reduce(sendbuf_start, (void*) recvbuf_start, test_count, MPI_DOUBLE, MPI_MIN, 0, senders);
          MPI_Reduce(sendbuf_end, (void*) recvbuf_end, test_count, MPI_DOUBLE, MPI_MAX, 0, senders);
          if(rank == 0){
            for(size_t idx = 0; idx < test_count; idx++){
	      //printf("Reduced %f %f\n", recvbuf_start[idx], recvbuf_end[idx]);
              mytrtt.push_back((recvbuf_end[idx] - recvbuf_start[idx])/2.0);
            }
          }
        }

        if(rank == 0){
          for(size_t idx = 0; idx < mytrtt.size(); idx++){
            double rtt = mytrtt[idx];
            fprintf(fulloutputfd, "%d\t%lf\n", data_size*(p/2), rtt);
          }
        }
      }
    }
    // write output file
      
    ng_info(NG_VLEV1, "\n");
    fflush(stdout);

    /* only a client does the stats stuff */
    //if (!g_options.server)
	  //  ng_statistics_finish_round(&statistics);
      
  }	/* end outer test loop */

  if(rank % 2 == 0) {
    fclose(outputfd);
    fclose(fulloutputfd);
  }


   
 shutdown:
   if(txtbuf) free(txtbuf);
    
}

} /* extern C */

#else
extern "C" {
int register_pattern_one_one_mpi_bidirect(void) {return 0;};
} /* extern C */
#endif
