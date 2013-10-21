#pragma once

#include "fpcontroller.h"

/*
* Sequental program for testing
*/
class SHFEMSeqController: public FPController {
public:
	SHFEMSeqController(IRuntimeSystem* s) : FPController(s) {}
	~SHFEMSeqController() {}

	void exec(const size_t& mesh_size_x, const size_t& mesh_size_y, const size_t& num_of_steps);
};
