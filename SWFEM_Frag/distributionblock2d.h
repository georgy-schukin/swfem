#pragma once

#include <cstddef>

/**
* Block for 2D distribution
*/
class DistributionBlock2D {
private:
	size_t start_x;
	size_t start_y;
	size_t end_x;
	size_t end_y;

public:
	DistributionBlock2D() : start_x(0), start_y(0), end_x(0), end_y(0) {}
	DistributionBlock2D(const size_t& sx, const size_t& sy, const size_t& ex, const size_t& ey) : start_x(sx), start_y(sy), end_x(ex), end_y(ey) {}
	DistributionBlock2D(const DistributionBlock2D& b) : start_x(b.start_x), start_y(b.start_y), end_x(b.end_x), end_y(b.end_y) {}
	~DistributionBlock2D() {}

	void setStartX(const size_t& x) {
		this->start_x = x;
	}

	void setStartY(const size_t& y) {
		this->start_y = y;
	}

	void setEndX(const size_t& x) {
		this->end_x = x;
	}

	void setEndY(const size_t& y) {
		this->end_y = y;
	}

	size_t getStartX() const {
		return start_x;
	}

	size_t getStartY() const {
		return start_y;
	}

	size_t getEndX() const {
		return end_x;
	}

	size_t getEndY() const {
		return end_y;
	}
};