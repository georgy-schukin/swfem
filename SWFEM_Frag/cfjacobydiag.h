#pragma once

#include "compfragment.h"
#include "data.h"
#include "mesh.h"

/**
* Count diag elems for Jacoby method
*/
class CFJacobyDiag: public CompFragment {
public:
	CFJacobyDiag() {}
	CFJacobyDiag(MeshFragment *mesh, Data *data, DataCoef *data_coef) {
		addArg(mesh);
		addArg(data);
		addArg(data_coef);
	}
	~CFJacobyDiag() {}

	void execute() {
		exec(getArg<MeshFragment>(0), getArg<Data>(1), getArg<DataCoef>(2));
	}

	void exec(MeshFragment& mesh, Data& data, DataCoef& data_coef);

	std::string toString() const {
		return "JacobyDiag " + CompFragment::toString();
	}
};
