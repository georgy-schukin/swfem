#include "communicator.h"
#include "rts.h"
#include "cfdispatcher.h"
#include "dfdispatcher.h"
#include "cfscheduler.h"
#include "cfgroupscheduler.h"
#include "reductionmanager.h"
#include "threadpool.h"
//#include "eventmanager.h"

RuntimeSystem::RuntimeSystem(int argc, char **argv, size_t num_of_threads) {
	communicator.reset(new Communicator(argc, argv));	
//	DFDispatcher *df_disp = new DFDispatcher();
	thread_pool.reset(new ThreadPool(num_of_threads, communicator->getRank()));
	cf_scheduler.reset(new CFScheduler(thread_pool.get()));
	cf_dispatcher.reset(new CFDispatcher(cf_scheduler.get(), communicator->getRank()));
	reduction_manager.reset(new ReductionManager(communicator.get()));
	//EventManager *event_manager = new EventManager();
	logger.reset(new Logger());
	
	//thread_pool->addCFListener(logger.get()); // add logging
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

/*IEventManager* RuntimeSystem::getEventManager() {
	return eventManager.get();
}*/

ICommunicator* RuntimeSystem::getCommunicator() {
	return communicator.get();
}
