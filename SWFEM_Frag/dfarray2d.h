#pragma once

#include "dfarray.h"
#include "distribution2d.h"

template<class T, class D>
class DFArray2D /*: public DFArray*/ {
private:
	Distribution2D distr;
	size_t size_x;
	size_t size_y;	

public:
	DFArray2D(const size_t& sz_i, const size_t& sz_j) : size_i(sz_i), size_j(sz_j) {
		init<T>(size_i*size_j);
	}
	~DFArray2D() {}

	T* operator()(const size_t& ind_i, const size_t& ind_j) {
		return (T*)content.at(ind_i*size_j + ind_j);
	}

	const size_t getSizeByY() const {
		return size_i;
	}

	const size_t getSizeByX() const {
		return size_j;
	}
};
