#include "rts.h"
#include "shfemprogram.h"
#include "shfemseqprogram.h"
#include "shfemmpiprogram.h"
#include "timer.h"
#include <sstream>
#include <stdio.h>

class Args {
private:
	int argc;
	char **argv;
	size_t current_arg;
    
public:
	Args(int ac, char **av) : argc(ac), argv(av), current_arg(1) {}
	~Args() {} 
       
	size_t arg(const int& ind, const size_t& def) {
		return def;//(argc > ind) ? atoi(argv[ind]) : def;
	}

	size_t arg(const size_t& def) {
		current_arg++;
		return def;//(argc > ind) ? atoi(argv[ind]) : def;
	}
};

enum RunMode {
	USE_FRAG = 0,
	USE_MPI,
	USE_SEQ
};

const std::string mode_names[3] = {"FRAG", "MPI", "SEQ"};

int main(int argc, char **argv) {

	Args a(argc, argv);
	const size_t mode = a.arg(USE_FRAG); // mode
	const size_t mesh_size_x = a.arg(201); // num of nodes in mesh by X
	const size_t mesh_size_y = a.arg(201); // num of nodes in mesh by Y	
	const size_t fragment_num_x = a.arg(8); // num of fragments by X
	const size_t fragment_num_y = a.arg(8);	 // num of fragments by Y
	const size_t num_of_exec_threads = a.arg(1); // num of exec threads to run fragments
	const size_t num_of_time_steps = a.arg(100); // num of time steps to do
	const bool use_groups = (a.arg(0) != 0);

	RuntimeSystem::Config conf;
	conf.num_of_threads = num_of_exec_threads;
	conf.use_groups = use_groups;
	conf.use_logging = false;

	RuntimeSystem rts(argc, argv, conf);	// create and start rts
	
	if(rts.getCommunicator()->getRank() == 0) {
		std::ostringstream out;
		out << "Mode: " << mode_names[mode] << "\n" 
			<< "Nodes: " << rts.getCommunicator()->getSize() << "\n"
			<< "Threads: " << num_of_exec_threads << "\n"
			<< "Mesh: " << mesh_size_x << " x " << mesh_size_y << "\n"
			<< "Fragments: " << fragment_num_x << " x " << fragment_num_y << "\n"
			<< "Time steps: " << num_of_time_steps << "\n"
			<< "Use groups: " << use_groups << "\n";
	    
		std::cout << out.str() << std::endl;
	}

	std::ostringstream out;

	Timer timer;
	timer.start();
	switch(mode) {	
		case USE_FRAG:	{	// fragmented program			
			SHFEMProgram(&rts, mesh_size_x, mesh_size_y, fragment_num_x, fragment_num_y).exec(num_of_time_steps);				
			break;
		}
		case USE_MPI: {	// MPI program			
			SHFEMMPIProgram(&rts, mesh_size_x, mesh_size_y).exec(num_of_time_steps);	
			break;
		}
		case USE_SEQ: {	// sequental program			
			SHFEMSeqProgram(&rts).exec(mesh_size_x, mesh_size_y, num_of_time_steps);	
			break;
		}
	} 		
	double time = timer.stop();
	out << rts.getCommunicator()->getRank() << " : Total " << time << std::endl;

	std::cout << out.str();

	return 0;
}
