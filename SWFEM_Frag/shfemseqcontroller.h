#pragma once

#include "fpcontroller.h"

/*
* Sequental program for testing
*/
class SHFEMSeqController: public FPController {
public:
	SHFEMSeqController(IRuntimeSystem* s) : FPController(s) {}
	~SHFEMSeqController() {}

	void exec(const unsigned int& mesh_size_x, const unsigned int& mesh_size_y, const unsigned int& num_of_steps);
};
