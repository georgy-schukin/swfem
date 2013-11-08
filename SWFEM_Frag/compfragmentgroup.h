#pragma once

#include "compfragmentbunch.h"

class CompFragmentGroup : public CompFragmentBunch {
protected:	
	size_t group_id;

public:
	CompFragmentGroup() : group_id(0) {}
	CompFragmentGroup(const size_t& id) : group_id(id) {}
	CompFragmentGroup(const size_t& id, const CompFragmentPtrArray& cfs) : group_id(id), CompFragmentBunch(cfs) {}
	~CompFragmentGroup() {}

	void setGroupId(const size_t& id) {
		group_id = id;
	}

	const size_t& getGroupId() const {
		return group_id;
	}	
};
