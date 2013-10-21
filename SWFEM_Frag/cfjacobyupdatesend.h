#pragma once

#include "cfjacobyupdate.h"

/**
* Write update values into buf
*/
class CFJacobyUpdateSend: public CFJacobyUpdate {
public:
	CFJacobyUpdateSend() {}	
	CFJacobyUpdateSend(MeshBlockFragment *mesh, Data *src, Data *buf, const CFJacobyUpdate::BorderType& border) : CFJacobyUpdate(mesh, src, buf, border) {}		
	~CFJacobyUpdateSend() {}	

	void exec(Data& src, Data& buf);

	std::string toString() const {
		return "JacobyUpdateSend " + CompFragment::toString();
	}
};
