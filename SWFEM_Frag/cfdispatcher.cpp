#include "cfdispatcher.h"
#include <boost/foreach.hpp>
#include <iostream>
#include <set>

void CFDispatcher::addCFs(const CompFragmentBunch& cf_bunch) {
	boost::unique_lock<boost::mutex> lock(mutex);

	BOOST_FOREACH(CompFragment *cf, cf_bunch) {
		BOOST_FOREACH(DataFragment *df, cf->getArgs()) {
			df->getRoute().addPoint(DataFragmentRoute::RoutePoint(cf, this_node));
			//std::cout << df << " add arg" << cf->toString() << std::endl;
		}
		//std::cout << "Add " << cf->toString() << std::endl;
	}

	cfs_count += cf_bunch.size();

	executeCFs(cf_bunch.getArgs());
}

void CFDispatcher::executeCFs(const DataFragmentBunch& seed) {	
	DataFragmentBunch ready_args = seed;
	removeNotReadyArgs(ready_args);

	CompFragmentPtrArray ready_cfs;
	getGeneration(ready_args, ready_cfs);

	if (ready_cfs.size() > 0) {
		CompFragmentBunch cf_bunch(ready_cfs);
		//cf_bunch.lockArgs();
		cf_scheduler->scheduleCFs(cf_bunch);
	}
}

void CFDispatcher::getGeneration(const DataFragmentBunch& args, CompFragmentPtrArray& ready_cfs) {
	BOOST_FOREACH(DataFragment *df, args) {
		if (df->isReady()) {			
			const DataFragmentRoute::RoutePoint next_point = df->getRoute().getNextPoint();
			CompFragment *cf = next_point.getCF();			
			//std::cout << "Next " << cf->toString() << std::endl;
			df->setCurrentGroup(cf->getGroupId());
			df->lock();
			if (cf->pushArgAndCheckReady(df)) {				
				ready_cfs.push_back(cf);
			}
		}
	}
}

void CFDispatcher::removeNotReadyArgs(DataFragmentBunch& args) {
	DataFragmentPtrArray args_to_remove;
	BOOST_FOREACH(DataFragment *df, args) {		
		if (!df->isReady())			
			args_to_remove.push_back(df);
	}

	BOOST_FOREACH(DataFragment *df, args_to_remove)
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
