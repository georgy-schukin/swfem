#include "cfjacobyupdate.h"

void CFJacobyUpdate::init(const Region2D& reg, const BorderType& border) {		
	switch (border) {
		case CFJacobyUpdate::LEFT: // left vert
			{
				start = 0;
				step = reg.getSizeByX();
				num = reg.getSizeByY();
				break;
			}
		case CFJacobyUpdate::RIGHT: // right vert
			{
				start = reg.getSizeByX() - 1;
				step = reg.getSizeByX();
				num = reg.getSizeByY();
				break;
			}
		case CFJacobyUpdate::TOP: // top horiz
			{
				start = 0;
				step = 1;
				num = reg.getSizeByX();
				break;
			}
		case CFJacobyUpdate::BOTTOM: // bottom horiz
			{
				start = (reg.getSizeByY() - 1)*reg.getSizeByX();
				step = 1;
				num = reg.getSizeByX();
				break;
			}
	}
}
