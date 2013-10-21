#pragma once

#include "ieventmanager.h"
#include "icflistener.h"
#include "event.h"
#include <boost/ptr_container/ptr_map.hpp>

class EventManager : public IEventManager, public ICFListener {
protected:
	boost::ptr_map<size_t, Event> events;

public:
	//void registerEventCF(size_t event_id, EventCompFragment *cf);
	void registerEventCFs(const size_t& event_id, const EventCompFragmentPtrArray& cfs);
	void waitForEvent(const size_t& event_id);

	//void onCFDone(CompFragment *cf);
	void onCFsDone(const CompFragmentPtrArray& cfs);
};
