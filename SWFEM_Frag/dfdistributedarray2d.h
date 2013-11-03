#pragma once

#include "dfarray2d.h"
#include "distribution2d.h"
#include <boost/scoped_array.hpp>
#include <boost/shared_ptr.hpp>
#include <cassert>
#include <vector>
#include <iostream>

template<class T>
class DFDistributedArray2D {
private:
	std::vector<boost::shared_ptr<T> > content;
	//boost::scoped_array<T> content;	
	//Distribution2D distribution;
	Region2D my_block;
	int my_node;

private:
	void init(const size_t& local_num_of_rows, const size_t& local_num_of_cols) {
		//content.reset(new T[local_num_of_rows*local_num_of_cols]);
		const size_t size = local_num_of_rows*local_num_of_cols;
		for (size_t i = 0; i < size; i++)
			content.push_back(boost::shared_ptr<T>(new T()));
	}

public:
	DFDistributedArray2D(const Distribution2D& distr, const int& node) : my_node(node) {
		my_block = distr.getBlock(node);
		init(my_block.getSizeByY(), my_block.getSizeByX());
	}		
	~DFDistributedArray2D() {}	

	T* operator()(const size_t& global_row, const size_t& global_col) {
		const size_t row = global_row - my_block.getStartByY();
		const size_t col = global_col - my_block.getStartByX();
		assert(row*my_block.getSizeByX() + col < content.size());		
		return content[row*my_block.getSizeByX() + col].get();
	}
};
