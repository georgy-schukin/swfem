#include "cfjacobyupdatesend.h"
#include <cassert>

void CFJacobyUpdateSend::exec(Data& src, Data& buf) {
	assert (num > 0);
	buf.resize(num);
	for (size_t i = 0; i < num; i++) {		
		buf[i] = src[start + i*step];		
	}
}
