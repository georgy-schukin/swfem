#pragma once

#include "cfjacobyupdate.h"

/**
* Recv boundary values from buf and update
*/
class CFJacobyUpdateRecv: public CFJacobyUpdate {
public:
	CFJacobyUpdateRecv() {}	
	CFJacobyUpdateRecv(Data *dest, Data *buf, const Region2D& reg, const CFJacobyUpdate::BorderType& border) : CFJacobyUpdate(dest, buf, reg, border) {}		
	~CFJacobyUpdateRecv() {}	

	void exec(Data& dest, Data& buf);

	std::string toString() const {
		return "JacobyUpdateRecv " + CompFragment::toString();
	}
};
