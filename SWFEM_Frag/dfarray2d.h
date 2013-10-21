#pragma once

#include <boost/ptr_container/ptr_array.hpp>

template<class T>
class DFArray2D {
private:
	boost::ptr_array<T> content;
	size_t num_of_rows;
	size_t num_of_cols;

private:
	void init(const size_t& num_of_rows, const size_t& num_of_cols) {
		content.reset(new T[num_of_rows*num_of_cols]);
	}

public:
	DFArray2D(const size_t& rows, const size_t& cols) : num_of_rows(rows), num_of_cols(cols) {
		this->init(rows, cols);
	}		
	~DFDistributedArray2D() {}

	T* operator()(const size_t& row, const size_t& col) {
		return content[row*num_of_cols + col];
	}
};
