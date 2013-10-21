#pragma once

#include "dfarray2d.h"
#include "distribution2d.h"
#include <boost/scoped_array.hpp>

template<class T>
class DFDistributedArray2D {
private:
	boost::scoped_array<T> content;	
	//Distribution2D distribution;
	Region2D my_block;
	int my_node;

private:
	void init(const int& local_num_of_rows, const int& local_num_of_cols) {
		content.reset(new T[local_num_of_rows*local_num_of_cols]);
	}

public:
	DFDistributedArray2D(const Distribution2D& distr, const int& node) : distribution(distr), my_node(node) {
		my_block = distr.getBlock(node);
		init(my_block.getSizeByY(), my_block.getSizeByX());
	}		
	~DFDistributedArray2D() {}	

	T* operator()(const size_t& global_row, const size_t& global_col) {
		const size_t row = global_row - my_block.getStartByY();
		const size_t col = global_col - my_block.getStartByX();
		return content[row*my_block.getSizeByX() + col];
	}
};
