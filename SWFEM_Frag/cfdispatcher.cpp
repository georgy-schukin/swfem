#include "cfdispatcher.h"
#include <boost/foreach.hpp>
#include <iostream>
#include <set>

void CFDispatcher::addCFs(const CompFragmentBunch& cf_bunch) {
	boost::unique_lock<boost::mutex> lock(mutex);

	BOOST_FOREACH(CompFragment *cf, cf_bunch) {
		//std::cout << "ADD " << cf->toString() << std::endl;
		BOOST_FOREACH(DataFragment *df, cf->getArgs()) {
			df->getRoute().addPoint(DataFragmentRoute::RoutePoint(cf, this_node));			
		}		
	}

	cfs_count += cf_bunch.size();

	executeCFs(cf_bunch.getArgs());
}

void CFDispatcher::executeCFs(const DataFragmentBunch& seed) {	
	CompFragmentBunch ready_cfs;
	getGeneration(seed, ready_cfs);

	if (ready_cfs.size() > 0) {		
		cf_scheduler->scheduleCFs(ready_cfs);
	}
}

void CFDispatcher::getGeneration(const DataFragmentBunch& args, CompFragmentBunch& ready_cfs) {
	BOOST_FOREACH(DataFragment *df, args) {
		CompFragment *next_cf = df->moveToNextCF();
		if (next_cf && next_cf->isReady()) { 		
			ready_cfs.add(next_cf);	
		}
	}
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
	
	BOOST_FOREACH(DataFragment *df, cf_bunch.getArgs())
		df->freeFromCF();

	//cf_bunch.unlockArgs();

	cfs_count -= cf_bunch.size();	
	if(cfs_count == 0) {
		cond.notify_all();
	} else {		
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
