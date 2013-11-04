#include "rts.h"
#include "cfgroupdispatcher.h"
#include "cfgroupscheduler.h"

RuntimeSystem::RuntimeSystem(int argc, char **argv, const size_t& num_of_threads, const bool& use_groups) {
	communicator.reset(new Communicator(argc, argv));	
//	DFDispatcher *df_disp = new DFDispatcher();
	thread_pool.reset(new ThreadPool(num_of_threads, communicator->getRank()));

	if (use_groups) {
		cf_scheduler.reset(new CFGroupScheduler(thread_pool.get()));
		cf_dispatcher.reset(new CFGroupDispatcher(cf_scheduler.get(), communicator->getRank()));
	} else {
		cf_scheduler.reset(new CFScheduler(thread_pool.get()));
		cf_dispatcher.reset(new CFDispatcher(cf_scheduler.get(), communicator->getRank()));
	}

	reduction_manager.reset(new ReductionManager(communicator.get()));
	//EventManager *event_manager = new EventManager();
	logger.reset(new Logger());
	
	thread_pool->addCFListener(logger.get()); // add logging	
	thread_pool->addCFListener(reduction_manager.get());
	thread_pool->addCFListener(cf_dispatcher.get());		
}

RuntimeSystem::~RuntimeSystem() {
	cf_dispatcher->waitForAllDone();
}

ICFDispatcher* RuntimeSystem::getCFDispatcher() {
	return cf_dispatcher.get();
}

/*IDFDispatcher* RuntimeSystem::getDFDispatcher() {
	return df_dispatcher.get();
}*/

IReductionManager* RuntimeSystem::getReductionManager() {
	return reduction_manager.get();
}

ICommunicator* RuntimeSystem::getCommunicator() {
	return communicator.get();
}
