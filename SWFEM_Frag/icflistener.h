#pragma once

#include "compfragment.h"
#include "compfragmentgroup.h"

class ICFListener {
public:
	//virtual void onCFDone(CompFragment *cf) = 0;
	virtual void onCFsDone(CompFragmentBunch& cf_bunch) = 0;
	//virtual void onCFGroupDone(const CompFragmentGroup& group) = 0;
};
