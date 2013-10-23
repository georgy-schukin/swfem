#include "threadpool.h"
#include <boost/foreach.hpp>

ThreadPool::ThreadPool(const size_t& num_of_threads, const int& rnk) {	
	for(size_t i = 0;i < num_of_threads;i++) {
		threads.push_back(new ExecThread(i, rnk));
	}	
}

ThreadPool::~ThreadPool() {	
}

/*void ThreadPool::execCFs(const CompFragmentPtrArray& cfs, const size_t& thread_id) {
	threads.at(thread_id).execCFs(cfs);
}*/

void ThreadPool::execCFGroup(const CompFragmentGroup& group, const size_t& thread_id) {
	threads.at(thread_id).execCFGroup(group);
}

void ThreadPool::addCFListener(ICFListener *l) {
	BOOST_FOREACH(ExecThread& t, threads)
		t.addCFListener(l);
}


