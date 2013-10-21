#pragma once

#include "datafragment.h"

class ICommListener {
public:
	virtual void onDataRecv(DataFragment *df, const size_t& tag, const int& src_node) = 0;
};
