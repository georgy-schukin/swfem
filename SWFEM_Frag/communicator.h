#pragma once

#include <mpi.h>
#include "icommunicator.h"

class Communicator : public ICommunicator {
private:
	int rank;
	int size;
	MPI_Comm comm;
	double time;

public:
	Communicator(int argc, char **argv);
	~Communicator();

	void send(void *buf, const int& buf_size, const int& tag, const int& dst_rank);
	void recv(void *buf, const int& buf_size, const int& tag, const int& src_rank);
	void sendRecvReplace(void *buf, const int& buf_size, const int& dst_tag, const int& dst_rank, const int& src_tag, const int& src_rank);
	void sendRecv(void *sbuf, const int& sbuf_size, void *rbuf, const int& rbuf_size, const int& dst_tag, const int& dst_rank, const int& src_tag, const int& src_rank);	

	double allReduce(double& send);

	int getRank() const {
		return rank;
	}

	int getSize() const {
		return size;
	}
};