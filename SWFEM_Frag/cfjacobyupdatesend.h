#pragma once

#include "eventcompfragment.h"
#include "data.h"

/**
* Write update values into buf
*/
class CFJacobyUpdateSend: public EventCompFragment {
protected:
	unsigned int start;
	unsigned int step;	
	unsigned int num;

public:
	CFJacobyUpdateSend() {}
	CFJacobyUpdateSend(const unsigned int& str, const unsigned int& stp, const unsigned int& n) : start(str), step(stp), num(n) {}
	CFJacobyUpdateSend(Data *src, Data *buf, const unsigned int& str, const unsigned int& stp, const unsigned int& n) : start(str), step(stp), num(n) {				
		addArg(src);		
		addArg(buf);		
	}
	~CFJacobyUpdateSend() {}

	void execute() {
		exec(getArg<Data>(0), getArg<Data>(1));
	}

	void exec(Data& src, Data& buf);

	std::string toString() const {
		return "JacobyUpdateSend " + CompFragment::toString();
	}
};
