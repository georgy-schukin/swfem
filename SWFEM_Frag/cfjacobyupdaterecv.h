#pragma once

#include "compfragment.h"
#include "data.h"

/**
* Recv boundary values from buf and update
*/
class CFJacobyUpdateRecv: public CompFragment {
protected:
	unsigned int start;
	unsigned int step;	
	unsigned int num;

public:
	CFJacobyUpdateRecv() {}
	CFJacobyUpdateRecv(const unsigned int& str, const unsigned int& stp, const unsigned int& n) : start(str), step(stp), num(n) {}
	CFJacobyUpdateRecv(Data *dst, Data *buf, const unsigned int& str, const unsigned int& stp, const unsigned int& n) : start(str), step(stp), num(n) {				
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
