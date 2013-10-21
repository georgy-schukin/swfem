#pragma once

#include "compfragment.h"
#include "data.h"
#include "meshfragment.h"

/**
* Do iteration of Jacoby method for mesh fragment
*/ 
class CFJacobyMultDirect: public CompFragment {
public:
	CFJacobyMultDirect() {}
	CFJacobyMultDirect(MeshFragment *mesh, Data *data_new, Data *data, Data *data_prev, DataCoef *data_coef) {
		addArg(mesh);
		addArg(data_new);
		addArg(data);
		addArg(data_prev);
		addArg(data_coef);
	}
	~CFJacobyMultDirect() {}

	void execute() {
		exec(getArg<MeshFragment>(0), getArg<Data>(1), getArg<Data>(2), getArg<Data>(3), getArg<DataCoef>(4));
	}

	void exec(MeshFragment& mesh, Data& data_new, Data& data, Data& data_prev, DataCoef& data_coef);

	std::string toString() const {
		return "JacobyMult " + CompFragment::toString();
	}
};
