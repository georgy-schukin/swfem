#pragma once

#include "compfragment.h"
#include "data.h"
#include "mesh.h"

/**
* Calculate friction
*/
class CFExact: public CompFragment {
protected:
	double tt;

public:
	CFExact(double t) : tt(t) {}
	CFExact(MeshFragment *mesh, Data *data, double t) : tt(t) {
		addArg(mesh);
		addArg(data);
	}
	~CFExact() {}

	void execute() {
		exec(getArg<MeshFragment>(0), getArg<Data>(1));
	}

	void exec(MeshFragment& mesh, Data& data);

	std::string toString() const {
		return "Exact " + CompFragment::toString();
	}
};
