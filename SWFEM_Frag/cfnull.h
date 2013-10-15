#pragma once

#include "compfragment.h"
#include "data.h"

/**
* Null data
*/
class CFNull: public CompFragment {
public:
	CFNull() {}
	CFNull(Data *data) {				
		addArg(data);		
	}
	~CFNull() {}

	void execute() {
		exec(getArg<Data>(0));
	}

	void exec(Data& data);

	std::string toString() const {
		return "Null " + CompFragment::toString();
	}
};
