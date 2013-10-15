#pragma once

#include <math.h>

namespace cnst {
	const double PI = 3.1415926535897932384626433832795;
	const double PI_DIV_2 = PI/2.0;
	const double PI_DIV_180 = PI/180.0;

	const double RF = 0.0;			//2.60e-3 // constant for frictions define
	const double BETA = 1.0;		// parameter in the boundary conditions
	const double ALPHA = 1.0E-3;	// parameter before d^m in iteration for d
	const double P = 0.8;			// parameter at gamma_opt
//#define gamma (double)0.4 // parameter at gamma_opt

//#define gamma (double)0.2 // parameter in in iteration for d	

	const double TAU = 1.0;			// time step in seconds
	const double TAU1 = 1.0/TAU;

	const double EPS = 1.0e-10;		// precision 

// The numerical methods parameters
//#define exact_jac (double)1.e-10 // this is an exactness of Jacoby method now
//#define exact_d (double)2.e-3 // this is an exactness for d determination !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//#define exact_solv (double)5.e-5 // this is an exactness for determination of steady-state solution

	//The parameters of differential problem
	const double G = 9.81; // gravitation constant

	//Parameters for sphera and Coriolysis
	const double RADIUS = 6.367456E+6; //radius of the Earth
	const double OMEGA = 0.7292E-4; // speed of rotation of the Earth
	const double OMEGA2 = 2*OMEGA;
}
