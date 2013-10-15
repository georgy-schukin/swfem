#include "eventmanager.h"
#include <boost/foreach.hpp>
#include <boost/unordered_map.hpp>
#include <map>

/*void EventManager::registerEventCF(unsigned int event_id, EventCompFragment *cf) {
	if (events.find(event_id) == events.end()) {	// new reduction		
		events.insert(event_id, new Event(1)); // create new reducer for reduction		
	} else {	// redution already exists
		events.at(event_id).changeSize(1);		// increment local size by 1
	}
	cf->setEventId(event_id);
}*/

void EventManager::registerEventCFs(const unsigned int& event_id, const EventCompFragmentPtrArray& cfs) {
	if (events.find(event_id) == events.end()) {	// new reduction		
		unsigned int evnt_id = event_id;
		events.insert(evnt_id, new Event(cfs.size())); // create new reducer for reduction
	} else {	// redution already exists
		events.at(event_id).changeSize(cfs.size());		// increment local size by 1
	}
	BOOST_FOREACH(EventCompFragment *cf, cfs)
		cf->setEventId(event_id);
}

void EventManager::waitForEvent(const unsigned int& event_id) {
	events.at(event_id).waitForEvent();	
	events.erase(event_id); //delete event
}

/*void EventManager::onCFDone(CompFragment *cf) {
	if (cf->isEventCF()) {
		const unsigned int event_id = ((EventCompFragment*)cf)->getEventId();
		events.at(event_id).changeSize(-1);	
	}	
}*/

void EventManager::onCFsDone(const CompFragmentPtrArray& cfs) {
	typedef std::map<unsigned int, int> EventsDoneMap;
	EventsDoneMap events_done;
	BOOST_FOREACH(CompFragment *cf, cfs) 
		if (cf->isEventCF()) {
			const unsigned int event_id = ((EventCompFragment*)cf)->getEventId();
			events_done[event_id]--;
		}
	BOOST_FOREACH(const EventsDoneMap::value_type& p, events_done)
		events.at(p.first).changeSize(p.second);
}
