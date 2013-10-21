#pragma once

#include <cstddef>

/**
* Region for 2D distribution
*/
class Region2D {
private:
	size_t start_x;
	size_t start_y;
	size_t end_x;
	size_t end_y;

public:
	Region2D() : start_x(0), start_y(0), end_x(0), end_y(0) {}
	Region2D(const size_t& sx, const size_t& sy, const size_t& ex, const size_t& ey) : start_x(sx), start_y(sy), end_x(ex), end_y(ey) {}
	Region2D(const Region2D& r) : start_x(r.start_x), start_y(r.start_y), end_x(r.end_x), end_y(r.end_y) {}
	~Region2D() {}

	/*void setStartByX(const size_t& x) {
		this->start_x = x;
	}

	void setStartByY(const size_t& y) {
		this->start_y = y;
	}

	void setEndByX(const size_t& x) {
		this->end_x = x;
	}

	void setEndByY(const size_t& y) {
		this->end_y = y;
	}*/

	size_t getStartByX() const {
		return start_x;
	}

	size_t getStartByY() const {
		return start_y;
	}

	size_t getEndByX() const {
		return end_x;
	}

	size_t getEndByY() const {
		return end_y;
	}

	size_t getSizeByX() const {
		return end_x - start_x;
	}

	size_t getSizeByY() const {
		return end_y - start_y;
	}
};