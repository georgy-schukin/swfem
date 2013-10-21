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

void CFJacobyUpdate::init(MeshBlockFragment *mesh, const BorderType& border) {
	switch (border) {
		case CFJacobyUpdate::LEFT: // left vert
			{
				start = 0;
				step = mesh->getSizeByX();
				num = mesh->getSizeByY();
				break;
			}
		case CFJacobyUpdate::RIGHT: // right vert
			{
				start = mesh->getSizeByX() - 1;
				step = mesh->getSizeByX();
				num = mesh->getSizeByY();
				break;
			}
		case CFJacobyUpdate::TOP: // top horiz
			{
				start = 0;
				step = 1;
				num = mesh->getSizeByX();
				break;
			}
		case CFJacobyUpdate::BOTTOM: // bottom horiz
			{
				start = (mesh->getSizeByY() - 1)*mesh->getSizeByX();
				step = 1;
				num = mesh->getSizeByX();
				break;
			}
	}
}
