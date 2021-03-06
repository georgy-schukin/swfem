#include "cfgroupscheduler.h"
#include <boost/foreach.hpp>
#include <iostream>

void CFGroupScheduler::scheduleCFs(const CompFragmentBunch& cf_bunch) {
	const CompFragmentGroup& cf_group = static_cast<const CompFragmentGroup&>(cf_bunch);
	//std::cout << "Group " << cf_group.getGroupId() << std::endl;
	//BOOST_FOREACH(CompFragment *cf, cf_group)
		//std::cout << cf->toString() << std::endl;
	thread_pool->execCFs(cf_group, getThread(cf_group.getGroupId()));
}

size_t CFGroupScheduler::getThread(const size_t& group_id) {
	size_t thread_id = 0;
	if (!isGroupAlreadyPlaced(group_id, thread_id)) {	
		thread_id = getMinLoadedThread();
		placeGroup(group_id, thread_id);
	}
	return thread_id;
}

bool CFGroupScheduler::isGroupAlreadyPlaced(const size_t& group_id, size_t& thread_id) {
	for (size_t i = 0; i < group_placement.size(); i++) {
		if (group_placement[i].find(group_id) != group_placement[i].end()) {
			thread_id = i;
			return true;
		}
	}
	return false;
}

void CFGroupScheduler::placeGroup(const size_t& group_id, const size_t& thread_id) {
	group_placement[thread_id].insert(group_id);
}

size_t CFGroupScheduler::getMinLoadedThread() {
	size_t min_thread = 0;
	for (size_t i = 1; i < group_placement.size(); i++) {
		if (group_placement[i].size() < group_placement[min_thread].size())
			min_thread = i;
	}
	return min_thread;
}
