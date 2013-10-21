#pragma once

#include "compfragment.h"
#include "data.h"
#include "meshfragment.h"

/**
* Count coeffs that are not depend from time
*/
class CFCoef: public CompFragment {
public:
	CFCoef() {}
	CFCoef(MeshFragment *mesh, DataCoef *data_coef) {
		addArg(mesh);
		addArg(data_coef);
	}
	~CFCoef() {}

	void execute() {
		exec(getArg<MeshFragment>(0), getArg<DataCoef>(1));
	}

	void exec(MeshFragment& mesh, DataCoef& data_coef);

	std::string toString() const {
		return "Coef " + CompFragment::toString();
	}
};
