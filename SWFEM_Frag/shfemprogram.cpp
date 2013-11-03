#include "shfemprogram.h"
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

SHFEMProgram::SHFEMProgram(IRuntimeSystem* s, const size_t& mesh_size_x, const size_t& mesh_size_y, const size_t& fragment_num_x, const size_t& fragment_num_y) : FragmentedProgram(s) {
	this_node = getNodeId();
	num_of_nodes = getNumOfNodes();	

	mesh_fragmentation = DoublingDistribution2D(mesh_size_x, mesh_size_y, fragment_num_x, fragment_num_y); // mesh on fragments
	mesh_distribution = BlockDistribution2D(fragment_num_x, fragment_num_y, 1, num_of_nodes); // fragments by nodes
}

void SHFEMProgram::exec(const size_t& num_of_steps) {
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

		addCF(new CFAlloc(mesh(i, j), data(i, j), data_new(i, j), data_prev(i, j), data_diag(i, j), data_exact(i, j),
			data_coef(i, j), data_interaction(i, j)));

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
			addCF(new CFInteraction(mesh(i, j), data_interaction(i, j), s*cnst::TAU));	// compute interaction data			
			addCF(new CFDiag(mesh(i, j), data_coef(i, j), data_interaction(i, j)));		// compute interactions on s-th time step		
			addCF(new CFJacobyDiag(mesh(i, j), data_diag(i, j), data_coef(i, j)));			// compute diag Jacoby elems		
			addCF(new CFCopy(data_prev(i, j), data(i, j)));								// copy data to prev
		}

		//timer.start();
		processCFs();
		//tp += timer.stop();
		
		sendUpdates(data_diag, upd_left, upd_right, upd_top, upd_bottom);
		recvUpdates(data_diag, upd_left, upd_right, upd_top, upd_bottom);
		//update(data_diag, dg_send_t, dg_recv_t, dg_send_b, dg_recv_b);	// update jacoby diag data

		//timer.start();
		processCFs();
		//tp += timer.stop();

		//timer.start();
		//performUpdate(dg_send_t, dg_recv_t, dg_send_b, dg_recv_b);	// perform data diag update
		//tpu += timer.stop();

		double eps = 1.0;
		while(eps > cnst::EPS) {	// Jacoby method			
			FOREACH(i, j)
				addCF(new CFJacobyMultDirect(mesh(i, j), data_new(i, j), data(i, j), data_prev(i, j), data_coef(i, j)));	// multiplication for Jacoby method			

			//timer.start();
			processCFs();
			//tp += timer.stop();
			
			sendUpdates(data_new, upd_left, upd_right, upd_top, upd_bottom);
			recvUpdates(data_new, upd_left, upd_right, upd_top, upd_bottom);
			//update(data_new, send_t, recv_t, send_b, recv_b);	// update jacoby diag data // update Jacoby mult data						

			//timer.start();
			processCFs();
			//tp += timer.stop();

			//timer.start();
			//performUpdate(send_t, recv_t, send_b, recv_b);	// perform data new update
			//tpu += timer.stop();
							
			FOREACH(i, j) {
				addReductionCF(new CFJacobyReduce(mesh(i, j), data_new(i, j), data(i, j), data_diag(i, j)), iter);	// reduction										
				addCF(new CFCopy(data(i, j), data_new(i, j)));	// copy data new to data
			}

			//timer.start();
			processCFs();
			//tp += timer.stop();			
			
			timer.start();
			eps = getReductionResult(iter);
			tr += timer.stop();							
			
			std::cout << "EPS: " << eps << std::endl;						
			iter++;
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

	// TODO: replace with wait for only this program
	getRTS()->getCFDispatcher()->waitForAllDone();
}

void SHFEMProgram::sendUpdates(DataArray& data, DataArray& left, DataArray& right, DataArray& top, DataArray& bottom) {
	const Region2D& this_block = mesh_distribution.getBlock(this_node);	

	for (size_t i = this_block.getStartByY(); i < this_block.getEndByY(); i++)
	for (size_t j = this_block.getStartByX(); j < this_block.getEndByX(); j++)  {			
		const size_t size_x = mesh_fragmentation.getBlock(i, j).getSizeByX();
		const size_t size_y = mesh_fragmentation.getBlock(i, j).getSizeByY();
		addCF(new CFJacobyUpdateSend(data(i, j), left(i, j), size_x, size_y, CFJacobyUpdate::LEFT));
		addCF(new CFJacobyUpdateSend(data(i, j), right(i, j), size_x, size_y, CFJacobyUpdate::RIGHT));
		addCF(new CFJacobyUpdateSend(data(i, j), top(i, j), size_x, size_y, CFJacobyUpdate::TOP));
		addCF(new CFJacobyUpdateSend(data(i, j), bottom(i, j), size_x, size_y, CFJacobyUpdate::BOTTOM));
	}
}

void SHFEMProgram::recvUpdates(DataArray& data, DataArray& left, DataArray& right, DataArray& top, DataArray& bottom) {
	const Region2D& this_block = mesh_distribution.getBlock(this_node);	

	for (size_t i = this_block.getStartByY(); i < this_block.getEndByY(); i++)
	for (size_t j = this_block.getStartByX(); j < this_block.getEndByX(); j++)  {
		const size_t size_x = mesh_fragmentation.getBlock(i, j).getSizeByX();
		const size_t size_y = mesh_fragmentation.getBlock(i, j).getSizeByY();
		if (j > 0) 
			addCF(new CFJacobyUpdateRecv(data(i, j), right(i, j - 1), size_x, size_y, CFJacobyUpdate::LEFT)); // upd left with right
		if (j < mesh_distribution.getSizeByX() - 1)
			addCF(new CFJacobyUpdateRecv(data(i, j), left(i, j + 1), size_x, size_y, CFJacobyUpdate::RIGHT)); // upd right with left
		if (i > 0)
			addCF(new CFJacobyUpdateRecv(data(i, j), bottom(i - 1, j), size_x, size_y, CFJacobyUpdate::TOP)); // upd top with bottom
		if (i < mesh_distribution.getSizeByY() - 1)
			addCF(new CFJacobyUpdateRecv(data(i, j), top(i + 1, j), size_x, size_y, CFJacobyUpdate::BOTTOM)); // upd bottom with top
	}
}


