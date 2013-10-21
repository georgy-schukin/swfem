#include "scheduler.h"
#include "datafragment.h"
#include <boost/foreach.hpp>
#include <iostream>

Scheduler::Scheduler(const size_t& nt) : num_of_threads(nt), step(0) {	
	//thread_weight.resize(num_of_threads, 0);	
}

/*size_t Scheduler::scheduleCF(CompFragment *cf) {	
	vector<size_t> t_weight(num_of_threads, 0);
	size_t new_dfs_weight = 0;
	size_t old_dfs_weight = 0;
	BOOST_FOREACH(const RemotePtr& arg, cf->getArgs()) {
		const size_t df_id = arg.getId();
		const size_t df_weight = ((DataFragment*)arg.getPtr())->getWeight();		
		if (dfs_placement.find(df_id) != dfs_placement.end()) {	// dfs was placed before
			t_weight[dfs_placement[df_id]] += df_weight;
			old_dfs_weight += df_weight;
		} else {	// this is new dfs
			new_dfs_weight += df_weight;
		}
	}

	size_t min_thread = getIndexWithMinValue(thread_weight);
	size_t max_thread = getIndexWithMaxValue(t_weight);
	size_t sched_thread = (new_dfs_weight > old_dfs_weight ? min_thread : max_thread);

	BOOST_FOREACH(const RemotePtr& arg, cf->getArgs())
		dfs_placement[arg.getId()] = sched_thread;		
	thread_weight[sched_thread] += (old_dfs_weight + new_dfs_weight);

	//cout << sched_thread << endl;	

	static size_t thread = 0;
	size_t sched_thread = thread;
	thread = (thread + 1) % num_of_threads;
	return sched_thread;
}*/

void Scheduler::scheduleCFs(const CompFragmentPtrArray& cfs, std::vector<size_t>& thread_ids) {
	//static size_t step = 0;
	thread_ids.resize(cfs.size());
	for(size_t i = 0;i < cfs.size();i++)
		thread_ids[i] = (i + step) % num_of_threads;
	step = (step + cfs.size()) % num_of_threads;
}

size_t Scheduler::getIndexWithMinValue(const std::vector<size_t>& v) {
	size_t min_index = 0;
	size_t min_value = v[0];
	for(size_t i = 1;i < v.size();i++) {
		if(v[i] < min_value) {
			min_value = v[i];
			min_index = i;
		}
	}
	return min_index;
}

size_t Scheduler::getIndexWithMaxValue(const std::vector<size_t>& v) {
	size_t max_index = 0;
	size_t max_value = v[0];
	for(size_t i = 1;i < v.size();i++) {
		if(v[i] > max_value) {
			max_value = v[i];
			max_index = i;
		}
	}
	return max_index;
}
