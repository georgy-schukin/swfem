#pragma once

#include "icfscheduler.h"
#include "ithreadpool.h"
#include <map>
#include <set>
#include <vector>

class CFGroupScheduler : public ICFScheduler {
protected:
	std::vector<std::set<size_t> > group_placement; // placement of groups on threads
	IThreadPool *thread_pool;
	size_t num_of_threads;

protected:
	size_t getThread(const size_t& group_id);
	bool isGroupAlreadyPlaced(const size_t& group_id, size_t& thread_id);
	void placeGroup(const size_t& group_id, const size_t& thread_id);
	size_t getMinLoadedThread();

public:
	CFGroupScheduler(IThreadPool *pool) : 
	  thread_pool(pool), group_placement(pool->getNumOfThreads()), num_of_threads(pool->getNumOfThreads()) {}
	~CFGroupScheduler() {}

	//void scheduleCF(CompFragment *cf);
	//void scheduleCFs(CompFragmentPtrArray& cfs);
	void scheduleCFGroup(const CompFragmentGroup& group);
};
