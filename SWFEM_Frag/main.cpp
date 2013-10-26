#include "shfemcontroller.h"
#include "shfemseqcontroller.h"
#include "shfemmpicontroller.h"
#include "rts.h"
#include "timer.h"
#include <sstream>
#include <stdio.h>

class Args {
private:
	int argc;
	char **argv;
    
public:
	Args(int ac, char **av) : argc(ac), argv(av) {}
	~Args() {} 
       
	size_t arg(int ind, size_t def) {
		return def;//(argc > ind) ? atoi(argv[ind]) : def;
	}
};

int main(int argc, char **argv) {
	Args a(argc, argv);
	const size_t mode = a.arg(1, 0);					// mode
	const size_t mesh_size_x = a.arg(2, 201);			// num of nodes in mesh by X
	const size_t mesh_size_y = a.arg(3, 201);			// num of nodes in mesh by Y	
	const size_t fragment_num_x = a.arg(4, 4);		// num of fragments by X
	const size_t fragment_num_y = a.arg(5, 4);		// num of fragments by Y
	const size_t num_of_exec_threads = a.arg(6, 1);	// num of exec threads to run fragments
	const size_t num_of_time_steps = a.arg(7, 5);		// num of time steps to do
		
	RuntimeSystem rts(argc, argv, num_of_exec_threads);	// create and start rts
	
	if(rts.getCommunicator()->getRank() == 0)
	    printf("%d nodes\n%d threads\n%d %d mesh\n%d %d fragments\n%d steps\n", 
	    rts.getCommunicator()->getSize(), num_of_exec_threads, 
	    mesh_size_x, mesh_size_y, fragment_num_x, fragment_num_y, num_of_time_steps);

	std::ostringstream out;

	Timer t;
	t.start();
	switch(mode) {	// which program to run
		case 0:	{	// fragmented program			
			SHFEMController(&rts, mesh_size_x, mesh_size_y, fragment_num_x, fragment_num_y).exec(num_of_time_steps);				
			break;
		}
		case 1: {	// MPI program			
			SHFEMMPIController(&rts, mesh_size_x, mesh_size_y).exec(num_of_time_steps);	
			break;
		}
		case 2: {	// sequental program			
			SHFEMSeqController(&rts).exec(mesh_size_x, mesh_size_y, num_of_time_steps);	
			break;
		}
	} 		
	double time = t.stop();
	out << rts.getCommunicator()->getRank() << " : Total " << time << std::endl;

	std::cout << out.str();

	return 0;
}
