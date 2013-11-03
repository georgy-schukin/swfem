#include "cfjacobyupdaterecv.h"
#include <cassert>

void CFJacobyUpdateRecv::exec(Data& dest, Data& buf) {
	assert ((num > 0) && (buf.size() > 0));
	for(size_t i = 0;i < num;i++) {	
		dest[start + i*step] += buf[i];
		/*const NodeData& dt_src = buf[i];
		NodeData& dt_dst = dest[start + i*step];		
		dt_dst.u += dt_src.u;
		dt_dst.v += dt_src.v;
		dt_dst.xi += dt_src.xi;*/
	}
}
