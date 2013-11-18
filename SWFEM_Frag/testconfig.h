#pragma once

#include <string>

class TestConfig {
public:
	enum TestType {
		FRAG = 0,
		MPI,
		SEQ
	};

private:
	class ArgParser {
	private:
		int argc;
		char **argv;
		size_t current_arg;
    
	public:
		ArgParser(int ac, char **av) : argc(ac), argv(av), current_arg(1) {}
		~ArgParser() {}     		

		size_t nextArg(const size_t& dflt) {			
			const size_t arg_value = (argc > current_arg) ? atoi(argv[current_arg]) : dflt;
			current_arg++;
			return arg_value;
		}
};

protected:
	TestType test_type;	
	size_t mesh_size_x;
	size_t mesh_size_y;
	size_t fragment_num_x;
	size_t fragment_num_y;
	size_t num_of_exec_threads;
	size_t num_of_time_steps;
	bool use_groups;
	bool use_logging;

public:
	TestConfig();
	TestConfig(int argc, char **argv);
	~TestConfig() {}

	void setTestType(const TestType& type) {
		test_type = type;
	}

	void setMeshSizeByX(const size_t& size) {
		mesh_size_x = size;
	}

	void setMeshSizeByY(const size_t& size) {
		mesh_size_y = size;
	}

	void setNumOfFragmentsByX(const size_t& num) {
		fragment_num_x = num;
	}

	void setNumOfFragmentsByY(const size_t& num) {
		fragment_num_y = num;
	}

	void setNumOfExecThreads(const size_t& num) {
		num_of_exec_threads = num;
	}

	void setNumOfTimeSteps(const size_t& num) {
		num_of_time_steps = num;
	}

	void setGrouping(const bool& use) {
		use_groups = use;
	}

	void setLogging(const bool& use) {
		use_logging = use;
	}

	const TestType& getTestType() const {
		return test_type;
	}

	const size_t& getMeshSizeByX() const {
		return mesh_size_x;
	}

	const size_t& getMeshSizeByY() const {
		return mesh_size_y;
	}

	const size_t& getNumOfFragmentsByX() const {
		return fragment_num_x;
	}

	const size_t& getNumOfFragmentsByY() const {
		return fragment_num_y;
	}

	const size_t& getNumOfExecThreads() const {
		return num_of_exec_threads;
	}

	const size_t& getNumOfTimeSteps() const {
		return num_of_time_steps;
	}

	const bool& getGrouping() const {
		return use_groups;
	}

	const bool& getLogging() const {
		return use_logging;
	}

	std::string toString(const size_t& num_of_nodes) const;
};
