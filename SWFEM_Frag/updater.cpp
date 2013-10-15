#include "updater.h"
#include <boost/scoped_array.hpp>
#include <boost/foreach.hpp>

void Updater::update(const DataFragmentPtrArray& send, const DataFragmentPtrArray& recv, const int& tag, const int& node) {
	const unsigned int buf_size = computeBufSize(send);
	boost::scoped_array<char> buf(new char[buf_size]);

	pack(buf.get(), buf_size, send);		

	comm->sendRecvReplace(buf.get(), buf_size, tag, node, tag, node);	

	unpack(buf.get(), buf_size, recv);
}

unsigned int Updater::computeBufSize(const DataFragmentPtrArray& data) {
	unsigned int size = (data.size() + 1)*sizeof(unsigned int);
	BOOST_FOREACH(DataFragment* df, data) 
		size += ((Data*)df)->size()*3*sizeof(double);
	return size;
}

void Updater::pack(void *buf, const unsigned int& buf_size, const DataFragmentPtrArray& data) {
	unsigned int *num_buf = (unsigned int*)buf;		// part of buffer for data sizes
	double *data_buf = (double*)(num_buf + 1 + data.size());	// part of buffer for data
	num_buf[0] = data.size();	// write num of parts
	unsigned int k = 1;
	unsigned int step = 0;
	BOOST_FOREACH(DataFragment *df, data) {
		Data *dt = (Data*)df;
		num_buf[k++] = dt->size();	// write part sizes		
		BOOST_FOREACH(const NodeData& d, *dt) {
			data_buf[step] = d.u;	// write data
			data_buf[step + 1] = d.v;
			data_buf[step + 2] = d.xi;			
			step += 3;
		}
	}
}

void Updater::unpack(void *buf, const unsigned int& buf_size, const DataFragmentPtrArray& data) {
	const unsigned int *num_buf = (unsigned int*)buf;		// part of buffer for data sizes
	const unsigned int num = num_buf[0];	
	const double *data_buf = (double*)(num_buf + 1 + num);	// part of buffer for data
	unsigned int step = 0;
	for(unsigned int k = 0;k < num;k++) {		
		Data *dt = (Data*)data[k];
		dt->resize(num_buf[k + 1]);
		BOOST_FOREACH(NodeData& d, *dt) {			
			d.u = data_buf[step];
			d.v = data_buf[step + 1];
			d.xi = data_buf[step + 2];
			step += 3;
		}		
	}
}
