#pragma once

#include "compfragment.h"
#include "icflistener.h"
#include <vector>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/atomic.hpp>

/**
 * Thread for execution of comp fragments
 */
class ExecThread {
private:
	unsigned int thread_id;
	int rank;

	std::vector<CompFragment*> cfs_queue;
	std::vector<ICFListener*> cfListeners;	
	boost::thread thread;
	boost::mutex mutex;
	boost::condition_variable cond;		

	boost::atomic<bool> is_working;

protected:
	void threadFunc();

public:
	ExecThread(const unsigned int& t_id, const int& rnk);
	~ExecThread();

	//void start();
	//void stop();

	void execCFs(const CompFragmentPtrArray& cfs);
	void addCFListener(ICFListener *l);
};