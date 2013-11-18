#include "testconfig.h"
#include <sstream>

TestConfig::TestConfig() : test_type(TestConfig::SEQ), mesh_size_x(201), mesh_size_y(201), fragment_num_x(1), fragment_num_y(1), 
	num_of_exec_threads(1), num_of_time_steps(5), use_groups(false), use_logging(false) {}

TestConfig::TestConfig(int argc, char **argv) {
	TestConfig::ArgParser args(argc, argv);

	setTestType((TestConfig::TestType)args.nextArg(TestConfig::SEQ));
	setMeshSizeByX(args.nextArg(201)); // num of nodes in mesh by X
	setMeshSizeByY(args.nextArg(201)); // num of nodes in mesh by Y	
	setNumOfFragmentsByX(args.nextArg(1)); // num of fragments by X
	setNumOfFragmentsByY(args.nextArg(1));	 // num of fragments by Y
	setNumOfExecThreads(args.nextArg(1)); // num of exec threads to run fragments
	setNumOfTimeSteps(args.nextArg(5)); // num of time steps to do
	setGrouping((args.nextArg(0) != 0)); // use groups or not
	setLogging(false);
}

std::string TestConfig::toString(const size_t& num_of_nodes) const {

	const std::string mode_names[3] = {"FRAG", "MPI", "SEQ"};

	std::ostringstream out;
		out << "Mode: " << mode_names[getTestType()] << "\n" 
			<< "Nodes: " << num_of_nodes << "\n"
			<< "Threads: " << getNumOfExecThreads() << "\n"
			<< "Mesh: " << getMeshSizeByX() << " x " << getMeshSizeByY() << "\n"
			<< "Fragments: " << getNumOfFragmentsByX() << " x " << getNumOfFragmentsByY() << "\n"
			<< "Time steps: " << getNumOfTimeSteps() << "\n"
			<< "Use groups: " << getGrouping() << "\n";
	    
	return out.str();
}
