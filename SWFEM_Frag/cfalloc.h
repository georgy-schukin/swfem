#pragma once

#include "compfragment.h"
#include "data.h"
#include "meshblockfragment.h"

/**
* Alloc memory for main data fragments
*/
class CFAlloc: public CompFragment {
public:
	CFAlloc() {}
	CFAlloc(MeshBlockFragment *mesh, Data *data, Data *data_new, Data *data_prev, Data *data_diag, Data *data_exact, 
		DataCoef *data_coef, DataInteraction *data_interaction) {
		addArg(mesh);
		addArg(data);
		addArg(data_new);
		addArg(data_prev);
		addArg(data_diag);
		addArg(data_exact);
		addArg(data_coef);
		addArg(data_interaction);
	}
	~CFAlloc() {}

	void execute() {
		exec(getArg<MeshBlockFragment>(0), getArg<Data>(1), getArg<Data>(2), getArg<Data>(3), getArg<Data>(4), getArg<Data>(5),
			getArg<DataCoef>(6), getArg<DataInteraction>(7));
	}

	void exec(MeshBlockFragment& mesh, Data& data, Data& data_new, Data& data_prev, Data& data_diag, Data& data_exact,
		DataCoef& data_coef, DataInteraction& data_interaction);

	std::string toString() const {
		return "Alloc " + CompFragment::toString();
	}
};
