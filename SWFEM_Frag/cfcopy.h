#pragma once

#include "compfragment.h"
#include "data.h"

/**
* Null data
*/
class CFCopy: public CompFragment {
public:
	CFCopy() {}
	CFCopy(Data *data_dst, Data *data_src) {				
		addArg(data_dst);		
		addArg(data_src);		
	}
	~CFCopy() {}

	void execute() {
		exec(getArg<Data>(0), getArg<Data>(1));
	}

	void exec(Data& dst, Data& src);

	std::string toString() const {
		return "Copy " + CompFragment::toString();
	}
};
