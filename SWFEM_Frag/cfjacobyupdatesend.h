#pragma once

#include "eventcompfragment.h"
#include "data.h"

/**
* Write update values into buf
*/
class CFJacobyUpdateSend: public EventCompFragment {
protected:
	size_t start;
	size_t step;	
	size_t num;

public:
	CFJacobyUpdateSend() {}
	CFJacobyUpdateSend(const size_t& str, const size_t& stp, const size_t& n) : start(str), step(stp), num(n) {}
	CFJacobyUpdateSend(Data *src, Data *buf, const size_t& str, const size_t& stp, const size_t& n) : start(str), step(stp), num(n) {				
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
