#pragma once

#include "compfragment.h"
#include "data.h"
#include "mesh.h"

/**
* Calculate interactions (w1, w2, w3)
*/
class CFInteraction: public CompFragment {
protected:
	double tt;

public:
	CFInteraction(double t) : tt(t) {}
	CFInteraction(MeshFragment *mesh, DataInteraction *data_interaction, double t) : tt(t) {		
		addArg(mesh);
		addArg(data_interaction);
	}
	~CFInteraction() {}

	void execute() {
		exec(getArg<MeshFragment>(0), getArg<DataInteraction>(1));
	}

	void exec(MeshFragment& mesh, DataInteraction& data_interaction);

	std::string toString() const {
		return "Interaction " + CompFragment::toString();
	}
};
