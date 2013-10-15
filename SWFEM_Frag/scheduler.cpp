#include "scheduler.h"
#include "datafragment.h"
#include <boost/foreach.hpp>
#include <iostream>

Scheduler::Scheduler(const unsigned int& nt) : num_of_threads(nt), step(0) {	
	//thread_weight.resize(num_of_threads, 0);	
}

/*unsigned int Scheduler::scheduleCF(CompFragment *cf) {	
	vector<unsigned int> t_weight(num_of_threads, 0);
	unsigned int new_dfs_weight = 0;
	unsigned int old_dfs_weight = 0;
	BOOST_FOREACH(const RemotePtr& arg, cf->getArgs()) {
		const unsigned int df_id = arg.getId();
		const unsigned int df_weight = ((DataFragment*)arg.getPtr())->getWeight();		
		if (dfs_placement.find(df_id) != dfs_placement.end()) {	// dfs was placed before
			t_weight[dfs_placement[df_id]] += df_weight;
			old_dfs_weight += df_weight;
		} else {	// this is new dfs
			new_dfs_weight += df_weight;
		}
	}

	unsigned int min_thread = getIndexWithMinValue(thread_weight);
	unsigned int max_thread = getIndexWithMaxValue(t_weight);
	unsigned int sched_thread = (new_dfs_weight > old_dfs_weight ? min_thread : max_thread);

	BOOST_FOREACH(const RemotePtr& arg, cf->getArgs())
		dfs_placement[arg.getId()] = sched_thread;		
	thread_weight[sched_thread] += (old_dfs_weight + new_dfs_weight);

	//cout << sched_thread << endl;	

	static unsigned int thread = 0;
	unsigned int sched_thread = thread;
	thread = (thread + 1) % num_of_threads;
	return sched_thread;
}*/

void Scheduler::scheduleCFs(const CompFragmentPtrArray& cfs, std::vector<unsigned int>& thread_ids) {
	//static unsigned int step = 0;
	thread_ids.resize(cfs.size());
	for(unsigned int i = 0;i < cfs.size();i++)
		thread_ids[i] = (i + step) % num_of_threads;
	step = (step + cfs.size()) % num_of_threads;
}

unsigned int Scheduler::getIndexWithMinValue(const std::vector<unsigned int>& v) {
	unsigned int min_index = 0;
	unsigned int min_value = v[0];
	for(unsigned int i = 1;i < v.size();i++) {
		if(v[i] < min_value) {
			min_value = v[i];
			min_index = i;
		}
	}
	return min_index;
}

unsigned int Scheduler::getIndexWithMaxValue(const std::vector<unsigned int>& v) {
	unsigned int max_index = 0;
	unsigned int max_value = v[0];
	for(unsigned int i = 1;i < v.size();i++) {
		if(v[i] > max_value) {
			max_value = v[i];
			max_index = i;
		}
	}
	return max_index;
}
