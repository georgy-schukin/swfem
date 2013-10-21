#include "cfjacobyupdate.h"

void CFJacobyUpdate::exec(Data& src, Data& dst) {
	for(size_t i = 0;i < num;i++) {		
		NodeData& dt_src = src[src_start + i*src_step];
		NodeData& dt_dst = dst[dst_start + i*dst_step];		
		dt_dst.u += dt_src.u;
		dt_dst.v += dt_src.v;
		dt_dst.xi += dt_src.xi;
		dt_src.u = dt_dst.u;
		dt_src.v = dt_dst.v;
		dt_src.xi = dt_dst.xi;
	}
}
