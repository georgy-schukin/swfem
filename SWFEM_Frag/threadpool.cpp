#include "threadpool.h"
#include <boost/foreach.hpp>

ThreadPool::ThreadPool(const unsigned int& num_of_threads, const int& rnk) {	
	for(unsigned int i = 0;i < num_of_threads;i++) {
		threads.push_back(new ExecThread(i, rnk));
	}	
}

ThreadPool::~ThreadPool() {	
}

void ThreadPool::execCFs(const CompFragmentPtrArray& cfs, const unsigned int& thread_id) {
	threads.at(thread_id).execCFs(cfs);
}

void ThreadPool::addCFListener(ICFListener *l) {
	BOOST_FOREACH(ExecThread& t, threads)
		t.addCFListener(l);
}


