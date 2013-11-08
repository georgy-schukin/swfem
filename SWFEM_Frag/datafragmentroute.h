#pragma once

#include <queue>
#include <cassert>

class CompFragment;

class DataFragmentRoute {
public:
	class RoutePoint {
	private:
		class CompFragment *cf;
		int node;
	public:
		RoutePoint() : cf(0), node(-1) {}
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
	std::queue<RoutePoint> route;

public:
	DataFragmentRoute() {}	
	~DataFragmentRoute() {}

	void addPoint(const RoutePoint& point) {
		route.push(point);
	}	

	RoutePoint getNextPoint() {
		assert(!route.empty());
		if (!route.empty()) {
			RoutePoint point = route.front();						
			route.pop();		
			return point;
		}		
		return RoutePoint(0, -1);
	}

	const RoutePoint& peekNextPoint() const {
		assert(!route.empty());
		return route.front();
	}

	CompFragment* peekNextCF() const {
		return route.front().getCF();
	}

	bool isEmpty() const {
		return route.empty();
	}	
};
