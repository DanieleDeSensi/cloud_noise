#include <mpi.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "../thread-pool/thpool.h"
#define STRIPING_FACTOR_MAX 64

static unsigned int striping_factor;
static unsigned int use_threads;
static threadpool thpool;

void read_env(){
  char* striping_factor_s = getenv("LIBSTRIPE_FACTOR");
  if(!striping_factor_s){
    striping_factor = 16;
  }else{
    striping_factor = atoi(striping_factor_s);
  }
  if(striping_factor > STRIPING_FACTOR_MAX){
    fprintf(stderr, "LIBSTRIPE_FACTOR %d is too high.", striping_factor);
    exit(-1);
  }

  char* use_threads_s = getenv("LIBSTRIPE_THREADS");
  if(!use_threads_s){
    use_threads = 0;
  }else{
    use_threads = atoi(use_threads_s);
    thpool = thpool_init(striping_factor);
  }
}

int MPI_Init(int *argc, char ***argv){
  read_env();
  return PMPI_Init(argc, argv);
}

int MPI_Init_thread( int *argc, char ***argv, int required, int *provided ){
  read_env();
  return PMPI_Init_thread(argc, argv, required, provided);
}

typedef enum{
  MPI_OPERATION_SEND = 0,
  MPI_OPERATION_RECV,
}operation_t;

typedef struct{
  void *buf;
  int count;
  MPI_Datatype datatype;
  int source;
  int dest;
  int tag;
  MPI_Comm comm;
  int* r;
  MPI_Status* status;
  operation_t op;
}sendrecv_args_t;

void MPI_Operation_Pool(sendrecv_args_t* args){
  if(args->op == MPI_OPERATION_SEND){
    *(args->r) = PMPI_Send(args->buf, args->count, args->datatype, args->dest, args->tag, args->comm);
  }else{
    *(args->r) = PMPI_Recv(args->buf, args->count, args->datatype, args->source, args->tag, args->comm, args->status);
  }
}

int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm){
  if(striping_factor == 1 || count < striping_factor){
    return PMPI_Send(buf, count, datatype, dest, tag, comm);
  }else{
    MPI_Request reqs[STRIPING_FACTOR_MAX];
    sendrecv_args_t targs[STRIPING_FACTOR_MAX];
    int stripe_size = count / striping_factor, stripe_size_f;
    int r = MPI_SUCCESS;
    size_t i;
    for(i  = 0; i < striping_factor; i++){
        if(i == striping_factor - 1){
          stripe_size_f += count - stripe_size * striping_factor;
        }else{
	        stripe_size_f = stripe_size;
	      }
        if(use_threads){
          targs[i].buf = (void*) buf + i*stripe_size;
          targs[i].count = stripe_size_f;
          targs[i].datatype = datatype;
          targs[i].dest = dest;
          targs[i].tag = tag;
          targs[i].comm = comm;
          targs[i].r = &r;
          targs[i].op = MPI_OPERATION_SEND;
          thpool_add_work(thpool, (void*) MPI_Operation_Pool, (void*) &(targs[i]));
        }else{
          r = PMPI_Isend(buf + i*stripe_size, stripe_size_f, datatype, dest, tag, comm, &reqs[i]);
          if(r != MPI_SUCCESS){
            return r;
          }
        }
    }
    if(use_threads){
      thpool_wait(thpool);
      size_t i;
      for(i = 0; i < striping_factor; i++){
        if(targs[i].r != MPI_SUCCESS){
          return *(targs[i].r);
        }
      }
      return MPI_SUCCESS;
    }else{
      return PMPI_Waitall(striping_factor, reqs, MPI_STATUSES_IGNORE);
    }
  }
}

// TODO: Status ignored when doing Irecv
int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status){
  if(striping_factor == 1 || count < striping_factor){
    return PMPI_Recv(buf, count, datatype, source, tag, comm, status);
  }else{
    MPI_Request reqs[STRIPING_FACTOR_MAX];
    sendrecv_args_t targs[STRIPING_FACTOR_MAX];
    int stripe_size = count / striping_factor, stripe_size_f;
    int r = MPI_SUCCESS;
    size_t i;
    for(i = 0; i < striping_factor; i++){
        if(i == striping_factor - 1){
          stripe_size_f += count - stripe_size * striping_factor;
        }else{
	        stripe_size_f = stripe_size;
  	    }
        if(use_threads){
          targs[i].buf = buf + i*stripe_size;
          targs[i].count = stripe_size_f;
          targs[i].datatype = datatype;
          targs[i].source = source;
          targs[i].tag = tag;
          targs[i].comm = comm;
	  targs[i].status = status;
          targs[i].r = &r;
          targs[i].op = MPI_OPERATION_RECV;
          thpool_add_work(thpool, (void*) MPI_Operation_Pool, (void*) &(targs[i]));
        }else{
          r = PMPI_Irecv(buf + i*stripe_size, stripe_size_f, datatype, source, tag, comm, &reqs[i]);
          if(r != MPI_SUCCESS){
            return r;
          }
        }
    }
    if(use_threads){
      thpool_wait(thpool);
      size_t i;
      for(i = 0; i < striping_factor; i++){
        if(targs[i].r != MPI_SUCCESS){
          return *(targs[i].r);
        }
      }
      return MPI_SUCCESS;
    }else{
      return PMPI_Waitall(striping_factor, reqs, MPI_STATUSES_IGNORE);
    }
  }
}

int MPI_Sendrecv(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                 int dest, int sendtag,
                 void *recvbuf, int recvcount, MPI_Datatype recvtype,
                 int source, int recvtag, MPI_Comm comm, MPI_Status * status){
  if(striping_factor == 1){
    return PMPI_Sendrecv(sendbuf, sendcount, sendtype, dest, sendtag, recvbuf, recvcount, recvtype, source, recvtag, comm, status);
  }else{
    MPI_Request reqs[STRIPING_FACTOR_MAX*2];
    // Send stuff
    int stripe_size_send = sendcount / striping_factor, stripe_size_recv = recvcount / striping_factor; 
    int stripe_size_send_f, stripe_size_recv_f;
    int r = MPI_SUCCESS;
    size_t i;
    for(i  = 0; i < striping_factor; i++){
        if(i == striping_factor - 1){
          stripe_size_send_f += sendcount - stripe_size_send * striping_factor;
          stripe_size_recv_f += recvcount - stripe_size_recv * striping_factor;
        }else{
	        stripe_size_send_f = stripe_size_send;
          stripe_size_recv_f = stripe_size_recv;
  	    }
        r = PMPI_Isend(sendbuf + i*stripe_size_send, stripe_size_send_f, sendtype, dest, sendtag, comm, &reqs[i*2]);
        if(r != MPI_SUCCESS){
            return r;
        }
        r = PMPI_Irecv(recvbuf + i*stripe_size_recv, stripe_size_recv_f, recvtype, source, recvtag, comm, &reqs[i*2+1]);
        if(r != MPI_SUCCESS){
            return r;
        }
    }
    return PMPI_Waitall(striping_factor*2, reqs, MPI_STATUSES_IGNORE);
  }
}
