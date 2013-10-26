#pragma once

#include "datafragmentroute.h"
#include <vector>
#include <set>

class CompFragment;

/**
* Generic data fragment (piece of data)
*/
class DataFragment {
public:
	static const size_t NO_GROUP = (size_t)(-1);

private:	
	DataFragmentRoute route;
	bool is_locked;
	size_t curr_group;

public:
	DataFragment() : is_locked(false), curr_group(DataFragment::NO_GROUP) {}	

	void lock() {
		this->is_locked = true;
	}

	void unlock() {
		this->is_locked = false;
	}

	bool isLocked() const {
		return is_locked;
	}

	bool isReady() const {
		return (!is_locked && !route.isEmpty());
	}

	DataFragmentRoute& getRoute() {
		return route;
	}

	void setCurrentGroup(const size_t& group) {
		curr_group = group;
	}

	const size_t& getCurrentGroup() const {
		return curr_group;
	}

	virtual ~DataFragment() {}
	virtual size_t getWeight() = 0;
};

typedef std::vector<DataFragment*> DataFragmentPtrArray;
typedef std::set<DataFragment*> DataFragmentPtrSet;
