#pragma once

#include "cfdispatcher.h"

class CFGroupDispatcher : public CFDispatcher {
protected:
	virtual void executeCFs(const DataFragmentBunch& seed);
	virtual void removeNotReadyArgs(DataFragmentBunch& args);

	void getGroups(const DataFragmentBunch& seed, CompFragmentGroupMap& cf_groups);	

public:
	CFGroupDispatcher(ICFScheduler *sched, const int& node) : CFDispatcher(sched, node) {}
	virtual ~CFGroupDispatcher() {}

};