#include "datafragmentbunch.h"
#include <boost/foreach.hpp>

void DataFragmentBunch::add(DataFragment *df) {
	content.insert(df);
}

void DataFragmentBunch::add(const DataFragmentPtrArray& dfs) {
	content.insert(dfs.begin(), dfs.end());
}

void DataFragmentBunch::add(const DataFragmentBunch& df_bunch) {
	content.insert(df_bunch.begin(), df_bunch.end());
}

bool DataFragmentBunch::isIn(DataFragment *df) const {
	return (content.find(df) != content.end());
}

void DataFragmentBunch::remove(DataFragment *df) {
	content.erase(df);
}

void DataFragmentBunch::lock() {
	BOOST_FOREACH(DataFragment* df, content) 
		df->lock();
}

void DataFragmentBunch::unlock() {
	BOOST_FOREACH(DataFragment* df, content) 
		df->unlock();
}
