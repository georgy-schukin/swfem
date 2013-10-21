#pragma once

/*
* Node(point) of a mesh
*/
class MeshNode {	
public:
	double lambda;		// coord by lambda
	double phi;			// coord by phi
	double depth;		// depth of a sea in this point
	size_t id;	// id (number) of a node

public:
	MeshNode() {}
	~MeshNode() {}
};
