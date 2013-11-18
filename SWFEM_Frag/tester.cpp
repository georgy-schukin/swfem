#include "tester.h"
#include "rts.h"
#include "shfemprogram.h"
#include "shfemseqprogram.h"
#include "shfemmpiprogram.h"
#include "timer.h"

double Tester::run(int argc, char **argv) {

	RuntimeSystem::Config rts_conf;
	rts_conf.num_of_threads = config.getNumOfExecThreads();
	rts_conf.use_groups = config.getGrouping();
	rts_conf.use_logging = config.getLogging();

	RuntimeSystem rts(argc, argv, rts_conf);	// create and start rts
	
	if(rts.getCommunicator()->getRank() == 0) {	    
		std::cout << config.toString(rts.getCommunicator()->getSize()) << std::endl; // output config
	}	

	Timer timer;
	timer.start();

	switch(config.getTestType()) {	
		case TestConfig::FRAG:	{	// fragmented program			
			SHFEMProgram(&rts, config.getMeshSizeByX(), config.getMeshSizeByY(), 
				config.getNumOfFragmentsByX(), config.getNumOfFragmentsByY()).exec(config.getNumOfTimeSteps());				
			break;
		}
		case TestConfig::MPI: {	// MPI program			
			SHFEMMPIProgram(&rts, config.getMeshSizeByX(), config.getMeshSizeByY()).exec(config.getNumOfTimeSteps());	
			break;
		}
		case TestConfig::SEQ: {	// sequental program			
			SHFEMSeqProgram(&rts).exec(config.getMeshSizeByX(), config.getMeshSizeByY(), config.getNumOfTimeSteps());	
			break;
		}
	}

	double time = timer.stop();

	std::ostringstream out;
	out << rts.getCommunicator()->getRank() << " : Total " << time << std::endl;
	std::cout << out.str();
}