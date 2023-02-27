/*Copyright 2017 Intel Corporation.

The source code, information and material ("Material") contained herein is owned 
by Intel Corporation or its suppliers or licensors, and title to such Material 
remains with Intel Corporation or its suppliers or licensors. The Material 
contains proprietary information of Intel or its suppliers and licensors. The 
Material is protected by worldwide copyright laws and treaty provisions. 
No part of the Material may be used, copied, reproduced, modified, published, 
uploaded, posted, transmitted, distributed or disclosed in any way without 
Intel's prior express written permission. No license under any patent, copyright 
or other intellectual property rights in the Material is granted to or conferred 
upon you, either expressly, by implication, inducement, estoppel or otherwise. 
Any license under such intellectual property rights must be express and approved 
by Intel in writing.

Unless otherwise agreed by Intel in writing, you may not remove or alter this 
notice or any other notice embedded in Materials by Intel or Intel's suppliers or 
licensors in any way.
*/


// Note: A copy of the license is included in the LICENSE file that accompanies the
// software.



#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <omp.h>
#include <time.h>
#ifndef	USE_DOUBLE
#define FLOAT	float
#define GEMM	sgemm_
#else
#define FLOAT	double
#define GEMM	dgemm_
#endif

void GEMM(char *, char *, int *, int *, int *, FLOAT *, FLOAT *, int *, FLOAT *, int *, FLOAT *, FLOAT *, int *);

#define LOOP	40 //number of executions
#define THEO_PEAK 0 // theo peak of the current system

int main(int argc, char **argv) {

  int m, i, j;
  FLOAT *a, *b, *c;
  FLOAT alpha = 1.;
  FLOAT beta  = 1.;
  double gflops, dstart, dstop;

  if (argc <= 1) {
    printf("Please specify problem size.\n");
    exit(1);
  }

  m = atoi(argv[1]);

  gflops = 2. * (double)m * (double)m * (double)m;

  a = (FLOAT *)memalign(128, (size_t)m * (size_t)m * sizeof(FLOAT));
  if (a == (FLOAT *)NULL) {
    printf("Out of memory for A matrix\n");
    exit(1);
  }
  b = (FLOAT *)memalign(128, (size_t)m * (size_t)m * sizeof(FLOAT));
  if (b == (FLOAT *)NULL) {
    printf("Out of memory for B matrix\n");
    exit(1);
  }
  c = (FLOAT *)memalign(128, (size_t)m * (size_t)m * sizeof(FLOAT));
  if (c == (FLOAT *)NULL) {
    printf("Out of memory for C matrix\n");
    exit(1);
  }

  for (j = 0; j < m; j ++) {
    for (i = 0; i < m; i ++) {
      a[i + (size_t)j * (size_t)m] = rand() / RAND_MAX - 0.5;
      b[i + (size_t)j * (size_t)m] = rand() / RAND_MAX - 0.5;
      c[i + (size_t)j * (size_t)m] = rand() / RAND_MAX - 0.5;
    }
  }

  GEMM("N", "N", &m, &m, &m, &alpha, a, &m, b, &m, &beta, c, &m);

  dstart = omp_get_wtime();
  struct timespec start_tv, end_tv;
  for (i = 0; i < LOOP; i ++) {
    //addedd local timing (not using omp time)
    
    //    double dstart2 =  omp_get_wtime();
    clock_gettime(CLOCK_REALTIME, &start_tv);
    GEMM("N", "N", &m, &m, &m, &alpha, a, &m, b, &m, &beta, c, &m);
    //double dstop2 = omp_get_wtime();
    clock_gettime(CLOCK_REALTIME, &end_tv);
    // time in seconds
    double start_t = start_tv.tv_sec + start_tv.tv_nsec * 1e-9;
    double end_t = end_tv.tv_sec + end_tv.tv_nsec * 1e-9;
    // Verbose
    // old omp time
    //printf("DGEMM Performance N = %6d : %10.4f GF\n", m, gflops / (dstop2 - dstart2) * 1.e-9);
    //printf("DGEMM Time N = %6d : %10.4f secs\n", m, (dstop2 - dstart2));

    //Non-verbose: matr size, time(s), gflops, theopeak
    // old omp time
    //printf("%d\t%4.4f\t%1.4f\t%4.4f\n", m, (dstop2 - dstart2), gflops / (dstop2 - dstart2) * 1.e-9, THEO_PEAK);
    printf("%d\t%1.8f\t%4.4f\t%4.4f\n", m, (end_t-start_t), gflops / (end_t-start_t) * 1.e-9, THEO_PEAK);



  }

  dstop = omp_get_wtime();

  /*
#ifndef USE_DOUBLE
  printf("SGEMM Performance N = %6d : %10.4f GF\n", m, gflops / (dstop - dstart) * (double)LOOP * 1.e-9);
#else
  printf("DGEMM Performance N = %6d : %10.4f GF\n", m, gflops / (dstop - dstart) * (double)LOOP * 1.e-9);
  printf("DGEMM Time N = %6d : %10.4f secs\n", m, (dstop - dstart)/ (double)LOOP);
#endif
  */
  free(a);
  free(b);
  free(c);

  return 0;
}


