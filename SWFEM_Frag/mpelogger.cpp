#ifdef ENABLE_MPE
#include <mpe.h>
#endif
#include "mpelogger.h"

MPELogger::MPEEvent MPELogger::newEvent(const std::string& name, const std::string& color) {
	MPELogger::MPEEvent evnt;

#ifdef ENABLE_MPE
	evnt.start = MPE_Log_get_event_number();
	evnt.end = MPE_Log_get_event_number();
	MPE_Describe_state(evnt.start, evnt.end, name.c_str(), color.c_str());
#endif

	return evnt;
}

void MPELogger::logStart(MPELogger::MPEEvent& evnt) {
#ifdef ENABLE_MPE
	MPE_Log_event(evnt.start, 0, 0);
#endif
}

void MPELogger::logEnd(MPELogger::MPEEvent& evnt) {
#ifdef ENABLE_MPE
	MPE_Log_event(evnt.end, 0, 0);
#endif
}