#pragma once

/*
* Problem data, corresponding to a point(node) with coords (lambda, phi)
*/
class NodeData {
public:
	double u, v, xi;	

public:
	NodeData() : u(0), v(0), xi(0) {} 
	~NodeData() {}
};

class NodeDataCoef {
public:
	double a1, a3;
	double b1;
	double c1, c2;
	double e0, e1, e2, e3;
	double gamma1, gamma2;	
	double d_bc;	
	double rr;

public:
	NodeDataCoef() : d_bc(0) {}
	~NodeDataCoef() {}
};

class NodeDataInteraction {
public:
	double w1, w2, w3;

public:
	NodeDataInteraction() : w1(0), w2(0), w3(0) {}
	~NodeDataInteraction() {}
};
