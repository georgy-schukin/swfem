#include "reductionmanager.h"
#include <boost/foreach.hpp>
#include <map>
#include <iostream>

void ReductionManager::registerReductionCFs(const size_t& red_id, const ReductionCompFragmentPtrArray& cfs) {	
	ReductionMap::iterator it = reductions.find(red_id);
	if (it == reductions.end()) {	// new reduction								
		reductions.insert(const_cast<size_t&>(red_id), new Reduction(cfs.size())); // create new reducer for reduction		
	} else {	// redution already exists	
		it->second->addSize(cfs.size());		// increment local size by array size
	}	
}

double ReductionManager::waitForReductionResult(const size_t& red_id) {
	ReductionMap::iterator it = reductions.find(red_id);
	if (it != reductions.end()) {		
		double local_result = it->second->waitForResult();		
		reductions.erase(red_id); // delete reduction after getting result
		return comm->allReduce(local_result);	// call internode comm for final result									
	}
	return 0;
}

void ReductionManager::onCFsDone(CompFragmentBunch& cf_bunch) {		
	//size_t red_id = -1;	// ATTENTION: we think that there is only ONE active reduction among cfs
	//size_t cnt = 0;
	//double val = 0;
	//typedef std::map<size_t, std::pair<size_t, double> > ReductionValueMap;
	//ReductionValueMap value_map;
	boost::unique_lock<boost::mutex> lock(mutex);
	BOOST_FOREACH(CompFragment *cf, cf_bunch) {
		if (cf->getType() == CompFragment::REDUCTION) {
			ReductionCompFragment *rcf = (ReductionCompFragment*)cf;
			//const size_t red_id = rcf->getReductionId();						
			reductions.at(rcf->getReductionId()).processNewValue(rcf->getReductionValue());			
			//double &val = red_map[red_id].second;
			//if (val < rcf->getReductionValue()) val = rcf->getReductionValue();	// get max
			//cnt++;
			//red_map[red_id].first++;
		}
	}
	//BOOST_FOREACH(ReductionMap::value_type& p, red_map)
//		reductions.at(p.first).processNewValue(p.second.second, p.second.first);
	//if (cnt > 0)
		//reductions.at(red_id).processNewValue(val, cnt);			
}
