#pragma once

#include "icfscheduler.h"
#include "ithreadpool.h"
#include <vector>
#include <set>
#include <map>

class CFScheduler : public ICFScheduler {
protected:
	IThreadPool *thread_pool;		
	//map<size_t, size_t> dfs_placement;	// affinity of data to threads
	//vector<size_t> thread_weight;		// accum weight of data on threads
	//int step;

protected:
	//size_t getIndexWithMinValue(const std::vector<size_t>& v);
	//size_t getIndexWithMaxValue(const std::vector<size_t>& v);

public:
	CFScheduler(IThreadPool *pool) : thread_pool(pool) {}
	virtual ~CFScheduler() {}

	//virtual void scheduleCF(CompFragment *cf);
	virtual void scheduleCFs(const CompFragmentBunch& cf_bunch);	
	//virtual void scheduleCFGroup(const CompFragmentGroup& cf_group);	
};
