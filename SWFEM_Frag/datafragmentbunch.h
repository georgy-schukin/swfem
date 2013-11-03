#pragma once

#include "datafragment.h"
#include <set>

/**
* Bunch of unique data fragments
*/
class DataFragmentBunch {
public:
	typedef std::set<DataFragment*>::iterator iterator;
    typedef std::set<DataFragment*>::const_iterator const_iterator;

private:
	std::set<DataFragment*> content;

public:
	DataFragmentBunch() {}
	DataFragmentBunch(const DataFragmentBunch& b) : content(b.content) {}
	~DataFragmentBunch() {}	

	iterator begin() { 
		return content.begin(); 
	}

    const_iterator begin() const { 
		return content.begin(); 
	}

    iterator end() { 
		return content.end(); 
	}

    const_iterator end() const { 
		return content.end(); 
	}

	void add(DataFragment* df);
	void add(const DataFragmentPtrArray& dfs);	

	bool isIn(DataFragment *df) const;	

	void remove(DataFragment *df);

	bool isEmpty() {
		return content.empty();
	}

	void lock();
	void unlock();
};
