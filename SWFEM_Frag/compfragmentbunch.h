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
	CompFragmentPtrArray content;
	DataFragmentBunch used_dfs;	

private:
	void populateDFs(const CompFragmentPtrArray& cfs);
	void populateDFs(CompFragment *cf);

public:
	CompFragmentBunch() {}
	CompFragmentBunch(const CompFragmentPtrArray& cfs) : content(cfs) {
		populateDFs(cfs);
	}
	~CompFragmentBunch() {}

	/*const CompFragmentPtrArray& getContent() const {
		return content;
	}*/

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

	void lockArgs();
	void unlockArgs();	
};
