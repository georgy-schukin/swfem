#include "fragmentedprogram.h"
#include <boost/foreach.hpp>

void FragmentedProgram::addCF(CompFragment* cf, const size_t& group_id, const size_t& priority, const int& node) {	
	cf->setGroupId(group_id);
	cf->setPriority(priority);

	added_cfs.add(cf);
	cfs_storage.push_back(cf);
}

void FragmentedProgram::addReductionCF(ReductionCompFragment* cf, const size_t& red_id, const size_t& group_id, const size_t& priority, const int& node) {		
	cf->setReductionId(red_id);
	cf->setGroupId(group_id);
	cf->setPriority(priority);

	added_cfs.add(cf);
	reduction_cfs[red_id].push_back(cf);
	cfs_storage.push_back(cf);
}

void FragmentedProgram::processCFs() {
	//deleteDoneCFs(); // clear garbage first
	BOOST_FOREACH(ReductionCFsMap::value_type& p, reduction_cfs)
		rts->getReductionManager()->registerReductionCFs(p.first, p.second);

	rts->getCFDispatcher()->addCFs(added_cfs);

	reduction_cfs.clear();
	added_cfs = CompFragmentBunch(); // clear
}

void FragmentedProgram::deleteDoneCFs() {
	boost::ptr_list<CompFragment>::iterator it = cfs_storage.begin();
	while (it != cfs_storage.end()) 
		if (it->isDone())
			it = cfs_storage.erase(it);
		else it++;
}

double FragmentedProgram::getReductionResult(const size_t& red_id) {
	return rts->getReductionManager()->waitForReductionResult(red_id);
}

/*void FragmentedProgram::waitForEvent(const size_t& event_id) {
	return rts->getEventManager()->waitForEvent(event_id);
}*/

int FragmentedProgram::getNodeId() {
	return rts->getCommunicator()->getRank();
}

int FragmentedProgram::getNumOfNodes() {
	return rts->getCommunicator()->getSize();
}

void FragmentedProgram::waitForAllDone() {
}
