#pragma once

class ICommunicator {
public:
	virtual void send(void *buf, const int& buf_size, const int& tag, const int& dst_rank) = 0;
	virtual void recv(void *buf, const int& buf_size, const int& tag, const int& src_rank) = 0;
	virtual void sendRecvReplace(void *buf, const int& buf_size, const int& dst_tag, const int& dst_rank, const int& src_tag, const int& src_rank) = 0;
	virtual void sendRecv(void *sbuf, const int& sbuf_size, void *rbuf, const int& rbuf_size, const int& dst_tag, const int& dst_rank, const int& src_tag, const int& src_rank) = 0;	

	virtual double allReduce(double& send) = 0;

	virtual int getRank() const = 0;
	virtual int getSize() const = 0;

	virtual ~ICommunicator() {}
};