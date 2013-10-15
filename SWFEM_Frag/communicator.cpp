#include <mpi.h>
#include "communicator.h"
#include "timer.h"
#include <iostream>
#include <stdio.h>

using namespace std;

Communicator::Communicator(int argc, char **argv) : time(0) {
	int required = MPI_THREAD_FUNNELED;
	int provided;
	MPI_Init_thread(&argc, &argv, required, &provided);
	//if (provided != required)
		//printf("MPI Error : get only %d\n", provided);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int periods = 0;	
	//MPI_Comm_dup(MPI_COMM_WORLD, &comm);
	MPI_Cart_create(MPI_COMM_WORLD, 1, &size, &periods, 0, &comm);
	MPI_Comm_rank(comm, &rank);
}

Communicator::~Communicator() {
	printf("%d : Comms %f\n", rank, time);
	MPI_Comm_free(&comm);
	MPI_Finalize();
}

void Communicator::send(void *buf, const int& buf_size, const int& tag, const int& dest_rank) {
	Timer t;
	t.start();
	MPI_Send(buf, buf_size, MPI_BYTE, dest_rank, tag, comm);
	time += t.stop();
}

void Communicator::recv(void *buf, const int& buf_size, const int& tag, const int& src_rank) {
	Timer t;
	t.start();
	MPI_Recv(buf, buf_size, MPI_BYTE, src_rank, tag, comm, MPI_STATUS_IGNORE);
	time += t.stop();
}

void Communicator::sendRecvReplace(void *buf, const int& buf_size, const int& dst_tag, const int& dst_rank, const int& src_tag, const int& src_rank) {	
	Timer t;
	t.start();
	MPI_Sendrecv_replace(buf, buf_size, MPI_BYTE, dst_rank, dst_tag, src_rank, src_tag, 
		comm,  MPI_STATUS_IGNORE);	
	time += t.stop();
}		
		
void Communicator::sendRecv(void *sbuf, const int& sbuf_size, void *rbuf, const int& rbuf_size, const int& dst_tag, const int& dst_rank, const int& src_tag, const int& src_rank) {	
	Timer t;
	t.start();
	MPI_Sendrecv(sbuf, sbuf_size, MPI_BYTE, dst_rank, dst_tag, rbuf, rbuf_size, MPI_BYTE, src_rank, src_tag, 
		comm,  MPI_STATUS_IGNORE);
	time += t.stop();
}

double Communicator::allReduce(double& send) {
	double recv;
	Timer t;
	t.start();
	MPI_Allreduce(&send, &recv, 1, MPI_DOUBLE, MPI_MAX, comm); 
	time += t.stop();
	return recv;
}

