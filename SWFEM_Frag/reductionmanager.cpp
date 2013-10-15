#include "reductionmanager.h"
#include <boost/foreach.hpp>
#include <map>

/*void ReductionManager::registerReductionCF(unsigned int red_id, ReductionCompFragment *cf) {	
	ReductionsMap::iterator it = reductions.find(red_id);
	if (it == reductions.end()) {	// new reduction				
		reductions.insert(red_id, new Reduction(1)); // create new reducer for reduction		
	} else {	// redution already exists		
		it->second->changeSize(1);		// increment local size by 1
	}
	cf->setReductionId(red_id);
}*/

void ReductionManager::registerReductionCFs(const unsigned int& red_id, const ReductionCompFragmentPtrArray& cfs) {	
	ReductionsMap::iterator it = reductions.find(red_id);
	if (it == reductions.end()) {	// new reduction				
		unsigned int rd_id = red_id;
		reductions.insert(rd_id, new Reduction(cfs.size())); // create new reducer for reduction		
	} else {	// redution already exists		
		it->second->changeSize(cfs.size());		// increment local size by array size
	}
	BOOST_FOREACH(ReductionCompFragment *cf, cfs)
		cf->setReductionId(red_id);
}

double ReductionManager::waitForReductionResult(const unsigned int& red_id) {
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

void ReductionManager::onCFsDone(const CompFragmentPtrArray& cfs) {		
	unsigned int red_id = -1;	// ATTENTION: we think that there is only ONE active reduction among cfs
	unsigned int cnt = 0;
	double val = 0;
	//typedef std::map<unsigned int, std::pair<unsigned int, double> > ReductionMap;
	//ReductionMap red_map;
	BOOST_FOREACH(CompFragment *cf, cfs) {
		if (cf->isReductionCF()) {
			ReductionCompFragment *rcf = (ReductionCompFragment*)cf;
			red_id = rcf->getReductionId();
			//double &val = red_map[red_id].second;
			if (val < rcf->getReductionValue()) val = rcf->getReductionValue();			
			cnt++;
			//red_map[red_id].first++;
		}
	}
	//BOOST_FOREACH(ReductionMap::value_type& p, red_map)
//		reductions.at(p.first).processNewValue(p.second.second, p.second.first);
	if (cnt > 0)
		reductions.at(red_id).processNewValue(val, cnt);			
}
