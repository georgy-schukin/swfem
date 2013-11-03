#pragma once

#include "cfjacobyupdate.h"

/**
* Recv boundary values from buf and update
*/
class CFJacobyUpdateRecv: public CFJacobyUpdate {
public:
	CFJacobyUpdateRecv() {}	
	CFJacobyUpdateRecv(Data *src, Data *buf, const size_t& size_x, const size_t& size_y, const CFJacobyUpdate::BorderType& border) : CFJacobyUpdate(src, buf, size_x, size_y, border) {}		
	~CFJacobyUpdateRecv() {}	

	void exec(Data& dest, Data& buf);

	std::string toString() const {
		return "JacobyUpdateRecv " + CompFragment::toString();
	}
};
