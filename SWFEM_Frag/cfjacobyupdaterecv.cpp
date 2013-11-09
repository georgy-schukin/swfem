#include "cfjacobyupdaterecv.h"
#include <cassert>

void CFJacobyUpdateRecv::exec(Data& dest, Data& buf) {
	assert ((num > 0) && (buf.size() > 0) && (num == buf.size()));
	for(size_t i = 0;i < num;i++) {	
		dest[start + i*step] += buf[i];
	}
}
