#include "cfcopy.h"

void CFCopy::exec(Data& dst, Data& src) {	
	dst.resize(src.size());
	copy(src.begin(), src.end(), dst.begin());
	/*for(size_t i = 0;i < dst.size();i++) {
		dst[i].u = src[i].u;
		dst[i].v = src[i].v;
		dst[i].xi = src[i].xi;
	}*/
}