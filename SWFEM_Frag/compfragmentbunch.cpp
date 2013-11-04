#include "compfragmentbunch.h"
#include <boost/foreach.hpp>

void CompFragmentBunch::add(CompFragment *cf) {
	content.push_back(cf);
	used_dfs.add(cf->getArgs());
}

void CompFragmentBunch::add(const CompFragmentPtrArray& cfs) {
	content.insert(content.end(), cfs.begin(), cfs.end());
	BOOST_FOREACH(CompFragment *cf, cfs)
		used_dfs.add(cf->getArgs());
}

void CompFragmentBunch::add(const CompFragmentBunch& cf_bunch) {
	content.insert(content.end(), cf_bunch.begin(), cf_bunch.end());
	used_dfs.add(cf_bunch.getArgs());
}

void CompFragmentBunch::lockArgs() {
	used_dfs.lock();
}

void CompFragmentBunch::unlockArgs() {
	used_dfs.unlock();
}


