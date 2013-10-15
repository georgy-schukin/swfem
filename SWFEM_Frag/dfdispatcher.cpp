#include "dfdispatcher.h"
#include <boost/foreach.hpp>

/*void DFDispatcher::addDF(DataFragment *df, bool update) {	
	boost::unique_lock<boost::mutex> lock(mutex);
	unsigned int df_id = df->getId();	
	dataFragments.insert(df_id, df);	
	lock.unlock();
	if (update)
		BOOST_FOREACH(IDFListener *l, dfListeners) 
			l->onDFCreated(df);
}

void DFDispatcher::addDFs(const vector<DataFragment*>& dfs, bool update) {	
	boost::unique_lock<boost::mutex> lock(mutex);
	BOOST_FOREACH(DataFragment *df, dfs) {
		unsigned int df_id = df->getId();
		dataFragments.insert(df_id, df);
	}	
	lock.unlock();
	if (update)
		BOOST_FOREACH(IDFListener *l, dfListeners) 
			l->onDFsCreated(dfs);
}

DataFragment* DFDispatcher::getDF(unsigned int df_id) {	
	boost::unique_lock<boost::mutex> lock(mutex);
	DataFragments::iterator it = dataFragments.find(df_id);
	return (it != dataFragments.end()) ? it->second : 0;
}

void DFDispatcher::getDFs(const vector<unsigned int>& df_ids, vector<DataFragment*>& dfs) {	
	boost::unique_lock<boost::mutex> lock(mutex);	
	BOOST_FOREACH(unsigned int df_id, df_ids) {
		DataFragments::iterator it = dataFragments.find(df_id);
		dfs.push_back((it != dataFragments.end()) ? it->second : 0);
	}	
}

void DFDispatcher::getReadyDFs(vector<DataFragment*>& dfs) {
	boost::unique_lock<boost::mutex> lock(mutex);
	BOOST_FOREACH(const DataFragments::value_type& p, dataFragments) {
		DataFragment *df = p->second;
		if (df->isReady())
			dfs.push_back(df);
	}
}*/

void DFDispatcher::getReadyDFs(const DataFragmentPtrArray& src, DataFragmentPtrArray& ready_dfs) {
	boost::unique_lock<boost::mutex> lock(mutex);
	BOOST_FOREACH(DataFragment *df, src)
		if (df->isReady())
			ready_dfs.push_back(df);
}

void DFDispatcher::getReadyDFsAndLock(const DataFragmentPtrArray& src, DataFragmentPtrArray& ready_dfs) {
	boost::unique_lock<boost::mutex> lock(mutex);
	BOOST_FOREACH(DataFragment *df, src)
		if (df->isReady()) {
			df->setLocked(true);
			ready_dfs.push_back(df);
		}
}

void DFDispatcher::lockDFs(const DataFragmentPtrArray& dfs) {
	BOOST_FOREACH(DataFragment *df, dfs)
		df->setLocked(true);
}

void DFDispatcher::unlockDFs(const DataFragmentPtrArray& dfs) {
	BOOST_FOREACH(DataFragment *df, dfs)
		df->setLocked(false);
	BOOST_FOREACH(IDFListener *l, dfListeners) 
			l->onDFsUnlocked(dfs);
}

/*void DFDispatcher::removeDF(unsigned int df_id) {
	boost::unique_lock<boost::mutex> lock(mutex);
	dataFragments.erase(df_id);
}

void DFDispatcher::removeDFs(const vector<unsigned int>& df_ids) {	
	boost::unique_lock<boost::mutex> lock(mutex);
	BOOST_FOREACH(unsigned int df_id, df_ids)
		dataFragments.erase(df_id);
}*/

void DFDispatcher::addDFListener(IDFListener* l) {
	dfListeners.push_back(l);
}
