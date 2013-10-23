#pragma once

#include "compfragment.h"
#include "compfragmentgroup.h"
#include "icflistener.h"
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/atomic.hpp>
#include <vector>
#include <queue>

/**
 * Thread for execution of comp fragments
 */
class ExecThread {
private:
	size_t thread_id;
	int this_node;

	std::vector<CompFragment*> cfs_queue;
	std::queue<CompFragmentGroup> cfs_groups;
	std::vector<ICFListener*> cf_listeners;	

	boost::thread thread;
	boost::mutex mutex;
	boost::condition_variable cond;		

	boost::atomic<bool> is_working;

protected:
	void threadFunc();

public:
	ExecThread(const size_t& thread_id, const int& this_node);
	~ExecThread();

	//void start();
	//void stop();

	//void execCFs(const CompFragmentPtrArray& cfs);
	void execCFGroup(const CompFragmentGroup& group);
	void addCFListener(ICFListener *listener);
};
