#pragma once

#include "compfragment.h"
#include "data.h"
#include "mesh.h"

/**
* Initialize data
*/
class CFInit: public CompFragment {
protected:
	size_t start_x;
	size_t start_y;
public:
	CFInit() {}
	CFInit(MeshFragment *mesh, Data *data, DataCoef *data_coef) {		
		addArg(mesh);
		addArg(data);
		addArg(data_coef);
	}
	~CFInit() {}

	void execute() {
		exec(getArg<MeshFragment>(0), getArg<Data>(1), getArg<DataCoef>(2));
	}

	void exec(MeshFragment& mesh, Data& data, DataCoef& data_coef);

	std::string toString() const {
		return "Init " + CompFragment::toString();
	}
};
