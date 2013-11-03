#pragma once

#include "fragmentedprogram.h"
#include "data.h"
#include <vector>

/**
* MPI program for testing
*/
class SHFEMMPIProgram: public FragmentedProgram {
protected:		
	std::vector<size_t> start_y;	// indices of first point of the mesh in nodes by Y
	std::vector<size_t> ny;		// num of points in nodes by Y

	size_t mesh_size_x;
	size_t mesh_size_y;

	size_t node_rank;
	size_t node_size;

protected:
	void update(Data& data);
	void update(Data& data, size_t start, size_t num, int rank, int tag);
	void copyToBuffer(const Data& data, double* buf);
	void copyFromBuffer(Data& data, const double* buf);

public:
	SHFEMMPIProgram(IRuntimeSystem* s, size_t mx, size_t my);
	~SHFEMMPIProgram() {}

	void exec(size_t num_of_steps);
};
