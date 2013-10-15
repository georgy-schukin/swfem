#pragma once

#include <string>

/**
 * Logs events for MPE
 */
class MPELogger {
public:
	class MPEEvent {
	public:
		int start;
		int end;

	public:
		MPEEvent() : start(0), end(0) {}
		~MPEEvent() {}
	};

public:
	MPELogger() {}
	~MPELogger() {}

	MPELogger::MPEEvent newEvent(const std::string& name, const std::string& color);

	void logStart(MPELogger::MPEEvent& evnt); 
	void logEnd(MPELogger::MPEEvent& evnt); 
};