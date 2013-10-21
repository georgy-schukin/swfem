#include "communicator.h"
#include "rts.h"
#include "cfdispatcher.h"
#include "dfdispatcher.h"
#include "cfexecutor.h"
#include "reductionmanager.h"
#include "eventmanager.h"

RuntimeSystem::RuntimeSystem(int argc, char **argv, size_t num_of_threads) {
	Communicator *comm = new Communicator(argc, argv);
	CFExecutor *cf_exec = new CFExecutor(num_of_threads, comm->getRank());
	DFDispatcher *df_disp = new DFDispatcher();
	CFDispatcher *cf_disp = new CFDispatcher(df_disp, cf_exec);
	ReductionManager *red_manager = new ReductionManager(comm);
	EventManager *event_manager = new EventManager();
	Logger *log = new Logger();

	communicator.reset(comm);
	cfExecutor.reset(cf_exec);
	dfDispatcher.reset(df_disp);
	cfDispatcher.reset(cf_disp);	
	reductionManager.reset(red_manager);
	eventManager.reset(event_manager);
	logger.reset(log);

	dfDispatcher->addDFListener(cf_disp);
	cfExecutor->addCFListener(red_manager);
	//cfExecutor->addCFListener(log);	// turn on logging
	cfExecutor->addCFListener(event_manager);
	cfExecutor->addCFListener(cf_disp);
}

RuntimeSystem::~RuntimeSystem() {
	cfDispatcher->waitForAllDone();
}

ICFDispatcher* RuntimeSystem::getCFDispatcher() {
	return cfDispatcher.get();
}

IDFDispatcher* RuntimeSystem::getDFDispatcher() {
	return dfDispatcher.get();
}

IReductionManager* RuntimeSystem::getReductionManager() {
	return reductionManager.get();
}

IEventManager* RuntimeSystem::getEventManager() {
	return eventManager.get();
}

ICommunicator* RuntimeSystem::getCommunicator() {
	return communicator.get();
}
