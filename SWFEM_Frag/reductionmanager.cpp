#include "reductionmanager.h"
#include <boost/foreach.hpp>
#include <map>

/*void ReductionManager::registerReductionCF(size_t red_id, ReductionCompFragment *cf) {	
	ReductionsMap::iterator it = reductions.find(red_id);
	if (it == reductions.end()) {	// new reduction				
		reductions.insert(red_id, new Reduction(1)); // create new reducer for reduction		
	} else {	// redution already exists		
		it->second->changeSize(1);		// increment local size by 1
	}
	cf->setReductionId(red_id);
}*/

void ReductionManager::registerReductionCFs(const size_t& red_id, const ReductionCompFragmentPtrArray& cfs) {	
	ReductionMap::iterator it = reductions.find(red_id);
	if (it == reductions.end()) {	// new reduction						
		reductions.insert(const_cast<size_t&>(red_id), new Reduction(cfs.size())); // create new reducer for reduction		
	} else {	// redution already exists		
		it->second->addSize(cfs.size());		// increment local size by array size
	}
	//BOOST_FOREACH(ReductionCompFragment *cf, cfs)
		//cf->setReductionId(red_id);
}

double ReductionManager::waitForReductionResult(const size_t& red_id) {
	double local_result = reductions.at(red_id).waitForResult();
	double total_result = comm->allReduce(local_result);	// call internode comm for final result			
	reductions.erase(red_id); // delete reduction after getting result
	return total_result;
}

/*void ReductionManager::onCFDone(CompFragment *cf) {	
	if (cf->isReductionCF()) {
		ReductionCompFragment *rcf = (ReductionCompFragment*)cf;
		reductions.at(rcf->getReductionId()).processNewValue(rcf->getReductionValue());
	}		
}*/

void ReductionManager::onCFsDone(CompFragmentBunch& cf_bunch) {		
	size_t red_id = -1;	// ATTENTION: we think that there is only ONE active reduction among cfs
	size_t cnt = 0;
	double val = 0;
	//typedef std::map<size_t, std::pair<size_t, double> > ReductionValueMap;
	//ReductionMap red_map;
	BOOST_FOREACH(CompFragment *cf, cf_bunch) {
		if (cf->getType() == CompFragment::REDUCTION) {
			ReductionCompFragment *rcf = (ReductionCompFragment*)cf;
			red_id = rcf->getReductionId();
			//double &val = red_map[red_id].second;
			if (val < rcf->getReductionValue()) val = rcf->getReductionValue();	// get max
			cnt++;
			//red_map[red_id].first++;
		}
	}
	//BOOST_FOREACH(ReductionMap::value_type& p, red_map)
//		reductions.at(p.first).processNewValue(p.second.second, p.second.first);
	if (cnt > 0)
		reductions.at(red_id).processNewValue(val, cnt);			
}
