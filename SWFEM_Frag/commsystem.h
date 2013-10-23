#pragma once

#include "datafragment.h"
#include "icommlistener.h"

class CommSystem {
public:
	void sendDF(DataFragment *df, const int& dest_node);
	void addCommListener(ICommListener *listener);
};