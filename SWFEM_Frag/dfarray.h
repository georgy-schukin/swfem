#pragma once

#include "datafragment.h"
#include <cstddef>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/scoped_array.hpp>

/**
 * Array-container of data-fragments
 */
class DFArray {
private:	
	boost::ptr_vector<DataFragment> storage; // to store data fragments	
	unsigned int id;

protected:
	DataFragmentPtrArray content; // for general access to data fragments

protected:
	template<class T> void init(const size_t& size) {
		storage.reserve(size);
		content.reserve(size);
		for (size_t i = 0;i < size;i++) {			
			T *df = new T();
			storage.push_back(df);
			content.push_back(df);
		}
	}

public:
	DFArray() {}
	DFArray(const unsigned int& i) : id(i) {}
	virtual ~DFArray() {}

	size_t getSize() const {
		return content.size();
	}

	const DataFragmentPtrArray& getData() const {
		return content;
	}	

	void setId(const unsigned int& id) {
		this->id = id;
	}

	const unsigned int& getId() const {
		return id;
	}
};
