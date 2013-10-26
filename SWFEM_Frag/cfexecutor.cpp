#include "cfexecutor.h"
#include "threadpool.h"
//#include "scheduler.h"
#include <boost/foreach.hpp>
#include <stdio.h>
#include <map>
#include <vector>

CFExecutor::CFExecutor(const size_t& nt, const int& rank) : num_of_threads(nt) {
	//threadPool.reset(new ThreadPool(num_of_threads, rank));
	//scheduler.reset(new Scheduler(num_of_threads));
}

/*void CFExecutor::execCF(CompFragment *cf) {
	//boost::unique_lock<boost::mutex> lock(mutex);
	size_t thread_id = scheduler->scheduleCF(cf); // get thread id from scheduler
	threadPool->execCF(cf, thread_id); // place cf for exec on specified thread
}*/

/*void CFExecutor::execCFs(const CompFragmentPtrArray& cfs) {	
	if (num_of_threads == 1) {	// there is only one thread
		threadPool->execCFs(cfs, 0);
	} else {	// there are several threads		
		std::vector<size_t> thread_ids;
		scheduler->scheduleCFs(cfs, thread_ids);	// call scheduler to schedule
		std::vector<CompFragmentPtrArray> tasks(num_of_threads);
		for (size_t i = 0; i < cfs.size(); i++)
			tasks[thread_ids[i]].push_back(cfs[i]);
		for (size_t t = 0; t < num_of_threads; t++) 
			if (!tasks[t].empty()) 
				threadPool->execCFs(tasks[t], t); // place cfs for exec on specified thread	
	}
	
	typedef std::map<size_t, CompFragmentPtrArray> CompFragmentGroupMap;

	CompFragmentGroupMap groups;
	BOOST_FOREACH(CompFragment *cf, cfs)
		groups[cf->getGroupId()].push_back(cf); // get groups of comp fragments

	std::vector<CompFragmentPtrArray> tasks(num_of_threads);
	BOOST_FOREACH(const CompFragmentGroupMap::value_type& p, groups) { // for each group
		CompFragmentPtrArray& task = tasks[p.first % num_of_threads]; // choose thread for a group
		task.insert(task.end(), p.second.begin(), p.second.end()); // place group on a thread
	}

	for (size_t i = 0; i < tasks.size(); i++)
		if (!tasks[i].empty())
			threadPool->execCFs(tasks[i], i); // place cfs for exec on specified thread
}

void CFExecutor::addCFListener(ICFListener *l) {
	threadPool->addCFListener(l);
}*/
