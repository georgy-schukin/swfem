#pragma once

#include "icfexecutor.h"
#include "ithreadpool.h"
#include "icflistener.h"
#include "ischeduler.h"
#include <boost/scoped_ptr.hpp>
#include <boost/thread/mutex.hpp>

/**
 * Executor of comp fargments
 */
class CFExecutor: public ICFExecutor {
protected:
	boost::scoped_ptr<IThreadPool> threadPool;
	boost::scoped_ptr<IScheduler> scheduler;	
	boost::mutex mutex;
	size_t num_of_threads;

public:
	CFExecutor(const size_t& num_of_threads, const int& rank);
	~CFExecutor() {}

	//void execCF(CompFragment *cf);
	void execCFs(const CompFragmentPtrArray& cfs);
	void addCFListener(ICFListener *l);	
};
