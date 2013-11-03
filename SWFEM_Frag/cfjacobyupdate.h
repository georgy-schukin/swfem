#pragma once

#include "compfragment.h"
#include "meshblockfragment.h"
#include "data.h"

/**
* Update bound values
*/
class CFJacobyUpdate: public CompFragment {
public:
	enum BorderType {
		LEFT = 0,
		RIGHT,
		TOP,
		BOTTOM
	};	

protected:
	size_t start;
	size_t step;	
	size_t num;

protected:
	void init(const size_t& size_x, const size_t& size_y, const BorderType& border);

public:
	CFJacobyUpdate() {}
	CFJacobyUpdate(Data *data, Data *buf, const size_t& size_x, const size_t& size_y, const BorderType& border) {				
		addArg(data);		
		addArg(buf);
		init(size_x, size_y, border);
	}
	virtual ~CFJacobyUpdate() {}

	void execute() {
		exec(getArg<Data>(0), getArg<Data>(1));
	}

	virtual void exec(Data& data, Data& buf) = 0;	
};
