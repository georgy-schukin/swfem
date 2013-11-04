#pragma once

#include "irts.h"
#include "communicator.h"
#include "threadpool.h"
#include "cfscheduler.h"
#include "cfdispatcher.h"
#include "reductionmanager.h"
#include "logger.h"
#include <boost/scoped_ptr.hpp>

/*
* Runtime system - for execution of fragmented program
*/
class RuntimeSystem: public IRuntimeSystem {
private:	
	//boost::scoped_ptr<ICFExecutor> cf_executor;
	boost::scoped_ptr<CFScheduler> cf_scheduler;
	boost::scoped_ptr<CFDispatcher> cf_dispatcher;
	//boost::scoped_ptr<IDFDispatcher> df_dispatcher;
	boost::scoped_ptr<ReductionManager> reduction_manager;
	//boost::scoped_ptr<IEventManager> event_manager;
	boost::scoped_ptr<Communicator> communicator;
	boost::scoped_ptr<ThreadPool> thread_pool;	
	boost::scoped_ptr<Logger> logger;	

public:
	RuntimeSystem(int argc, char **argv, const size_t& num_of_threads, const bool& use_groups = false);
	virtual ~RuntimeSystem();	

	ICFDispatcher* getCFDispatcher();
	//IDFDispatcher* getDFDispatcher();
	IReductionManager* getReductionManager();
//	IEventManager* getEventManager();
	ICommunicator* getCommunicator();	
};
