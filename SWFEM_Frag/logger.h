#pragma once

#include "icflistener.h"

class Logger : public ICFListener {
public:
	//void onCFDone(CompFragment *cf);
	void onCFsDone(CompFragmentBunch& cf_bunch);
};