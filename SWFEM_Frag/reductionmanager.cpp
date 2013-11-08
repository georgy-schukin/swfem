#include "reductionmanager.h"
#include <boost/foreach.hpp>
#include <map>
#include <iostream>

void ReductionManager::registerReductionCFs(const size_t& red_id, const ReductionCompFragmentPtrArray& cfs) {	
	boost::unique_lock<boost::mutex> lock(mutex);
	ReductionMap::iterator it = reductions.find(red_id);
	if (it == reductions.end()) {	// new reduction								
		reductions.insert(const_cast<size_t&>(red_id), new Reduction(cfs.size())); // create new reducer for reduction		
	} else {	// redution already exists	
		it->second->addSize(cfs.size());		// increment local size by array size
	}	
}

double ReductionManager::waitForReductionResult(const size_t& red_id) {
	boost::unique_lock<boost::mutex> lock(mutex);
	ReductionMap::iterator it = reductions.find(red_id);
	if (it != reductions.end()) {	
		lock.unlock();
		double local_result = it->second->waitForResult();		
		lock.lock();
		reductions.erase(red_id); // delete reduction after getting result
		return comm->allReduce(local_result);	// call internode comm for final result									
	}
	return 0;
}

void ReductionManager::onCFsDone(CompFragmentBunch& cf_bunch) {			
	boost::unique_lock<boost::mutex> lock(mutex);
	BOOST_FOREACH(CompFragment *cf, cf_bunch) {
		if (cf->getType() == CompFragment::REDUCTION) {
			ReductionCompFragment *rcf = (ReductionCompFragment*)cf;			
			reductions.at(rcf->getReductionId()).processNewValue(rcf->getReductionValue());						
		}
	}	
}
