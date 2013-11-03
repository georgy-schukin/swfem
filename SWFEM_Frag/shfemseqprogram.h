#pragma once

#include "fragmentedprogram.h"

/*
* Sequental program for testing
*/
class SHFEMSeqProgram: public FragmentedProgram {
public:
	SHFEMSeqProgram(IRuntimeSystem* s) : FragmentedProgram(s) {}
	~SHFEMSeqProgram() {}

	void exec(const size_t& mesh_size_x, const size_t& mesh_size_y, const size_t& num_of_steps);
};
