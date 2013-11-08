#pragma once

#include "compfragment.h"
#include "datafragmentbunch.h"

/**
* Arbitrary bunch of cfs
*/
class CompFragmentBunch {
public:
	typedef std::vector<CompFragment*>::iterator iterator;
    typedef std::vector<CompFragment*>::const_iterator const_iterator;

protected:
	std::vector<CompFragment*> content;
	DataFragmentBunch used_dfs;	

public:
	CompFragmentBunch() {}
	CompFragmentBunch(const CompFragmentPtrArray& cfs) {
		add(cfs);
	}
	CompFragmentBunch(const CompFragmentBunch& b) : content(b.content), used_dfs(b.used_dfs) {}
	~CompFragmentBunch() {}

	const DataFragmentBunch& getArgs() const {
		return used_dfs;
	}

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

	size_t size() const {
		return content.size();
	}

	void add(CompFragment *cf);
	void add(const CompFragmentPtrArray& cfs);
	void add(const CompFragmentBunch& bunch);

	void lockArgs();
	void unlockArgs();	
};
