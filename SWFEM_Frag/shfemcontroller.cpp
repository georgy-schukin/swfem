#include "shfemcontroller.h"
#include "cfshfem.h"
#include "cnst.h"
#include "updater.h"
#include "timer.h"
#include <iostream>
#include <sstream>
#include <boost/foreach.hpp>

#define FORX(i) for (size_t i = this_block.getStartByX(); i < this_block.getEndByX(); i++)
#define FORY(i) for (size_t i = this_block.getStartByY(); i < this_block.getEndByY(); i++)
#define FOREACH(i,j) FORY(i) FORX(j)

SHFEMController::SHFEMController(IRuntimeSystem* s, const size_t& mesh_size_x, const size_t& mesh_size_y, const size_t& fragment_num_x, const size_t& fragment_num_y) : FPController(s) {
	this_node = getNodeId();
	num_of_nodes = getNumOfNodes();	

	mesh_fragmentation = DoublingDistribution2D(mesh_size_x, mesh_size_y, fragment_num_x, fragment_num_y); 
	mesh_distribution = BlockDistribution2D(fragment_num_x, fragment_num_y, 1, num_of_nodes); // distr array of fragments by nodes
}

void SHFEMController::exec(const size_t& num_of_steps) {
	const Region2D& this_block = mesh_distribution.getBlock(this_node);	

	MeshArray mesh(mesh_distribution, this_node); 

	DataArray data(mesh_distribution, this_node);	
	DataArray data_new(mesh_distribution, this_node);	
	DataArray data_prev(mesh_distribution, this_node);	
	DataArray data_diag(mesh_distribution, this_node);	
	DataArray data_exact(mesh_distribution, this_node);	
	DataCoefArray data_coef(mesh_distribution, this_node);	
	DataInteractionArray data_interaction(mesh_distribution, this_node);

	DataArray upd_left(mesh_distribution, this_node);
	DataArray upd_right(mesh_distribution, this_node);
	DataArray upd_top(mesh_distribution, this_node);
	DataArray upd_bottom(mesh_distribution, this_node);

	Timer timer;
	double td = 0, tc = 0, tp = 0, tu = 0, tpu = 0, tr = 0;

	const size_t mesh_size_x = mesh_fragmentation.getSizeByX();
	const size_t mesh_size_y = mesh_fragmentation.getSizeByY();
	const double beg_x = 0.0;
	const double beg_y = 90.0;		
	const double step_x = (10.0 - beg_x)/(mesh_size_x - 1);
	const double step_y = (100.0 - beg_y)/(mesh_size_y - 1);		
	
	FOREACH(i, j) {
		const Region2D& block = mesh_fragmentation.getBlock(i, j);				

		addCF(new CFGen(mesh(i, j), beg_x, beg_y, step_x, step_y, mesh_size_x, mesh_size_y, 
			block.getStartByX(), block.getStartByY(), block.getSizeByX(), block.getSizeByY()));	// generate mesh	
		addCF(new CFInit(mesh(i, j), data(i, j), data_coef(i, j)));	// init data	
		addCF(new CFExact(mesh(i, j), data(i, j), 0));				// init by exact solution	
		addCF(new CFExact(mesh(i, j), data_exact(i, j), 0));			// get exact solution	
		addCF(new CFCoef(mesh(i, j), data_coef(i, j)));				// compute coefs
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
		
		sendUpdates(mesh, data_diag, upd_left, upd_right, upd_top, upd_bottom);
		recvUpdates(mesh, data_diag, upd_left, upd_right, upd_top, upd_bottom);
		//update(data_diag, dg_send_t, dg_recv_t, dg_send_b, dg_recv_b);	// update jacoby diag data

		timer.start();
		processCFs();
		tp += timer.stop();

		//timer.start();
		//performUpdate(dg_send_t, dg_recv_t, dg_send_b, dg_recv_b);	// perform data diag update
		//tpu += timer.stop();

		double eps = 1.0;
		while(eps > cnst::EPS) {	// Jacoby method			
			FOREACH(i, j)
				addCF(new CFJacobyMultDirect(mesh(i, j), data_new(i, j), data(i, j), data_prev(i, j), data_coef(i, j)));	// multiplication for Jacoby method			

			timer.start();
			processCFs();
			tp += timer.stop();
			
			sendUpdates(mesh, data_new, upd_left, upd_right, upd_top, upd_bottom);
			recvUpdates(mesh, data_new, upd_left, upd_right, upd_top, upd_bottom);
			//update(data_new, send_t, recv_t, send_b, recv_b);	// update jacoby diag data // update Jacoby mult data						

			timer.start();
			processCFs();
			tp += timer.stop();

			//timer.start();
			//performUpdate(send_t, recv_t, send_b, recv_b);	// perform data new update
			//tpu += timer.stop();
							
			FOREACH(i, j) {
				addReductionCF(new CFJacobyReduce(mesh(i, j), data_new(i, j), data(i, j), data_diag(i, j)), red_id);	// reduction										
				addCF(new CFCopy(data(i, j), data_new(i, j)));	// copy data new to data
			}

			timer.start();
			processCFs();
			tp += timer.stop();			
			
			timer.start();
			eps = getReductionResult(red_id++);
			tr += timer.stop();							

			iter++;
			std::cout << "EPS: " << eps << std::endl;						
		}				
	}	
	std::ostringstream out;
	out << this_node << " :"
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

void SHFEMController::sendUpdates(MeshArray& mesh, DataArray& data, DataArray& left, DataArray& right, DataArray& top, DataArray& bottom) {
	const Region2D& this_block = mesh_distribution.getBlock(this_node);	

	for (size_t i = this_block.getStartByY(); i < this_block.getEndByY(); i++)
	for (size_t j = this_block.getStartByX(); j < this_block.getEndByX(); j++)  {
		addCF(new CFJacobyUpdateSend(mesh(i, j), data(i, j), left(i, j), CFJacobyUpdate::LEFT));
		addCF(new CFJacobyUpdateSend(mesh(i, j), data(i, j), right(i, j), CFJacobyUpdate::RIGHT));
		addCF(new CFJacobyUpdateSend(mesh(i, j), data(i, j), top(i, j), CFJacobyUpdate::TOP));
		addCF(new CFJacobyUpdateSend(mesh(i, j), data(i, j), bottom(i, j), CFJacobyUpdate::BOTTOM));
	}
}

void SHFEMController::recvUpdates(MeshArray& mesh, DataArray& data, DataArray& left, DataArray& right, DataArray& top, DataArray& bottom) {
	const Region2D& this_block = mesh_distribution.getBlock(this_node);	

	for (size_t i = this_block.getStartByY(); i < this_block.getEndByY(); i++)
	for (size_t j = this_block.getStartByX(); j < this_block.getEndByX(); j++)  {
		if (j > 0) 
			addCF(new CFJacobyUpdateRecv(mesh(i, j), data(i, j), right(i, j - 1), CFJacobyUpdate::LEFT)); // upd left with right
		if (j < mesh_distribution.getSizeByX() - 1)
			addCF(new CFJacobyUpdateRecv(mesh(i, j), data(i, j), left(i, j + 1), CFJacobyUpdate::RIGHT)); // upd right with left
		if (i > 0)
			addCF(new CFJacobyUpdateRecv(mesh(i, j), data(i, j), bottom(i - 1, j), CFJacobyUpdate::TOP)); // upd top with bottom
		if (i < mesh_distribution.getSizeByY() - 1)
			addCF(new CFJacobyUpdateRecv(mesh(i, j), data(i, j), top(i + 1, j), CFJacobyUpdate::BOTTOM)); // upd bottom with top
	}
}

/*void SHFEMController::update(DFArray2D<Data>& dt, DFArray1D<Data>& st, DFArray1D<Data>& rt, DFArray1D<Data>& sb, DFArray1D<Data>& rb) {
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
}*/

