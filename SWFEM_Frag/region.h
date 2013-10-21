#pragma once

class Region {
private:
	size_t start;
	size_t end;

public:
	Region() : start(0), end(0) {}	
	Region(const size_t& s, const size_t& e) : start(s), end(e) {}
	Region(const Region& r) : start(r.start), end(r.end) {}
	~Region() {}

	size_t getStart() const {
		return start;
	}
	
	size_t getEnd() const {
		return end;
	}

	size_t getSize() const {
		return end - start;
	}
};