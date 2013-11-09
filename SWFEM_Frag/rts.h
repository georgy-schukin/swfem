#pragma once

#include "communicator.h"
#include "irts.h"
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
public:
	class Config {
	public:
		size_t num_of_threads;
		bool use_logging;
		bool use_groups;

	public:
		Config() : num_of_threads(1), use_logging(false), use_groups(false) {}
		~Config() {}
	};

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
	RuntimeSystem(int argc, char **argv, const Config& conf);
	virtual ~RuntimeSystem();	

	ICFDispatcher* getCFDispatcher();
	//IDFDispatcher* getDFDispatcher();
	IReductionManager* getReductionManager();
//	IEventManager* getEventManager();
	ICommunicator* getCommunicator();	
};
