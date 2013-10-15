#pragma once

#include "reductioncompfragment.h"
#include "data.h"
#include "mesh.h"

/**
* Count part of local reduction
*/
class CFJacobyReduce: public ReductionCompFragment {
private:	
	double err_max;

public:
	CFJacobyReduce() {}
	CFJacobyReduce(MeshFragment *mesh, Data *data_new, Data *data, Data *data_diag) {
		addArg(mesh);
		addArg(data_new);
		addArg(data);
		addArg(data_diag);
	}
	~CFJacobyReduce() {}

	void execute() {
		exec(getArg<MeshFragment>(0), getArg<Data>(1), getArg<Data>(2), getArg<Data>(3));
	}

	double exec(MeshFragment& mesh, Data& data_new, Data& data, Data& data_diag); 
	
	double getReductionValue() const {
		return err_max;
	}

	std::string toString() const {
		return "JacobyReduce " + ReductionCompFragment::toString();
	}
};
