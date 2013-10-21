#include "shfemcontroller.h"
#include "cfshfem.h"
#include "cnst.h"
#include "updater.h"
#include "auxilary.h"
#include "timer.h"
#include "distribution2d.h"
#include "dfarray2d.h"
#include <iostream>
#include <sstream>
#include <boost/foreach.hpp>

SHFEMController::SHFEMController(IRuntimeSystem* s) : FPController(s) {
	this_node = getNodeId();
	num_of_nodes = getNumOfNodes();	
}

#define FOREACH(i,j) for (size_t i = 0; i < fy; i++) for (size_t j = 0; j < fx; j++)

void SHFEMController::exec(const size_t& mesh_size_x, const size_t& mesh_size_y, const size_t& fragment_num_x, const size_t& fragment_num_y, const size_t& num_of_steps) {
	const double beg_x = 0.0;
	const double beg_y = 90.0;		
	const double step_x = (10.0 - beg_x)/(mesh_size_x - 1);
	const double step_y = (100.0 - beg_y)/(mesh_size_y - 1);		

	distribute(mesh_size_x, mesh_size_y, fragment_num_x, fragment_num_y, mesh_data);

	mesh_distribution.init(fragment_num_x, fragment_num_y, 1, num_of_nodes); // distr array of fragments by nodes

	const DistributionBlock2D& this_block = mesh_distribution.getBlock(this_node);

	const size_t fy = this_block.getSizeByY();
	const size_t fx = this_block.getSizeByX();
		
	//const size_t fx = mesh_data.nx.size();	// num of fragments on this node by X
	//const size_t fy = mesh_data.ny.size();	// num of fragments on this node by Y

	DFArray2D<MeshFragment> mesh(fy, fx); 

	DFArray2D<Data> data(fy, fx);	
	DFArray2D<Data> data_new(fy, fx);	
	DFArray2D<Data> data_prev(fy, fx);	
	DFArray2D<Data> data_diag(fy, fx);	
	DFArray2D<Data> data_exact(fy, fx);	
	DFArray2D<DataCoef> data_coef(fy, fx);	
	DFArray2D<DataInteraction> data_interaction(fy, fx);

	DFArray2D<Data> data_send_left(fy, fx), data_send_right(fy, fx), data_send_top(fy, fx), data_send_bottom(fy, fx); // for Jacoby update send
	DFArray2D<Data> data_recv_left(fy, fx), data_recv_right(fy, fx), data_recv_top(fy, fx), data_recv_bottom(fy, fx); // for Jacoby update recv


//	DFArray1D<Data> send_t(fx), send_b(fx);
//	DFArray1D<Data> recv_t(fx), recv_b(fx);

//	DFArray1D<Data> dg_send_t(fx), dg_send_b(fx);
//	DFArray1D<Data> dg_recv_t(fx), dg_recv_b(fx);

	//send_t.setId(0);	// set id for updates
	//send_b.setId(1);	
	//dg_send_t.setId(2);
	//dg_send_b.setId(3);

	Timer timer;
	double td = 0, tc = 0, tp = 0, tu = 0, tpu = 0, tr = 0;
	
	FOREACH(i, j) {
		const size_t& stx = mesh_data.start_x[j];
		const size_t& sty = mesh_data.start_y[i];
		const size_t& nx = mesh_data.nx[j];
		const size_t& ny = mesh_data.ny[i];

		addCF(new CFGen(mesh(i, j), beg_x, beg_y, step_x, step_y, mesh_size_x, mesh_size_y, stx, sty, nx, ny), i*fx + j);	// generate mesh	
		addCF(new CFInit(mesh(i, j), data(i, j), data_coef(i, j)), i*fx + j);	// init data	
		addCF(new CFExact(mesh(i, j), data(i, j), 0), i*fx + j);				// init by exact solution	
		addCF(new CFExact(mesh(i, j), data_exact(i, j), 0), i*fx + j);			// get exact solution	
		addCF(new CFCoef(mesh(i, j), data_coef(i, j)), i*fx + j);				// compute coefs
	}

	timer.start();
	processCFs();
	tp += timer.stop();
	
	size_t red_id = 0;
	size_t iter = 0;
	for (size_t s = 1; s <= num_of_steps; s++) {	// for each time step		

		FOREACH(i, j) {
			addCF(new CFInteraction(mesh(i, j), data_interaction(i, j), s*cnst::TAU), i*fx + j);	// compute interaction data			
			addCF(new CFDiag(mesh(i, j), data_coef(i, j), data_interaction(i, j)), i*fx + j);		// compute interactions on s-th time step		
			addCF(new CFJacobyDiag(mesh(i, j), data_diag(i, j), data_coef(i, j)), i*fx + j);			// compute diag Jacoby elems		
			addCF(new CFCopy(data_prev(i, j), data(i, j)), i*fx + j);								// copy data to prev
		}

		timer.start();
		processCFs();
		tp += timer.stop();
		
		update(data_diag, dg_send_t, dg_recv_t, dg_send_b, dg_recv_b);	// update jacoby diag data

		timer.start();
		processCFs();
		tp += timer.stop();

		timer.start();
		performUpdate(dg_send_t, dg_recv_t, dg_send_b, dg_recv_b);	// perform data diag update
		tpu += timer.stop();

		double eps = 1.0;
		while(eps > cnst::EPS) {	// Jacoby method			
			FOREACH(i, j)
				addCF(new CFJacobyMultDirect(mesh(i, j), data_new(i, j), data(i, j), data_prev(i, j), data_coef(i, j)), i*fx + j);	// multiplication for Jacoby method			

			timer.start();
			processCFs();
			tp += timer.stop();
			
			update(data_new, send_t, recv_t, send_b, recv_b);	// update jacoby diag data // update Jacoby mult data						

			timer.start();
			processCFs();
			tp += timer.stop();

			timer.start();
			performUpdate(send_t, recv_t, send_b, recv_b);	// perform data new update
			tpu += timer.stop();
							
			FOREACH(i, j) {
				addReductionCF(red_id, new CFJacobyReduce(mesh(i, j), data_new(i, j), data(i, j), data_diag(i, j)), i*fx + j);	// reduction										
				addCF(new CFCopy(data(i, j), data_new(i, j)), i*fx + j);	// copy data new to data
			}

			timer.start();
			processCFs();
			tp += timer.stop();			
			
			timer.start();
			eps = getReductionResult(red_id++);
			tr += timer.stop();							

			iter++;
			cout << "EPS: " << eps << endl;						
		}				
	}	
	std::ostringstream out;
	out << node_rank << " :"
		//<< " Create " << tc
		//<< " Data " << td
		<< " Process " << tp 		
		//<< " Update " << tu 
		<< " Perform " << tpu
		<< " Reduce " << tr
		<< " Iters " << iter
		<< std::endl;	
	std::cout << out.str();	

	// TODO: replace with wait for only this controller
	getRTS()->getCFDispatcher()->waitForAllDone();
}

void SHFEMController::update(DFArray2D<Data>& dt, DFArray1D<Data>& st, DFArray1D<Data>& rt, DFArray1D<Data>& sb, DFArray1D<Data>& rb) {
	innerUpdate(dt);
	if (node_rank % 2 == 0) {
		if (node_rank > 0)
			outerUpdateTop(dt, st, rt);	// top
		if (node_rank < node_size - 1)
			outerUpdateBottom(dt, sb, rb);// bottom
	} else {
		if (node_rank < node_size - 1)
			outerUpdateBottom(dt, sb, rb);// bottom
		if (node_rank > 0)
			outerUpdateTop(dt, st, rt);	// top
	}	
}

void SHFEMController::innerUpdate(DFArray2D<Data>& dt) {
	for (size_t i = 0; i < dt.getSizeByY() - 1; i++) 
	for (size_t j = 0; j < dt.getSizeByX(); j++) {
		const size_t num = mesh_data.nx[j]; 
		const size_t start = (mesh_data.ny[i] - 1)*mesh_data.nx[j];
		addCF(new CFJacobyUpdate(dt(i, j), dt(i + 1, j), start, 1, 0, 1, num)); // Jacoby update (vertical, update hor lines)						
	}

	for (size_t i = 0; i < dt.getSizeByY(); i++) 
	for (size_t j = 0; j < dt.getSizeByX() - 1; j++) {
		const size_t num = mesh_data.ny[i]; 
		const size_t start = mesh_data.nx[j] - 1;
		const size_t step_l = mesh_data.nx[j];
		const size_t step_r = mesh_data.nx[j + 1];
		addCF(new CFJacobyUpdate(dt(i, j), dt(i, j + 1), start, step_l, 0, step_r, num)); // Jacoby update (horizontal, update vert lines)						
	}
}

void SHFEMController::outerUpdateTop(DFArray2D<Data>& dt, DFArray1D<Data>& send, DFArray1D<Data>& recv) {
	lockDFs(recv.getData()); // lock recv dfs (until values is received by MPI later)
	
	const size_t i = 0; // top line of fragments
	for (size_t j = 0; j < send.getSize(); j++) {
		const size_t start = 0;
		const size_t num = mesh_data.nx[j];
		addEventCF(send.getId(), new CFJacobyUpdateSend(dt(i, j), send(j), start, 1, num)); // copy top nodes of fragment to send
		addCF(new CFJacobyUpdateRecv(dt(i, j), recv(j), start, 1, num)); // add to top nodes of fragment from recv
	}
}

void SHFEMController::outerUpdateBottom(DFArray2D<Data>& dt, DFArray1D<Data>& send, DFArray1D<Data>& recv) {
	lockDFs(recv.getData()); // lock recv dfs (until values is received by MPI later)

	const size_t i = dt.getSizeByY() - 1; // bottom line
	for (size_t j = 0; j < send.getSize(); j++) {
		const size_t start = (mesh_data.ny[i] - 1)*mesh_data.nx[j];
		const size_t num = mesh_data.nx[j];
		addEventCF(send.getId(), new CFJacobyUpdateSend(dt(i, j), send(j), start, 1, num)); // copy bottom nodes of fragment to send
		addCF(new CFJacobyUpdateRecv(dt(i, j), recv(j), start, 1, num)); // add to bottom nodes of fragment from recv
	}
}

void SHFEMController::performUpdate(DFArray& st, DFArray& rt, DFArray& sb, DFArray& rb) {	
	if (node_rank % 2 == 0) {
		if (node_rank > 0)
			performOuterUpdate(st, rt, node_rank, node_rank - 1);	// top
		if (node_rank < node_size - 1)
			performOuterUpdate(sb, rb, node_rank, node_rank + 1);	// bottom
	} else {		
		if (node_rank < node_size - 1)
			performOuterUpdate(sb, rb, node_rank + 1, node_rank + 1);	// bottom
		if (node_rank > 0)
			performOuterUpdate(st, rt, node_rank - 1, node_rank - 1);	// top
	}
}

void SHFEMController::performOuterUpdate(DFArray& send, DFArray& recv, const int& tag, const int& rank) {
	waitForEvent(send.getId()); // wait until send data are ready

	Updater(getRTS()->getCommunicator()).update(send.getData(), recv.getData(), tag, rank);

	unlockDFs(recv.getData()); // unlock received data
}

void SHFEMController::distribute(const size_t& mesh_size_x, const size_t& mesh_size_y, const size_t& fragment_num_x, const size_t& fragment_num_y, MeshData& m_data) {
	MeshData global_data;

	aux::sliceMesh(mesh_size_x, fragment_num_x, global_data.start_x, global_data.nx);	// slice mesh between fragments by X
	aux::sliceMesh(mesh_size_y, fragment_num_y, global_data.start_y, global_data.ny);	// slice mesh between fragments by Y
	
	m_data.start_x = global_data.start_x; // don't distribute by X
	m_data.nx = global_data.nx;

	size_t f_start_y, f_end_y;
	aux::distributeFragments(fragment_num_y, node_rank, node_size, f_start_y, f_end_y); // distribute by Y on all nodes	

	m_data.start_y.insert(m_data.start_y.end(), global_data.start_y.begin() + f_start_y, global_data.start_y.begin() + f_end_y);	
	m_data.ny.insert(m_data.ny.end(), global_data.ny.begin() + f_start_y, global_data.ny.begin() + f_end_y);	
}

