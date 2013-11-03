#pragma once

#include "icflistener.h"

class Logger : public ICFListener {
public:
	Logger() {}
	virtual ~Logger() {}

	//void onCFDone(CompFragment *cf);
	void onCFsDone(CompFragmentBunch& cf_bunch);
};