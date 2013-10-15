#pragma once

#include "ieventmanager.h"
#include "icflistener.h"
#include "event.h"
#include <boost/ptr_container/ptr_map.hpp>

class EventManager : public IEventManager, public ICFListener {
protected:
	boost::ptr_map<unsigned int, Event> events;

public:
	//void registerEventCF(unsigned int event_id, EventCompFragment *cf);
	void registerEventCFs(const unsigned int& event_id, const EventCompFragmentPtrArray& cfs);
	void waitForEvent(const unsigned int& event_id);

	//void onCFDone(CompFragment *cf);
	void onCFsDone(const CompFragmentPtrArray& cfs);
};
