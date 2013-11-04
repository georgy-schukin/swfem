#pragma once

#include "cfjacobyupdate.h"

/**
* Write update values into buf
*/
class CFJacobyUpdateSend: public CFJacobyUpdate {
public:
	CFJacobyUpdateSend() {}	
	CFJacobyUpdateSend(Data *src, Data *buf, const Region2D& reg, const CFJacobyUpdate::BorderType& border) : CFJacobyUpdate(src, buf, reg, border) {}		
	~CFJacobyUpdateSend() {}	

	void exec(Data& src, Data& buf);

	std::string toString() const {
		return "JacobyUpdateSend " + CompFragment::toString();
	}
};
