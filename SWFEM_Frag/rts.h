#pragma once

#include "irts.h"
#include "icfexecutor.h"
#include "icommunicator.h"
#include "logger.h"
#include <boost/scoped_ptr.hpp>

/*
* Runtime system - for execution of fragmented program
*/
class RuntimeSystem: public IRuntimeSystem {
private:	
	boost::scoped_ptr<ICFExecutor> cfExecutor;
	boost::scoped_ptr<ICFDispatcher> cfDispatcher;
	boost::scoped_ptr<IDFDispatcher> dfDispatcher;
	boost::scoped_ptr<IReductionManager> reductionManager;
	boost::scoped_ptr<IEventManager> eventManager;
	boost::scoped_ptr<ICommunicator> communicator;
	boost::scoped_ptr<Logger> logger;

public:
	RuntimeSystem(int argc, char **argv, unsigned int num_of_threads);
	~RuntimeSystem();	

	ICFDispatcher* getCFDispatcher();
	IDFDispatcher* getDFDispatcher();
	IReductionManager* getReductionManager();
	IEventManager* getEventManager();
	ICommunicator* getCommunicator();	
};
