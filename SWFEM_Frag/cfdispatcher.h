#pragma once

#include "icfdispatcher.h"
#include "idfdispatcher.h"
#include "icfexecutor.h"
#include "icflistener.h"
#include "idflistener.h"
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <vector>
#include <set>

/**
* CF Dispatcher - controls execution of computational fragments
*/
class CFDispatcher: public ICFDispatcher, public ICFListener, public IDFListener {
private:
	IDFDispatcher* dfDispatcher;
	ICFExecutor* cfExecutor;	
	boost::mutex mutex;
	boost::condition_variable cond;
	size_t cfs_count;
	int this_node;

protected:		
	void getGroups(const CompFragmentPtrArray& cfs, std::vector<CompFragmentGroup>& groups);
	void getGeneration(const DataFragmentPtrArray& dfs, CompFragmentPtrArray& cfs);
	//void pushArgsAndExec(const DataFragmentPtrArray& dfs);	
	//void pushArgsAndGetReadyCFsMultiple(const DataFragmentPtrArray& dfs, CompFragmentPtrArray& ready_cfs);
	//void pushArgsAndGetReadyCFs(const DataFragmentPtrArray& dfs, CompFragmentPtrArray& ready_cfs);	
	void getArgs(const CompFragmentPtrArray& cfs, DataFragmentPtrArray& args);
	void getReadyArgs(const CompFragmentPtrArray& cfs, std::set<DataFragment*>& ready_args);

	//void unlkDFs(const DataFragmentPtrArray& dfs);

public:
	CFDispatcher(IDFDispatcher* d, ICFExecutor *e, const int& node) : dfDispatcher(d), cfExecutor(e), this_node(node), cfs_count(0) {}
	~CFDispatcher() {}

	//void addCF(CompFragment* cf, const int& node);	
	//void addReductionCF(const size_t& red_id, ReductionCompFragment* cf, const int& node = -1);
	void addCFs(const CompFragmentPtrArray& cfs);	// add new cfs on the node	
	void waitForAllDone();

	//void onCFDone(CompFragment *cf);
	//void onCFsDone(const CompFragmentPtrArray& cfs);
	void onCFGroupDone(const CompFragmentGroup& group);
	//void onDFCreated(DataFragment *df);
	//void onDFsCreated(const vector<DataFragment*>& dfs);
	//void onDFsUnlocked(const DataFragmentPtrArray& dfs);	
};
