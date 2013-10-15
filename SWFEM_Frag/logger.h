#pragma once

#include "icflistener.h"

class Logger : public ICFListener {
public:
	//void onCFDone(CompFragment *cf);
	void onCFsDone(const CompFragmentPtrArray& cfs);
};