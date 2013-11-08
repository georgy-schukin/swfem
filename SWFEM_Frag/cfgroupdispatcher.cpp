#include "cfgroupdispatcher.h"
#include <boost/foreach.hpp>

void CFGroupDispatcher::executeCFs(const DataFragmentBunch& seed) {
	CompFragmentGroupMap cf_groups;

	getGroups(seed, cf_groups);

	BOOST_FOREACH(CompFragmentGroupMap::value_type& p, cf_groups) {
		CompFragmentGroup& group = p.second;
		group.setGroupId(p.first);
		//group.lockArgs();
		cf_scheduler->scheduleCFs(group);
	}
}

void CFGroupDispatcher::getGroups(const DataFragmentBunch& seed, CompFragmentGroupMap& cf_groups) {
	DataFragmentBunch args = seed;

	//BOOST_FOREACH(DataFragment *df, args)
		//df->setCurrentGroup(DataFragment::NO_GROUP);	
	
	while (!args.isEmpty()) {		
		CompFragmentBunch ready;
		//std::cout << "GENERATION" << std::endl;
		getGenerationWithGroups(args, cf_groups, ready);
		//ready.unlockArgs();
	}		
	//std::cout << "END\n" << std::endl;
}

void CFGroupDispatcher::getGenerationWithGroups(DataFragmentBunch& args, CompFragmentGroupMap& cf_groups, CompFragmentBunch& ready) {
	DataFragmentPtrArray args_to_remove;

	BOOST_FOREACH(DataFragment *df, args) {
		CompFragment *next_cf = df->moveToNextCFInTheSameGroup();
		if (next_cf) { // success move			
			if (next_cf->isReady()) {
				//std::cout << "READY " << next_cf->toString() << std::endl;
				cf_groups[next_cf->getGroupId()].add(next_cf);
				//ready.add(next_cf);
				//BOOST_FOREACH(DataFragment *df, next_cf->getArgs())
					//df->unlock();
			}
		} else {
			args_to_remove.push_back(df); // can't move - remove arg
		}
	}

	BOOST_FOREACH(DataFragment *df, args_to_remove)
		args.remove(df);
}

