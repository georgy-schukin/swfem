#include "fpcontroller.h"
#include <boost/foreach.hpp>

void FPController::addCF(CompFragment* cf, const int& node) {
	//cf->setGroupId(group_id);
	//cfs_storage.push_back(cf);
	//new_cfs.push_back(cf);	
	rts->getCFDispatcher()->addCF(cf, node);	
}

/*void FPController::addReductionCF(const size_t& red_id, ReductionCompFragment* cf, const size_t& group_id) {
	cf->setGroupId(group_id);
	cfs_storage.push_back(cf);
	new_cfs.push_back(cf);
	reduction_cfs[red_id].push_back(cf);	
}

void FPController::addEventCF(const size_t& event_id, EventCompFragment* cf, const size_t& group_id) {
	cf->setGroupId(group_id);
	cfs_storage.push_back(cf);
	new_cfs.push_back(cf);
	event_cfs[event_id].push_back(cf);	
}*/

/*void FPController::lockDFs(const DataFragmentPtrArray& dfs) {
	rts->getCFDispatcher()->lockDFs(dfs);
}

void FPController::unlockDFs(const DataFragmentPtrArray& dfs) {
	rts->getCFDispatcher()->unlockDFs(dfs);
}*/

void FPController::processCFs() {
	deleteDoneCFs(); // clear garbage first
	BOOST_FOREACH(ReductionCFsMap::value_type& p, reduction_cfs)
		rts->getReductionManager()->registerReductionCFs(p.first, p.second);
	/*BOOST_FOREACH(EventCFsMap::value_type& p, event_cfs)
		rts->getEventManager()->registerEventCFs(p.first, p.second);*/
	rts->getCFDispatcher()->addCFs(new_cfs);
	reduction_cfs.clear();
	event_cfs.clear();
	new_cfs.clear();
}

void FPController::deleteDoneCFs() {
	boost::ptr_list<CompFragment>::iterator it = cfs_storage.begin();
	while (it != cfs_storage.end()) 
		if (it->isDone())
			it = cfs_storage.erase(it);
		else it++;
}

double FPController::getReductionResult(const size_t& red_id) {
	return rts->getReductionManager()->waitForReductionResult(red_id);
}

/*void FPController::waitForEvent(const size_t& event_id) {
	return rts->getEventManager()->waitForEvent(event_id);
}*/

int FPController::getNodeId() {
	return rts->getCommunicator()->getRank();
}

int FPController::getNumOfNodes() {
	return rts->getCommunicator()->getSize();
}

void FPController::waitForAllDone() {
}
