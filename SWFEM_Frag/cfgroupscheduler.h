#pragma once

#include "cfscheduler.h"
#include <map>
#include <set>
#include <vector>

class CFGroupScheduler : public CFScheduler {
protected:
	std::vector<std::set<size_t> > group_placement; // placement of groups on threads

protected:
	size_t getThread(const size_t& group_id);
	bool isGroupAlreadyPlaced(const size_t& group_id, size_t& thread_id);
	void placeGroup(const size_t& group_id, const size_t& thread_id);
	size_t getMinLoadedThread();

public:
	CFGroupScheduler(IThreadPool *pool) : CFScheduler(pool), group_placement(pool->getNumOfThreads()) {}
	~CFGroupScheduler() {}

	//void scheduleCF(CompFragment *cf);
	//void scheduleCFs(CompFragmentPtrArray& cfs);
	void scheduleCFGroup(const CompFragmentGroup& group);
};
