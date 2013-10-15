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
		RoutePoint(CompFragment *c, const int& n): cf(c), node(n) {}
		RoutePoint(const RoutePoint& p) : cf(p.cf), node(p.node) {}
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

	void addRoutePoint(CompFragment *cf, const int& node = -1) {
		route.push(DataFragment::RoutePoint(cf, node));
	}	

	int getNextRoutePoint(CompFragment **cf, int& node) {
		if (!route.empty()) {
			const DataFragment::RoutePoint& point = route.front();			
			*cf = point.getCF();
			node = point.getNode();
			route.pop();
			return 0;
		}
		return -1;
	}

	bool isRouteEmpty() const {
		return route.empty();
	}

	virtual ~DataFragment() {}
	virtual unsigned int getWeight() = 0;
};

typedef std::vector<DataFragment*> DataFragmentPtrArray;
