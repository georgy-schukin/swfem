#pragma once

#include "eventcompfragment.h"

/**
 * Interface for manager for event comp fragments
 */
class IEventManager {
public:
	//virtual void registerEventCF(const size_t& event_id, EventCompFragment *cf) = 0;
	virtual void registerEventCFs(const size_t& event_id, const EventCompFragmentPtrArray& cfs) = 0;
	virtual void waitForEvent(const size_t& event_id) = 0;

	virtual ~IEventManager() {}
};
