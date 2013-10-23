#pragma once

#include "irts.h"
#include "icfexecutor.h"
#include "icommunicator.h"
#include "ithreadpool.h"
#include "icfscheduler.h"
#include "logger.h"
#include <boost/scoped_ptr.hpp>

/*
* Runtime system - for execution of fragmented program
*/
class RuntimeSystem: public IRuntimeSystem {
private:	
	boost::scoped_ptr<ICFExecutor> cf_executor;
	boost::scoped_ptr<ICFDispatcher> cf_dispatcher;
	boost::scoped_ptr<IDFDispatcher> df_dispatcher;
	boost::scoped_ptr<IReductionManager> reduction_manager;
	//boost::scoped_ptr<IEventManager> event_manager;
	boost::scoped_ptr<ICommunicator> communicator;
	boost::scoped_ptr<IThreadPool> thread_pool;
	boost::scoped_ptr<ICFScheduler> scheduler;
	boost::scoped_ptr<Logger> logger;	

public:
	RuntimeSystem(int argc, char **argv, size_t num_of_threads);
	~RuntimeSystem();	

	ICFDispatcher* getCFDispatcher();
	IDFDispatcher* getDFDispatcher();
	IReductionManager* getReductionManager();
	IEventManager* getEventManager();
	ICommunicator* getCommunicator();	
};
