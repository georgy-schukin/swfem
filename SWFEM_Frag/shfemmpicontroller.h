#pragma once

#include "fpcontroller.h"
#include "data.h"
#include <vector>

/**
* MPI program for testing
*/
class SHFEMMPIController: public FPController {
protected:		
	std::vector<unsigned int> start_y;	// indices of first point of the mesh in nodes by Y
	std::vector<unsigned int> ny;		// num of points in nodes by Y

	unsigned int mesh_size_x;
	unsigned int mesh_size_y;

	unsigned int node_rank;
	unsigned int node_size;

protected:
	void update(Data& data);
	void update(Data& data, unsigned int start, unsigned int num, int rank, int tag);
	void copyToBuffer(const Data& data, double* buf);
	void copyFromBuffer(Data& data, const double* buf);

public:
	SHFEMMPIController(IRuntimeSystem* s, unsigned int mx, unsigned int my);
	~SHFEMMPIController() {}

	void exec(unsigned int num_of_steps);
};
