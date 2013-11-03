#include "cfjacobyupdate.h"

/*void CFJacobyUpdate::exec(Data& src, Data& dst) {
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
}*/

void CFJacobyUpdate::init(const size_t& size_x, const size_t& size_y, const BorderType& border) {		
	switch (border) {
		case CFJacobyUpdate::LEFT: // left vert
			{
				start = 0;
				step = size_x;
				num = size_y;
				break;
			}
		case CFJacobyUpdate::RIGHT: // right vert
			{
				start = size_x - 1;
				step = size_y;
				num = size_y;
				break;
			}
		case CFJacobyUpdate::TOP: // top horiz
			{
				start = 0;
				step = 1;
				num = size_x;
				break;
			}
		case CFJacobyUpdate::BOTTOM: // bottom horiz
			{
				start = (size_y - 1)*size_x;
				step = 1;
				num = size_x;
				break;
			}
	}
}
