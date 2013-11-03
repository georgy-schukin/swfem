#include "cfscheduler.h"
#include "datafragment.h"
#include <boost/foreach.hpp>
#include <iostream>

void CFScheduler::scheduleCFs(const CompFragmentBunch& cf_bunch) {
	//BOOST_FOREACH(CompFragment *cf, cf_bunch) 
		//std::cout << "Sched " << cf->toString() << std::endl;
	static int thread = 0;
	thread_pool->execCFs(cf_bunch, thread);
	thread = (thread + 1) % thread_pool->getNumOfThreads();
}
