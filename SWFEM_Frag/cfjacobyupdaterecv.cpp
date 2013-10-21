#include "cfjacobyupdaterecv.h"

void CFJacobyUpdateRecv::exec(Data& dst, Data& buf) {
	for(size_t i = 0;i < num;i++) {		
		const NodeData& dt_src = buf[i];
		NodeData& dt_dst = dst[start + i*step];		
		dt_dst.u += dt_src.u;
		dt_dst.v += dt_src.v;
		dt_dst.xi += dt_src.xi;
	}
}
