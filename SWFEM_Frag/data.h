#pragma once

#include "datafragment.h"
#include "nodedata.h"
#include <vector>

/**
 * Data fragment - array of data
 */
template<class T>
class DataVector: public DataFragment, public std::vector<T> {
public:
	DataVector() {}
	DataVector(const size_t& size) : std::vector<T>(size) {}
	~DataVector() {}

	size_t getWeight() {
		return sizeof(T)*(this->size()) + 1;
	}
};

typedef DataVector<NodeData> Data;
typedef DataVector<NodeDataInteraction> DataInteraction;
typedef DataVector<NodeDataCoef> DataCoef;
