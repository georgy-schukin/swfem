#pragma once

#include "dfarray.h"

template<class T>
class DFArray1D : public DFArray {
public:
	DFArray1D(const size_t& size) {
		init<T>(size);
	}	
	~DFArray1D() {}

	T* operator()(const size_t& ind) {
		return (T*)content.at(ind);
	}	
};
