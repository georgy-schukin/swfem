#pragma once

#include "cfjacobyupdate.h"

/**
* Recv boundary values from buf and update
*/
class CFJacobyUpdateRecv: public CFJacobyUpdate {
public:
	CFJacobyUpdateRecv() {}	
	CFJacobyUpdateRecv(MeshBlockFragment *mesh, Data *src, Data *buf, const CFJacobyUpdate::BorderType& border) : CFJacobyUpdate(mesh, src, buf, border) {}		
	~CFJacobyUpdateRecv() {}	

	void exec(Data& dest, Data& buf);

	std::string toString() const {
		return "JacobyUpdateRecv " + CompFragment::toString();
	}
};
