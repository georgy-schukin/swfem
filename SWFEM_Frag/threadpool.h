#pragma once

#include "ithreadpool.h"
#include "icflistener.h"
#include "execthread.h"
#include <boost/ptr_container/ptr_vector.hpp>

/*
* Pool of threads for fragment execution
*/
class ThreadPool: public IThreadPool {
private:		
	boost::ptr_vector<ExecThread> threads;

public:
	ThreadPool(const unsigned int& num_of_threads, const int& rank);
	~ThreadPool();

	//void execCF(CompFragment *cf, unsigned int thread_id);
	void execCFs(const CompFragmentPtrArray& cfs, const unsigned int& thread_id);
	void addCFListener(ICFListener *l);
};
