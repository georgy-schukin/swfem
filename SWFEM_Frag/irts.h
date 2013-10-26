#pragma once

#include "icfdispatcher.h"
#include "idfdispatcher.h"
#include "ireductionmanager.h"
#include "icommunicator.h"

/**
* Generic runtime system interface
*/
class IRuntimeSystem {
public:
	virtual ICFDispatcher* getCFDispatcher() = 0;
	//virtual IDFDispatcher* getDFDispatcher() = 0;
	virtual IReductionManager* getReductionManager() = 0;
	//virtual IEventManager* getEventManager() = 0;	
	virtual ICommunicator* getCommunicator() = 0;

	virtual ~IRuntimeSystem() {}
};
