#include "cfdispatcher.h"
#include <boost/foreach.hpp>
#include <iostream>
#include <set>

void CFDispatcher::addCFs(const CompFragmentBunch& cf_bunch) {
	boost::unique_lock<boost::mutex> lock(mutex);

	cfs_count += cf_bunch.size();

	executeCFs(cf_bunch.getArgs());
}

void CFDispatcher::executeCFs(const DataFragmentBunch& seed) {
	CompFragmentGroupMap cf_groups;
	getGroups(seed, cf_groups);

	BOOST_FOREACH(CompFragmentGroupMap::value_type& p, cf_groups) {
		CompFragmentGroup& group = p.second;
		group.lockArgs();
		cf_scheduler->scheduleCFGroup(group);
	}
}

void CFDispatcher::getGroups(const DataFragmentBunch& seed, CompFragmentGroupMap& cf_groups) {
	DataFragmentBunch ready_args = seed;

	BOOST_FOREACH(DataFragment *df, ready_args)
		df->setCurrentGroup(DataFragment::NO_GROUP);

	clearNotReadyArgs(ready_args);

	CompFragmentPtrArray ready_cfs;
	while (!ready_args.isEmpty()) {		
		getGeneration(ready_args, cf_groups);
		clearNotReadyArgs(ready_args);		
	}		
}

void CFDispatcher::getGeneration(const DataFragmentBunch& args, CompFragmentGroupMap& cf_groups) {
	BOOST_FOREACH(DataFragment *df, args) {
		if (df->isReady()) {			
			DataFragmentRoute::RoutePoint& next_point = df->getRoute().getNextPoint();
			CompFragment *cf = next_point.getCF();
			const size_t group_id = cf->getGroupId();
			df->setCurrentGroup(group_id);
			if (cf->pushArgAndCheckReady(df)) {
				cf_groups[group_id].add(cf);
			}
		}
	}
}

void CFDispatcher::clearNotReadyArgs(DataFragmentBunch& args) {
	DataFragmentPtrArray args_to_clear;
	BOOST_FOREACH(DataFragment *df, args) 
		if (!df->isReady() || (df->getCurrentGroup() != df->getRoute().peekNextPoint().getCF()->getGroupId())) 
			args_to_clear.push_back(df);

	BOOST_FOREACH(DataFragment *df, args_to_clear)
		args.remove(df);
}

void CFDispatcher::waitForAllDone() {
	boost::unique_lock<boost::mutex> lock(mutex);
	while (cfs_count > 0) {
		cond.timed_wait(lock, boost::posix_time::seconds(1));
	}
}

void CFDispatcher::onCFsDone(CompFragmentBunch& cf_bunch) {
	boost::unique_lock<boost::mutex> lock(mutex);				

	BOOST_FOREACH(CompFragment *cf, cf_bunch)
		cf->setDone(); // mark cf as done		

	cfs_count -= cf_bunch.size();	
	if(cfs_count == 0) {
		cond.notify_all();
	} else {
		cf_bunch.unlockArgs();
		executeCFs(cf_bunch.getArgs());		
	}
}

/*void CFDispatcher::onDFsUnlocked(const DataFragmentPtrArray& dfs) {
	boost::unique_lock<boost::mutex> lock(mutex);
	pushArgsAndExec(dfs);
}

void CFDispatcher::getArgs(const CompFragmentPtrArray& cfs, DataFragmentPtrArray& args) {
	BOOST_FOREACH(CompFragment *cf, cfs)
		args.insert(args.end(), cf->getArgs().begin(), cf->getArgs().end());
}

void CFDispatcher::unlkDFs(const DataFragmentPtrArray& dfs) {
	BOOST_FOREACH(DataFragment *df, dfs) 
		df->unlock();
}

void CFDispatcher::lockDFs(const DataFragmentPtrArray& dfs) {
	boost::unique_lock<boost::mutex> lock(mutex);
	BOOST_FOREACH(DataFragment *df, dfs)
		df->lock();
}

void CFDispatcher::unlockDFs(const DataFragmentPtrArray& dfs) {
	boost::unique_lock<boost::mutex> lock(mutex);
	unlkDFs(dfs);
	pushArgsAndExec(dfs);
	//onDFsUnlocked(dfs);
}*/
