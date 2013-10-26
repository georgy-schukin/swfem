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

/**
* CF Dispatcher - controls execution of computational fragments
*/
class CFDispatcher: public ICFDispatcher, public ICFListener {
private:
	typedef std::map<size_t, CompFragmentGroup> CompFragmentGroupMap;

private:
	//IDFDispatcher* df_dispatcher;
	ICFScheduler* cf_scheduler;	
	boost::mutex mutex;
	boost::condition_variable cond;
	size_t cfs_count;
	int this_node;

protected:		
	virtual void executeCFs(const DataFragmentBunch& seed);
	void getGroups(const DataFragmentBunch& seed, CompFragmentGroupMap& cf_groups);
	//void getGeneration(const DataFragmentPtrSet& dfs, CompFragmentPtrArray& ready_cfs);
	void getGeneration(const DataFragmentBunch& args, CompFragmentGroupMap& cf_groups);
	void clearNotReadyArgs(DataFragmentBunch& args);
	//void pushArgsAndExec(const DataFragmentPtrArray& dfs);	
	//void pushArgsAndGetReadyCFsMultiple(const DataFragmentPtrArray& dfs, CompFragmentPtrArray& ready_cfs);
	//void pushArgsAndGetReadyCFs(const DataFragmentPtrArray& dfs, CompFragmentPtrArray& ready_cfs);	
	//void getArgs(const CompFragmentPtrArray& cfs, DataFragmentPtrArray& args);
	//void getReadyArgs(const CompFragmentPtrArray& cfs, DataFragmentPtrSet& ready_args);

	//void unlkDFs(const DataFragmentPtrArray& dfs);

public:
	CFDispatcher(ICFScheduler *sched, const int& node) : cf_scheduler(sched), this_node(node), cfs_count(0) {}
	~CFDispatcher() {}

	//void addCF(CompFragment* cf, const int& node);	
	//void addReductionCF(const size_t& red_id, ReductionCompFragment* cf, const int& node = -1);
	//void addCFs(const CompFragmentPtrArray& cfs);	// add new cfs on the node	
	void addCFs(const CompFragmentBunch& cf_bunch);	// add new cfs on the node	

	void waitForAllDone();

	//void onCFDone(CompFragment *cf);
	//void onCFsDone(const CompFragmentPtrArray& cfs);
	void onCFsDone(CompFragmentBunch& cf_bunch);
	//void onDFCreated(DataFragment *df);
	//void onDFsCreated(const vector<DataFragment*>& dfs);
	//void onDFsUnlocked(const DataFragmentPtrArray& dfs);	
};
