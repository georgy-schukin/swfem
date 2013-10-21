#pragma once

#include "compfragment.h"
#include "data.h"
#include "meshfragment.h"

/**
* Count some coeffs on each time step before Jacoby method (diag + right hand side)
*/
class CFDiag: public CompFragment {
public:
	CFDiag() {}
	CFDiag(MeshFragment *mesh, DataCoef *data_coef, DataInteraction *data_interaction) {
		addArg(mesh);
		addArg(data_coef);
		addArg(data_interaction);
	}
	~CFDiag() {}

	void execute() {
		exec(getArg<MeshFragment>(0), getArg<DataCoef>(1), getArg<DataInteraction>(2));
	}

	void exec(MeshFragment& mesh, DataCoef& data_coef, DataInteraction& data_interaction);

	std::string toString() const {
		return "Diag " + CompFragment::toString();
	}
};
