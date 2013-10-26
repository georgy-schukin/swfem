#include "compfragmentbunch.h"
#include <boost/foreach.hpp>

void CompFragmentBunch::add(CompFragment *cf) {
	content.push_back(cf);
	populateDFs(cf);
}

void CompFragmentBunch::add(const CompFragmentPtrArray& cfs) {
	content.insert(content.end(), cfs.begin(), cfs.end());
	populateDFs(cfs);
}

void CompFragmentBunch::lockArgs() {
	used_dfs.lock();
}

void CompFragmentBunch::unlockArgs() {
	used_dfs.unlock();
}

void CompFragmentBunch::populateDFs(const CompFragmentPtrArray& cfs) {
	BOOST_FOREACH(CompFragment *cf, cfs)
		used_dfs.add(cf->getArgs());
}

void CompFragmentBunch::populateDFs(CompFragment *cf) {	
	used_dfs.add(cf->getArgs());
}

