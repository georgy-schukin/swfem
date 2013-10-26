#include "threadpool.h"
#include <boost/foreach.hpp>

ThreadPool::ThreadPool(const size_t& num_of_threads, const int& rnk) {	
	for(size_t i = 0;i < num_of_threads;i++) {
		threads.push_back(new ExecThread(i, rnk));
	}	
}

ThreadPool::~ThreadPool() {	
}

void ThreadPool::execCFs(const CompFragmentBunch& cf_bunch, const size_t& thread_id) {
	threads.at(thread_id).execCFs(cf_bunch);
}

void ThreadPool::addCFListener(ICFListener *listener) {
	BOOST_FOREACH(ExecThread& t, threads)
		t.addCFListener(listener);
}


