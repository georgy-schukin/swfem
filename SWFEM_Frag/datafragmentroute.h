#pragma once

#include <queue>

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
		if (!route.empty()) {
			RoutePoint point = route.front();						
			route.pop();		
			return point;
		}		
		return RoutePoint(0, -1);
	}

	const RoutePoint& peekNextPoint() {
		return route.front();
	}

	bool isEmpty() const {
		return route.empty();
	}	
};
