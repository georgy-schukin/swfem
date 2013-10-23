#pragma once

#include <queue>
#include <vector>

class CompFragment;

/**
* Generic data fragment (piece of data)
*/
class DataFragment {
public:
	class RoutePoint {
	private:
		CompFragment* cf;
		int node;
	public:
		RoutePoint() : cf(0), node(-1) {}
		RoutePoint(CompFragment *c, const int& n): cf(c), node(n) {}		
		~RoutePoint() {}

		CompFragment* getCF() const {
			return cf;
		}

		int getNode() const {
			return node;
		}
	};

private:	
	bool is_locked;
	std::queue<DataFragment::RoutePoint> route;

public:
	DataFragment() : is_locked(false) {}	

	void lock() {
		this->is_locked = true;
	}

	void unlock() {
		this->is_locked = false;
	}

	bool isLocked() const {
		return is_locked;
	}

	bool isReady() const {
		return (!is_locked && !route.empty());
	}

	void addRoutePoint(const DataFragment::RoutePoint& point) {
		route.push(point);
	}	

	DataFragment::RoutePoint getNextRoutePoint() {
		if (!route.empty()) {
			DataFragment::RoutePoint point = route.front();						
			route.pop();		
			return point;
		}		
		return DataFragment::RoutePoint(0, -1);
	}

	bool isRouteEmpty() const {
		return route.empty();
	}

	virtual ~DataFragment() {}
	virtual size_t getWeight() = 0;
};

typedef std::vector<DataFragment*> DataFragmentPtrArray;
