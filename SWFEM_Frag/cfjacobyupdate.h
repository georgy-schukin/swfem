#pragma once

#include "compfragment.h"
#include "meshblockfragment.h"
#include "data.h"
#include "region2d.h"

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
	BorderType border_type;

protected:
	void init(const Region2D& reg, const BorderType& border);

public:
	CFJacobyUpdate() {}
	CFJacobyUpdate(Data *data, Data *buf, const Region2D& reg, const BorderType& border) : border_type(border) {				
		addArg(data);		
		addArg(buf);
		init(reg, border);
	}
	virtual ~CFJacobyUpdate() {}

	void execute() {
		exec(getArg<Data>(0), getArg<Data>(1));
	}

	virtual void exec(Data& data, Data& buf) = 0;	
};
