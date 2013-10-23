#pragma once

#include "compfragment.h"

class CompFragmentGroup {
protected:
	CompFragmentPtrArray content;
	size_t group_id;

public:
	CompFragmentGroup(const size_t& id) : group_id(id) {}
	CompFragmentGroup(const size_t& id, const CompFragmentPtrArray& cfs) : group_id(id), content(cfs) {}
	~CompFragmentGroup() {}

	const size_t& getGroupId() const {
		return group_id;
	}

	const CompFragmentPtrArray& getContent() const {
		return content;
	}

	void add(const CompFragmentPtrArray& cfs) {
		content.insert(content.end(), cfs.begin(), cfs.end());
	}

	void add(CompFragment *cf) {
		content.push_back(cf);
	}
};
