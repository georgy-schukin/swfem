#pragma once

#include "cfjacobyupdate.h"

/**
* Write update values into buf
*/
class CFJacobyUpdateSend: public CFJacobyUpdate {
public:
	CFJacobyUpdateSend() {}	
	CFJacobyUpdateSend(Data *src, Data *buf, const size_t& size_x, const size_t& size_y, const CFJacobyUpdate::BorderType& border) : CFJacobyUpdate(src, buf, size_x, size_y, border) {}		
	~CFJacobyUpdateSend() {}	

	void exec(Data& src, Data& buf);

	std::string toString() const {
		return "JacobyUpdateSend " + CompFragment::toString();
	}
};
