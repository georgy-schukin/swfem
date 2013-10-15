#pragma once

#include "datafragment.h"

/**
 * Interface for listener for data fargments events
 */
class IDFListener {
public:
	//virtual void onDFCreated(DataFragment *df) = 0;
	//virtual void onDFsCreated(const vector<DataFragment*>& dfs) = 0;
	virtual void onDFsUnlocked(const DataFragmentPtrArray& dfs) = 0;
};
