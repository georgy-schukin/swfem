#pragma once

#include "meshfragment.h"

class MeshBlockFragment: public MeshFragment {
private:
	size_t size_x;
	size_t size_y;

public:
	MeshBlockFragment() : size_x(0), size_y(0) {}
	MeshBlockFragment(const size_t& sx, const size_t& sy) : size_x(sx), size_y(sy) {}
	~MeshBlockFragment() {}

	void setSizeByX(const size_t& sx) {
		size_x = sx;
	}

	void setSizeByY(const size_t& sy) {
		size_y = sy;
	}

	size_t getSizeByX() const {
		return size_x;
	}

	size_t getSizeByY() const {
		return size_y;
	}
};