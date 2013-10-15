#pragma once

#include "compfragment.h"

class ICFListener {
public:
	//virtual void onCFDone(CompFragment *cf) = 0;
	virtual void onCFsDone(const CompFragmentPtrArray& cfs) = 0;
};
