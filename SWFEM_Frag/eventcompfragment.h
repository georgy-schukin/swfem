#pragma once

#include "compfragment.h"

class EventCompFragment : public CompFragment {
private:
	unsigned int event_id;

public:
	EventCompFragment() : event_id(0) {}
	virtual ~EventCompFragment() {}

	void setEventId(unsigned int event_id) {
		this->event_id = event_id;
	}

	unsigned int getEventId() const {
		return event_id;
	}

	bool isEventCF() const {
		return true;
	}
};

typedef std::vector<EventCompFragment*> EventCompFragmentPtrArray;
