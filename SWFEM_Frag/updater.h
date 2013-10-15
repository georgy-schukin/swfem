#pragma once

#include "icommunicator.h"
#include "data.h"

class Updater {
protected:
	ICommunicator *comm;

protected:
	unsigned int computeBufSize(const DataFragmentPtrArray& data);
	void pack(void *buf, const unsigned int& buf_size, const DataFragmentPtrArray& data);
	void unpack(void *buf, const unsigned int& buf_size, const DataFragmentPtrArray& data);

public:
	Updater(ICommunicator *cm) : comm(cm) {}
	~Updater() {}

	void update(const DataFragmentPtrArray& send, const DataFragmentPtrArray& recv, const int& tag, const int& node);
};
