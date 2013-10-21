#pragma once

#include "compfragment.h"
#include "data.h"

/**
* Update bound values
*/
class CFJacobyUpdate: public CompFragment {
protected:
	size_t src_start;
	size_t src_step;
	size_t dst_start;	
	size_t dst_step;
	size_t num;

public:
	CFJacobyUpdate() {}
	CFJacobyUpdate(Data *src, Data *dst, 
		size_t src_st, size_t src_stp, size_t dst_st, size_t dst_stp, size_t n) :
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
