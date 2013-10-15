#pragma once

#include <cstddef>

/*
* Base element of a mesh - triangle (3 points/nodes)
*/
class MeshTriangle {
public:
	size_t id;		// id (number) of a triangle
	size_t n[3];	// points of a triangle - indices of nodes (ccw)
	int edge[3];	// edge types (ccw)	
	double square;	// square of triangle

public:
	MeshTriangle() {}
	~MeshTriangle() {}
};
