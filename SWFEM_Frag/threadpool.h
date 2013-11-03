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
	ThreadPool(const size_t& num_of_threads, const int& rank);
	virtual ~ThreadPool();

	//void execCF(CompFragment *cf, const size_t& thread_id);
	//void execCFs(const CompFragmentPtrArray& cfs, const size_t& thread_id);

	void execCFs(const CompFragmentBunch& cf_bunch, const size_t& thread_id);

	size_t getNumOfThreads() const {
		return threads.size();
	}

	void addCFListener(ICFListener *listener);
};
