#include "compfragmentbunch.h"
#include <boost/foreach.hpp>

void CompFragmentBunch::add(CompFragment *cf) {
	content.push_back(cf);
	is_changed = true;
	//used_dfs.add(cf->getArgs());
}

void CompFragmentBunch::add(const CompFragmentPtrArray& cfs) {
	content.insert(content.end(), cfs.begin(), cfs.end());
	is_changed = true;
	/*BOOST_FOREACH(CompFragment *cf, cfs)
		used_dfs.add(cf->getArgs());*/
}

void CompFragmentBunch::add(const CompFragmentBunch& cf_bunch) {
	content.insert(content.end(), cf_bunch.begin(), cf_bunch.end());
	is_changed = true;
	//used_dfs.add(cf_bunch.getArgs());
}

const DataFragmentBunch& CompFragmentBunch::getArgs() {
	if (is_changed) {
		BOOST_FOREACH(CompFragment *cf, content)
			used_dfs.add(cf->getArgs());
		is_changed = false;
	}
	return used_dfs;
}

/*void CompFragmentBunch::lockArgs() {
	getArgs().lock();
}

void CompFragmentBunch::unlockArgs() {
	getArgs().unlock();
}*/


