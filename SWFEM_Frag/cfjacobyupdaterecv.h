#pragma once

#include "compfragment.h"
#include "data.h"

/**
* Recv boundary values from buf and update
*/
class CFJacobyUpdateRecv: public CompFragment {
protected:
	size_t start;
	size_t step;	
	size_t num;

public:
	CFJacobyUpdateRecv() {}
	CFJacobyUpdateRecv(const size_t& str, const size_t& stp, const size_t& n) : start(str), step(stp), num(n) {}
	CFJacobyUpdateRecv(Data *dst, Data *buf, const size_t& str, const size_t& stp, const size_t& n) : start(str), step(stp), num(n) {				
		addArg(dst);		
		addArg(buf);		
	}
	~CFJacobyUpdateRecv() {}

	void execute() {
		exec(getArg<Data>(0), getArg<Data>(1));
	}

	void exec(Data& dst, Data& buf);

	std::string toString() const {
		return "JacobyUpdateRecv " + CompFragment::toString();
	}
};
