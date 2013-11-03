#include "cfgroupdispatcher.h"
#include <boost/foreach.hpp>

void CFGroupDispatcher::executeCFs(const DataFragmentBunch& seed) {
	CompFragmentGroupMap cf_groups;
	getGroups(seed, cf_groups);

	BOOST_FOREACH(CompFragmentGroupMap::value_type& p, cf_groups) {
		CompFragmentGroup& group = p.second;
		group.lockArgs();
		cf_scheduler->scheduleCFs(group);
	}
}

void CFGroupDispatcher::getGroups(const DataFragmentBunch& seed, CompFragmentGroupMap& cf_groups) {
	DataFragmentBunch ready_args = seed;

	BOOST_FOREACH(DataFragment *df, ready_args)
		df->setCurrentGroup(DataFragment::NO_GROUP);

	removeNotReadyArgs(ready_args);

	CompFragmentPtrArray ready_cfs;
	while (!ready_args.isEmpty()) {		
		getGeneration(ready_args, ready_cfs);
		removeNotReadyArgs(ready_args);		
	}	

	BOOST_FOREACH(CompFragment *cf, ready_cfs) 
		cf_groups[cf->getGroupId()].add(cf);
}

void CFGroupDispatcher::removeNotReadyArgs(DataFragmentBunch& args) {
	DataFragmentPtrArray args_to_remove;
	BOOST_FOREACH(DataFragment *df, args) {
		bool remove_df = false;

		if (!df->isReady())
			remove_df = true;
		else {
			const size_t& curr_group = df->getCurrentGroup();
			if ((curr_group != DataFragment::NO_GROUP) && 
				(curr_group != df->getRoute().peekNextCF()->getGroupId()))
				remove_df = true;
		}

		if (remove_df)
			args_to_remove.push_back(df);
	}

	BOOST_FOREACH(DataFragment *df, args_to_remove)
		args.remove(df);
}
