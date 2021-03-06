#pragma once

#include "icfdispatcher.h"
//#include "idfdispatcher.h"
#include "icfscheduler.h"
#include "icflistener.h"
//#include "idflistener.h"
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <vector>
#include <map>
#include <queue>

/**
* CF Dispatcher - controls execution of computational fragments
*/
class CFDispatcher: public ICFDispatcher, public ICFListener {
protected:	
	ICFScheduler* cf_scheduler;	
	boost::mutex mutex;
	boost::condition_variable cond;
	size_t cfs_count;
	int this_node;
	std::queue<DataFragmentBunch> seeds;

protected:		
	virtual void executeCFs(const DataFragmentBunch& seed);	
	void getGeneration(const DataFragmentBunch& args, CompFragmentBunch& ready_cfs);
		
public:
	CFDispatcher(ICFScheduler *sched, const int& node) : cf_scheduler(sched), this_node(node), cfs_count(0) {}
	virtual ~CFDispatcher() {}
	
	void addCFs(CompFragmentBunch& cf_bunch);	// add new cfs on the node	

	void waitForAllDone();
	
	void onCFsDone(CompFragmentBunch& cf_bunch);
};
