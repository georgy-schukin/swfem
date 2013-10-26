#include "shfemmpicontroller.h"
#include "cfshfem.h"
#include "meshfragment.h"
#include "data.h"
#include "cnst.h"
#include "auxilary.h"
#include "timer.h"
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/scoped_array.hpp>
#include <sstream>

using namespace std;

SHFEMMPIController::SHFEMMPIController(IRuntimeSystem *s, size_t mx, size_t my) : 
	FPController(s), mesh_size_x(mx), mesh_size_y(my) {

	node_rank = getNodeId();
	node_size = getNumOfNodes();

	aux::sliceMesh(mesh_size_y, node_size, start_y, ny); // slice mesh between nodes by Y
}

void SHFEMMPIController::exec(size_t num_of_steps) {
	const double bx = 0.0;
	const double by = 90.0;	
	const double sx = (10.0 - bx)/(mesh_size_x - 1);
	const double sy = (100.0 - by)/(mesh_size_y - 1);

	MeshBlockFragment mesh;
	Data data, data_new, data_prev, data_diag, data_exact;	
	DataCoef data_coef;	
	DataInteraction data_interaction;

	Timer timer_u;
	double tu = 0;

	CFGen(bx, by, sx, sy, mesh_size_x, mesh_size_y, 0, start_y[node_rank], mesh_size_x, ny[node_rank]).exec(mesh);

	CFInit().exec(mesh, data, data_coef);
	CFExact(0).exec(mesh, data);
	CFExact(0).exec(mesh, data_exact);
	CFCoef().exec(mesh, data_coef);		
	
	size_t iter = 0;
	for(size_t s = 1;s <= num_of_steps;s++) {		
		CFInteraction(s*cnst::TAU).exec(mesh, data_interaction);		
		CFDiag().exec(mesh, data_coef, data_interaction);
		CFJacobyDiag().exec(mesh, data_diag, data_coef);
		CFCopy().exec(data_prev, data);		

		//timer_u.start();
		update(data_diag);
		//tu += timer_u.stop();

		double eps = 1.0;
		while(eps > cnst::EPS) {	// Jacoby method
			CFJacobyMultDirect().exec(mesh, data_new, data, data_prev, data_coef);									
			//timer_u.start();
			update(data_new);
			//tu += timer_u.stop();
			double local_eps = CFJacobyReduce().exec(mesh, data_new, data, data_diag);
			CFCopy().exec(data, data_new);
			eps = getRTS()->getCommunicator()->allReduce(local_eps);

			//cout << "EPS: " << eps << endl;

			iter++;
		}				
	}
	//ostringstream out;
	//out << getRTS()->getCommunicator()->getRank() << " : Iters " << iter << endl;
	//cout << out.str();
}

void SHFEMMPIController::update(Data& data) {
	if(node_rank % 2 == 0) {
		if(node_rank > 0) update(data, 0, mesh_size_x, node_rank - 1, node_rank);	// top
		if(node_rank < node_size - 1) update(data, (ny[node_rank] - 1)*mesh_size_x, mesh_size_x, node_rank + 1, node_rank);	// bottom
	} else {
		if(node_rank < node_size - 1) update(data, (ny[node_rank] - 1)*mesh_size_x, mesh_size_x, node_rank + 1, node_rank + 1);	// bottom
		if(node_rank > 0) update(data, 0, mesh_size_x, node_rank - 1, node_rank - 1);	// top
	}
}

void SHFEMMPIController::update(Data& data, size_t start, size_t num, int rank, int tag) {
	Data send(num);
	Data recv(num);
	//CFJacobyUpdateSend(start, 1, num).exec(data, send);
	boost::scoped_array<double> buf(new double[num*3]);
	copyToBuffer(send, buf.get());
	getRTS()->getCommunicator()->sendRecvReplace(buf.get(), num*3*sizeof(double), tag, rank, tag, rank);
	copyFromBuffer(recv, buf.get());
	//CFJacobyUpdateRecv(start, 1, num).exec(data, recv);
}

void SHFEMMPIController::copyToBuffer(const Data& data, double* buf) {	
	size_t p = 0;
	BOOST_FOREACH(const NodeData& dt, data) {
		buf[p] = dt.u;
		buf[p + 1] = dt.v;
		buf[p + 2] = dt.xi;
		p += 3;
	}
}

void SHFEMMPIController::copyFromBuffer(Data& data, const double* buf) {
	size_t p = 0;
	BOOST_FOREACH(NodeData& dt, data) {
		dt.u = buf[p];
		dt.v = buf[p + 1];
		dt.xi = buf[p + 2];		
		p += 3;
	}
}
