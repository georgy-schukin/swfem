#include "communicator.h"
#include "rts.h"
#include "cfdispatcher.h"
#include "dfdispatcher.h"
#include "cfexecutor.h"
#include "cfscheduler.h"
#include "cfgroupscheduler.h"
#include "reductionmanager.h"
#include "threadpool.h"
//#include "eventmanager.h"

RuntimeSystem::RuntimeSystem(int argc, char **argv, size_t num_of_threads) {
	communicator.reset(new Communicator(argc, argv));
	//CFExecutor *cf_exec = new CFExecutor(num_of_threads, comm->getRank());
//	DFDispatcher *df_disp = new DFDispatcher();
	thread_pool.reset(new ThreadPool(num_of_threads, communicator->getRank()));
	cf_scheduler.reset(new CFGroupScheduler(thread_pool.get()));
	cf_dispatcher.reset(new CFDispatcher(cf_scheduler.get(), communicator->getRank()));
	reduction_manager.reset(new ReductionManager(communicator.get()));
	//EventManager *event_manager = new EventManager();
	logger.reset(new Logger());

	//communicator.reset(comm);
	//cf_executor.reset(cf_exec);
	//df_dispatcher.reset(df_disp);
	//cf_dispatcher.reset(cf_disp);	
	//reduction_manager.reset(red_manager);
	//eventManager.reset(event_manager);
	//logger.reset(log);

	//df_dispatcher->addDFListener(cf_disp);
	//cf_executor->addCFListener(reduction_manager.get());
	//cfExecutor->addCFListener(log);	// turn on logging
	//cf_executor->addCFListener(event_manager);
	//cf_executor->addCFListener(cf_disp);
	thread_pool->addCFListener((ICFListener*)cf_dispatcher.get());
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
