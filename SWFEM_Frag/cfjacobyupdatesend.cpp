#include "cfjacobyupdatesend.h"

void CFJacobyUpdateSend::exec(Data& src, Data& buf) {
	buf.resize(num);
	for(unsigned int i = 0;i < num;i++) {		
		const NodeData& dt_src = src[start + i*step];		
		NodeData& dt_dst = buf[i];		
		dt_dst.u = dt_src.u;		
		dt_dst.v = dt_src.v;		
		dt_dst.xi = dt_src.xi;
	}
}
