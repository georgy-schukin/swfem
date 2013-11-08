#pragma once

#include "cfdispatcher.h"

class CFGroupDispatcher : public CFDispatcher {
protected:
	typedef std::map<size_t, CompFragmentGroup> CompFragmentGroupMap;

protected:
	virtual void executeCFs(const DataFragmentBunch& seed);	

	void getGroups(const DataFragmentBunch& seed, CompFragmentGroupMap& cf_groups);	
	void getGenerationWithGroups(DataFragmentBunch& args, CompFragmentGroupMap& cf_groups, CompFragmentBunch& ready);	

public:
	CFGroupDispatcher(ICFScheduler *sched, const int& node) : CFDispatcher(sched, node) {}
	virtual ~CFGroupDispatcher() {}
};