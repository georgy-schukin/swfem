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
	~ThreadPool();

	//void execCF(CompFragment *cf, const size_t& thread_id);
	//void execCFs(const CompFragmentPtrArray& cfs, const size_t& thread_id);

	void execCFGroup(const CompFragmentGroup& group, const size_t& thread_id);

	void addCFListener(ICFListener *listener);
};
