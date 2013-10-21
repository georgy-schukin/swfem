#pragma once

#include "compfragment.h"

class EventCompFragment : public CompFragment {
private:
	size_t event_id;

public:
	EventCompFragment() : event_id(0) {}
	virtual ~EventCompFragment() {}

	void setEventId(size_t event_id) {
		this->event_id = event_id;
	}

	size_t getEventId() const {
		return event_id;
	}

	bool isEventCF() const {
		return true;
	}
};

typedef std::vector<EventCompFragment*> EventCompFragmentPtrArray;
