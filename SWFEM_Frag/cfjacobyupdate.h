#pragma once

#include "compfragment.h"
#include "data.h"

/**
* Update bound values
*/
class CFJacobyUpdate: public CompFragment {
protected:
	unsigned int src_start;
	unsigned int src_step;
	unsigned int dst_start;	
	unsigned int dst_step;
	unsigned int num;

public:
	CFJacobyUpdate() {}
	CFJacobyUpdate(Data *src, Data *dst, 
		unsigned int src_st, unsigned int src_stp, unsigned int dst_st, unsigned int dst_stp, unsigned int n) :
		src_start(src_st), src_step(src_stp), dst_start(dst_st), dst_step(dst_stp), num(n) {				
		addArg(src);		
		addArg(dst);		
	}
	~CFJacobyUpdate() {}

	void execute() {
		exec(getArg<Data>(0), getArg<Data>(1));
	}

	void exec(Data& src, Data& dst);

	std::string toString() const {
		return "JacobyUpdate " + CompFragment::toString();
	}
};
