#include "cfdispatcher.h"
#include <boost/foreach.hpp>
#include <iostream>
#include <set>

/*void CFDispatcher::addCFs(const CompFragmentPtrArray& cfs) {	
	boost::unique_lock<boost::mutex> lock(mutex);

	cfs_count += cfs.size();	
	
	BOOST_FOREACH(CompFragment *cf, cfs) 
		BOOST_FOREACH(DataFragment *df, cf->getArgs()) 
			df->pushRoutePoint(cf); // add to route	

	DataFragmentPtrArray args;
	getArgs(cfs, args);	
	pushArgsAndExec(args);
}*/

void CFDispatcher::addCF(CompFragment *cf, const int& node) {
	//if ((node == -1) || (node == this_node)) {
		BOOST_FOREACH(DataFragment *df, cf->getArgs()) 
			df->addRoutePoint(cf, node); // add to route	
	//}
}

void CFDispatcher::pushArgsAndExec(const DataFragmentPtrArray& dfs) {
	CompFragmentPtrArray ready_cfs;		
	//pushArgsAndGetReadyCFs(dfs, ready_cfs);	
	pushArgsAndGetReadyCFsMultiple(dfs, ready_cfs);	
	if (!ready_cfs.empty())
		cfExecutor->execCFs(ready_cfs);	
}

void CFDispatcher::pushArgsAndGetReadyCFsMultiple(const DataFragmentPtrArray& dfs, CompFragmentPtrArray& ready_cfs) {
	CompFragmentPtrArray next_cfs;	
	pushArgsAndGetReadyCFs(dfs, next_cfs); // get cfs for start shift

	while (!next_cfs.empty()) { // do next shifts
		ready_cfs.insert(ready_cfs.end(), next_cfs.begin(), next_cfs.end()); // add to total result
		DataFragmentPtrArray args;
		getArgs(next_cfs, args); // get args for next shift
		unlkDFs(args); // unlock args to do next shift		
		next_cfs.clear();
		pushArgsAndGetReadyCFs(args, next_cfs); // do another shift
	}	
}

void CFDispatcher::pushArgsAndGetReadyCFs(const DataFragmentPtrArray& dfs, CompFragmentPtrArray& ready_cfs) {	
	BOOST_FOREACH(DataFragment *df, dfs) // for each ready df		
		if (df->isReady()) {
			CompFragment *cf = df->popRoute(); // get next cf
			if (cf->pushArgAndCheckReady(df))  // push arg to cf and check if ready
				ready_cfs.push_back(cf); // add to ready				
			df->setLocked(true);			
		}	
}

void CFDispatcher::waitForAllDone() {
	boost::unique_lock<boost::mutex> lock(mutex);
	while (cfs_count > 0) {
		cond.timed_wait(lock, boost::posix_time::seconds(1));
	}
}

void CFDispatcher::onCFsDone(const CompFragmentPtrArray& cfs) {
	boost::unique_lock<boost::mutex> lock(mutex);			

	DataFragmentPtrArray dfs;	
	getArgs(cfs, dfs);	
	unlkDFs(dfs);

	BOOST_FOREACH(CompFragment *cf, cfs)
		cf->setDone(); // mark cf as done		

	cfs_count -= cfs.size();	
	if(cfs_count == 0) {
		cond.notify_all();
	} else {
		pushArgsAndExec(dfs);
	}
}

void CFDispatcher::onDFsUnlocked(const DataFragmentPtrArray& dfs) {
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
}
