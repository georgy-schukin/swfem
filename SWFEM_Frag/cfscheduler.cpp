#include "cfscheduler.h"
#include "datafragment.h"
#include <boost/foreach.hpp>
#include <iostream>
#include <vector>

void CFScheduler::scheduleCFs(const CompFragmentBunch& cf_bunch) {	
	static int thread = 0;
	if (thread_pool->getNumOfThreads() == 1) {
		thread_pool->execCFs(cf_bunch, 0);
	} else {
		std::vector<CompFragmentBunch> tasks(thread_pool->getNumOfThreads());
		BOOST_FOREACH(CompFragment *cf, cf_bunch) {
			tasks[thread].add(cf);
			thread = (thread + 1) % thread_pool->getNumOfThreads();
		}
		for (size_t i = 0; i < tasks.size(); i++)
			if (tasks[i].size() > 0)
				thread_pool->execCFs(tasks[i], i);
	}
}
