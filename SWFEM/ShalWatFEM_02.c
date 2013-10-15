#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <math.h>

#include "My_def.h"


/* ***************************************************************************** */
/*                                                                               */
/*                           Global parameters                                   */
/*                                                                               */
/* ***************************************************************************** */

//The parameters of differential problem
double g=9.81; // gravitation constant

//Parameters for sphera and Coriolysis
double radius=6.367456E6; //radius of the Earth
double omega=0.7292E-4; // speed of rotation of the Earth

double tau1=1/tau_fix;


/* ***************************************************************************** */
/*                                                                               */
/*                            main() begin                                       */
/*                                                                               */
/* ***************************************************************************** */


int main(int argc, char* argv[])
{
	#if (ind_rich == 1)
		int dim=801;
	#endif


	// Files definitions
	// names of infiles
	#if ind_test==1
		char name_in1[]="pts801dir.dat",
			 name_in2[]="tr801dir.dat";

	#elif ind_test==2 && ind_problem==1
		char name_in1[]="ptsOkh51Angle.dat",
			 name_in2[]="trOkh51Angle.dat";

	#elif ind_test==2 && ind_problem==0
		char name_in1[]="ptsOkhu51.dat",
			 name_in2[]="trOkh51obs.dat";

	#elif ind_test==3
		char name_in1[15]="Point.dat",
		     name_in2[15]="Trian.dat";
	#endif

	//prefix of outfiles
	char name_fix[]="out";
	char name_fix1[]="res";// out vectors of solutions (lambda,phi,u,v,xi) to direct problem

	char name[30]; // name of the help out file
	char temp[]="ind_pts.txt";
	FILE *in_file,*out_file0;//,*out_file;

	// The space parameters
	int MAX_NUM_OF_PTS, //number of points of the grid
		NUM_OF_Gamma2=0, //number of points belong to Gamma_2
		NUM_OF_TR,	//number of triangles
	    DIM_MATR_TR; //dimantion of arrays for informations about triangles

	/* ***************************************************************************** */
	/*                                                                               */
	/*                    definitions of main variables                              */
	/*                                                                               */
	/* ***************************************************************************** */

	//The known functions and variables of the differential problem
	double *lmbd, // lambda values
		   *phi,  // phi values
		   *H,  // depth
		   *RR, // frictions
		   *W1,*W2,*W3, // outside effect in three directions
		   *D_BC; //the right hand part in the boundary conditions for elevation on the free surface


	//Unknown of the problem
	double *u,*v, // vilocities components
		   *xi; // elevation on the free surface
	// and the same on the priviouse time lavel
	double *u_old, *v_old, *xi_old;
	double *u_new, *v_new, *xi_new;

	//Exact solution
	#if ind_test==1
		double *u_exact, *v_exact, *xi_exact;
	#endif

	//Parameters for Jacoby iteration
	double *a1, *a3, *b1, *c1, *c2, *e1, *e2, *e3, *e0, *gamma1, *gamma2;
	//diagonal D for Jacoby iteration: U^(n+1)=U^(n)-D^(-1)(AU^(n)-F)
	double *diag_u, *diag_v, *diag_xi;

	//for compare of solutions
	#if ind_test==1
		double *dif_u, *dif_v, *dif_xi;
	#endif

	//Parameters of triangulations
	double  *S;  // square of triangl multiply by 1/3
	int	**tr; //  appearance of points to triangles
	int **ind_tr; //  characteristic of side of triangle (1 is right angle)
		//   <0 when side belongs to Gamma2 ('liquid') boundary;
		//   >0 when side belongs to Gamma1 ('solid') boundary;
		//     = 0     inner side,


	int *ind_pts; //  characteristic of points of the grid (see above)


	/* ***************************************************************************** */
	/*                                                                               */
	/*                            help variables of main()                           */
	/*                                                                               */
	/* ***************************************************************************** */

	//for compare of solutions
	double  difference[4]={0.,0.,0.,0.}, // the maximum of difference between exact and numerical solutions
			min[4]={0.,0.,0.,0.}, //minimum of numerical solutions
			max[4]={0.,0.,0.,0.}, //maximum of numerical solutions
			be_max[4]={0.,0.,0.,0.}, //maximum of numerical solutions exclusive of solid boundary
			L_2_norm[4]={0.,0.,0.,0.}; // L_2 norm of error

	int max_num[4]={0,0,0,0}; // the number of points where there is maximum of numerical solutions
	int min_num[4]={0,0,0,0}; // the number of points where there is minimum of numerical solutions
	int be_max_num[4]={0,0,0,0};	// the number of points where there is maximum of numerical solutions
									// exclusive of solid boundary


	double tt,err_max=1;
	div_t tmp1, tmp2, tmp3;
	int hlp1,now_n;
	int ii=0,kk=0,mm=0,jj=0,ll=0;
	char help_ch='q';

	#if ind_plot==1
		int pic=0;
	#endif

	/* ***************************************************************************** */
	/*                                                                               */
	/*                        the begin of algorithm in main()                       */
	/*                                                                               */
	/* ***************************************************************************** */


	/* ***************************************************************************** */
	/*                                                                               */
	/*                               open the file                                   */
	/*             the information about number of points is reading                 */
	/*                                                                               */
	/* ***************************************************************************** */

	//text file open for read data about points
	if ((in_file=fopen(name_in1, "r"))==NULL)
	{
		printf("Error at opening of the file.\n");
		exit(1);
	}//if fopen

	rewind(in_file);

	fscanf(in_file,"%i",&MAX_NUM_OF_PTS);
	now_n=MAX_NUM_OF_PTS;
	fread(&help_ch, sizeof(char),1,in_file);

	printf("%i\n", MAX_NUM_OF_PTS);

	/* ***************************************************************************** */
	/*                                                                               */
	/*                             memory allocation                                 */
	/*                                                                               */
	/* ***************************************************************************** */


	lmbd=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));// lambda values
	phi=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));// phi values
	H=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));// depth
	RR=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));// frictions
	W1=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
	W2=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
	W3=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));// outside effect in three directions
	D_BC=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1)); //the right part in the boundary conditions
															//for vilosities or for elevation on the free surface
	//Unknown of the problem
	u=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
	v=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
	xi=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));

	// and the same on the priviouse time lavel and ajoint solution
	u_old=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
	v_old=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
	xi_old=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));

	u_new=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
	v_new=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
	xi_new=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));

	ind_pts=(int*)malloc(sizeof(int)*(MAX_NUM_OF_PTS+1));

	//Exact solution
	#if ind_test==1
		u_exact=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
		v_exact=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
		xi_exact=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
	#endif

	//Parameters for Jacoby iteration
	a1=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
	a3=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
	b1=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
	c1=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
	c2=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
	e1=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
	e2=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
	e3=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
	e0=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
	gamma1=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
	gamma2=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));

	//diagonal D for Jacoby iteration: U^(n+1)=U^(n)-D^(-1)(AU^(n)-R)
	diag_u=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
	diag_v=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
	diag_xi=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));

	//for compare of solutions
	#if ind_test==1
		dif_u=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
		dif_v=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
		dif_xi=(double*)malloc(sizeof(double)*(MAX_NUM_OF_PTS+1));
	#endif

	// initial filling
	fill_vector_by_value(H,0,now_n);
	fill_vector_by_value(RR,0,now_n);
	fill_vector_by_value(W1,0,now_n);
	fill_vector_by_value(W2,0,now_n);
	fill_vector_by_value(W3,0,now_n);
	fill_vector_by_value(D_BC,0,now_n);
	fill_vector_by_value(lmbd,0,now_n);
	fill_vector_by_value(phi,0,now_n);
	fill_vector_by_value(u,0,now_n);
	fill_vector_by_value(v,0,now_n);
	fill_vector_by_value(xi,0,now_n);
	fill_vector_by_value(u_old,0,now_n);
	fill_vector_by_value(v_old,0,now_n);
	fill_vector_by_value(xi_old,0,now_n);
	fill_vector_by_value(diag_u,0,now_n);
	fill_vector_by_value(diag_v,0,now_n);
	fill_vector_by_value(diag_xi,0,now_n);

	#if ind_test==1
		fill_vector_by_value(u_exact,0,now_n);
		fill_vector_by_value(v_exact,0,now_n);
		fill_vector_by_value(xi_exact,0,now_n);
	#endif


	/* ***************************************************************************** */
	/*                                                                               */
	/*                   the information about points is reading                     */
	/*                                                                               */
	/* ***************************************************************************** */

	//read data about points
		for (ii=1; ii<=now_n; ii++){
			fscanf(in_file, "%i%le%le%le",&hlp1,&lmbd[ii],&phi[ii],&H[ii]);
			#if ind_grad == 1
				lmbd[ii]=lmbd[ii]*PI_DIV_180;
				phi[ii]=phi[ii]*PI_DIV_180;//+half_PI;
			#endif
		}

	fclose(in_file);


	/* ***************************************************************************** */
	/*                                                                               */
	/*                               open the file                                   */
	/*        the information about number of triangle is reading                    */
	/*                                                                               */
	/* ***************************************************************************** */

	//text file open for read data about triangle
	if ((in_file=fopen(name_in2, "r"))==NULL)
	{
		printf("Error at opening of the file.\n");
		exit(1);
	}//if (open file)

	fscanf(in_file,"%i",&NUM_OF_TR);
	printf("%i \n", NUM_OF_TR);
//	help_ch=getchar();

	/* ***************************************************************************** */
	/*                                                                               */
	/*                             memory allocation                                 */
	/*                                                                               */
	/* ***************************************************************************** */

	DIM_MATR_TR=NUM_OF_TR+1;

	fread(&help_ch, sizeof(char),1,in_file);

	//  appearance of points to triangles
	tr=(int**)malloc(sizeof(int*)*(DIM_MATR_TR));
	if(!tr){ printf ("%s\n","error in y-malloc");exit(1);}

	for (ii=0; ii<=NUM_OF_TR; ii++){
		tr[ii]=(int*)malloc(sizeof(int)*(3));
		if(!tr[ii]){printf ("%s%u\n","error in x-malloc ",ii);exit(1);}
	}//for ii

	//  characteristic of side of triangle (1 is right angle)
	ind_tr=(int**)malloc(sizeof(int*)*(DIM_MATR_TR));
	if(!ind_tr){ printf ("%s\n","error in y-malloc");exit(1);}

	for (ii=0; ii<=NUM_OF_TR; ii++){
		ind_tr[ii]=(int*)malloc(sizeof(int)*(3));
		if(!ind_tr[ii]){ printf ("%s%u\n","error in x-malloc ",ii);exit(1);}
	}//for ii


	//  square of triangle multiplied by 1/3
	S=(double*)malloc(sizeof(double)*(DIM_MATR_TR));
	fill_vector_by_value(S,0,NUM_OF_TR);

	/* ***************************************************************************** */
	/*                                                                               */
	/*                 the information about triangle is reading                     */
	/*                                                                               */
	/* ***************************************************************************** */

	hlp1=0;
	for (ii=1; ii<=NUM_OF_TR; ii++){
		fscanf(in_file, "%i%i%i%i%i%i%i",
		&hlp1,&tr[ii][0],&tr[ii][1],&tr[ii][2],
		&ind_tr[ii][0],&ind_tr[ii][1],&ind_tr[ii][2]);
	}//for ii

	fclose(in_file);


	/* ******************************************************************************** */
	/*                                                                                  */
	/*                      fill up the square*1/3                                      */
	/*                                                                                  */
	/* ******************************************************************************** */

	for (ii=1; ii<=NUM_OF_TR; ii++)
		S[ii]=(lmbd[tr[ii][0]]*(phi[tr[ii][1]]-phi[tr[ii][2]])
			  +lmbd[tr[ii][1]]*(phi[tr[ii][2]]-phi[tr[ii][0]])
			  +lmbd[tr[ii][2]]*(phi[tr[ii][0]]-phi[tr[ii][1]]))/6;


	/* ******************************************************************************** */
	/*                                                                                  */
	/*                     initial data is calculated                                   */
	/*                                                                                  */
	/* ******************************************************************************** */


	#if ind_test==1 // with exact solution
		exact_solution(H,lmbd,phi,u,v,xi,0,now_n);
		exact_solution(H,lmbd,phi,u_exact,v_exact,xi_exact,0,now_n); // for comparison (also initial data)

		analyse_solution(u,v,xi,max,min,L_2_norm,phi,H,S,tr,max_num,min_num,NUM_OF_TR,now_n);
//		prn_result(lmbd,phi,u,v,xi,NULL,NULL,NULL,max,min,L_2_norm,max_num,min_num,
//			name_fix1,"txt",now_n,0,3,1,"****** FOR INITIAL DATA (EXACT SOLUTION) ******",
//			"N, lmbd, phi, u_0, v_0, xi_0",rank);

	#elif ind_test==2 && ind_problem==0 //on rectangle grid and direct problem is solved only
//		initial_xi_tst(xi,lmbd,phi,now_n); //for test on small grid 5X5
		def_xi_obs(xi,lmbd,phi,tr,ind_tr,xi,NUM_OF_TR);

	#elif ind_test==3 && ind_obs==0 // for Ohotskhoe sea and observation data is calculated by procedure
		initial_xi_okh(xi,lmbd,phi,now_n);

	#endif


	//print the general statistic
	sprintf(name,"%s_stat.txt",name_fix);
	//text file open for write data about points
	if ((out_file0=fopen(name, "w"))==NULL) {
		printf("Error at opening of the file.\n");
		exit(1);
	}//if (open file)

	fprintf(out_file0,"The parametrs of this numerical example are:\n\n");
	fprintf(out_file0,"the tests indicator (1 - with exact solution, 2 - on rectangle grid, 3 - for Ohotskhoe sea):\n %1i \n\n",
			ind_test);
	fprintf(out_file0,"the problem indicator (0 - direct problem will be only solved, 1 - direct and adjoint problem will be solved):\n %1i \n\n",
			ind_problem);

	#if ind_problem==1 && ind_adj_prn==1
		fprintf(out_file0,"detailed information about adjoint solution will be printed to special files and to file of statistics \n\n");
	#endif

	fprintf(out_file0,"the outer effect indicator (0 - =0, 1 - define in the W-def procedure):\n %1i \n\n",
			ind_W);
	fprintf(out_file0,"constant for frictions define:\n rf = %le \n\n",rf);
	fprintf(out_file0,"parameter in the boundary conditions:\n beta = %le \n\n",beta);
	fprintf(out_file0,"alpha = %le,    exactness in d iteration %le \n\n",alpha,exact_d);
	fprintf(out_file0,"exactness in Jacoby method\n %le \n\n", exact_jac);
	fprintf(out_file0,"the number of time step:\n NUMBER_OF_TIME = %i \n\n",NUMBER_OF_TIME);
	fprintf(out_file0,"the step by time, secunds:\n tau_fix = %le \n\n",tau_fix);
	fprintf(out_file0,"the number of points:\n %i \n\n",MAX_NUM_OF_PTS);
	fprintf(out_file0,"the number of triangles:\n %i \n\n\n",NUM_OF_TR);

	#if ind_test>1
		analyse_solution(u,v,xi,max,min,L_2_norm,phi,H,S,tr,max_num,min_num,NUM_OF_TR,now_n,LEFT_BORDER_OF_PTS,RIGHT_BORDER_OF_PTS,Num,size);
//		prn_analise(max,min,L_2_norm,max_num,min_num,"****** FOR INITIAL DATA (NUMERICAL SOLUTION) ******",out_file0);

	#elif ind_test==1
		cmp_solutions(u,v,xi,u_exact,v_exact,xi_exact,difference,dif_u,dif_v,dif_xi,L_2_norm,phi,H,S,tr,max_num,NUM_OF_TR,now_n);
//		prn_analise(difference,NULL,L_2_norm,max_num,NULL,
//			"****** FOR COMPARE EXACT SOLUTION AND INITIAL DATA ******",out_file0);
	#endif

	fflush(stdout);
	fflush(out_file0);


	/* **************************************************************************************** */
	/*                                                                                          */
	/* calculate the coefficients of matrix in discrete problem which are not depended of time  */
	/*                                                                                          */
	/* **************************************************************************************** */

	coef(H,b1,c1,c2,e0,gamma1,gamma2,phi,now_n);

	/* ***************************************************************************** */
	/*                                                                               */
	/*                  BEGIN TIME STEP FOR DIRECT PROBLEM                           */
	/*                    TO DETERMINE "OBSERVATION DATA"                            */
	/*                                                                               */
	/* ***************************************************************************** */

	kk=1;
//	while ((err_max>exact_solv)&&(kk<=NUMBER_OF_TIME))
	while (kk<=NUMBER_OF_TIME)
	{//begin while stable observation data

		tmp1=div(kk,s1);
		tmp2=div(kk,s2);
		tmp3=div(kk,s3);

		tt=kk*tau_fix;

		//prepare for right hand side
		copy_vect_to_vect(u,u_old,now_n);
		copy_vect_to_vect(v,v_old,now_n);
		copy_vect_to_vect(xi,xi_old,now_n);

		/* ******************************************************************************** */
		/*                                                                                  */
		/*                        frictions is calculated                                   */
		/*                                                                                  */
		/* ******************************************************************************** */

		def_friction(RR,H,lmbd,phi,u,v,now_n);

		/* ******************************************************************************** */
		/*                                                                                  */
		/*   calculate the W-parameters in discrete problem in tt time moment               */
		/*                                                                                  */
		/* ******************************************************************************** */

		#if ind_W==1
			W_def(H,lmbd,phi,W1,W2,W3,RR,tt,now_n);

		#endif

		/* ******************************************************************************** */
		/*                                                                                  */
		/* calculate the coefficients of matrix in discrete problem  in tt time moment      */
		/*                                                                                  */
		/* ******************************************************************************** */

		diag(H,RR,a1,a3,phi,now_n);

		right_hand_side(H,W1,W2,W3,e1,e2,e3,phi,now_n);

		/* ******************************************************************************** */
		/*                                                                                  */
		/*                        Fill up the diagonal in tt time moment                    */
		/*                                                                                  */
		/* ******************************************************************************** */

		fill_vector_by_value(diag_u,0,now_n);
		fill_vector_by_value(diag_v,0,now_n);
		fill_vector_by_value(diag_xi,0,now_n);

		diag_global(diag_u,diag_v,diag_xi,S,a1,a3,gamma1,gamma2,lmbd,phi,tr,ind_tr,NUM_OF_TR,out_file0);

		/* ******************************************************************************** */
		/*                                                                                  */
		/*                  Jacoby iterations for direct problem                            */
		/*                                                                                  */
		/* ******************************************************************************** */

		Jacoby(u,v,xi,u_old,v_old,xi_old,u_new,v_new,xi_new,diag_u,diag_v,diag_xi,
				a1,a3,b1,c1,c2,e1,e2,e3,e0,gamma1,gamma2,lmbd,phi,tr,ind_tr,0,S,
				D_BC,NULL,now_n,NUM_OF_TR,out_file0);

		// Далее проводится сравнение точного решения с полученным на данном шаге по времени. Разница (по норме) выводится в файл.
/*		#if ind_test == 1
			if (!tmp3.rem) fprintf(out_file0,"\n%s%d%s\n\n", " **************** time= ",kk," ***************");
			exact_solution(H,lmbd,phi,u_exact,v_exact,xi_exact,tt,now_n);
			cmp_solutions(u,v,xi,u_exact,v_exact,xi_exact,difference,dif_u,dif_v,dif_xi,L_2_norm,phi,H,S,tr,max_num,NUM_OF_TR,now_n);
			prn_analise(difference,NULL,L_2_norm,max_num,NULL,
										"****** FOR COMPARE EXACT AND NUMERICAL SOLUTIONS ******",out_file0);
		#endif
*/
		kk++;

	}

	// Далее проводится сравнение точного решения с полученным. Разница (по норме) выводится в файл.
	#if ind_test == 1
		if (!tmp3.rem) fprintf(out_file0,"\n%s%d%s\n\n", " **************** time= ",kk-1," ***************");
		exact_solution(H,lmbd,phi,u_exact,v_exact,xi_exact,tt,now_n);
		cmp_solutions(u,v,xi,u_exact,v_exact,xi_exact,difference,dif_u,dif_v,dif_xi,L_2_norm,phi,H,S,tr,max_num,NUM_OF_TR,now_n);
		prn_analise(difference,NULL,L_2_norm,max_num,NULL,
										"****** FOR COMPARE EXACT AND NUMERICAL SOLUTIONS ******",out_file0);
	#endif



	fclose(out_file0);

	free(D_BC); free(W1); free(W2); free(W3); free(RR); free(H); free(phi); free(lmbd);
	free(xi); free(v); free(u);
	free(xi_old); free(v_old); free(u_old);
	free(xi_new); free(v_new); free(u_new);

	free(a1); free(a3); free(b1); free(c1); free(c2); free(e1); free(e2); free(e3); free(e0);
	free(gamma1); free(gamma2);
	free(diag_xi); free(diag_v); free(diag_u);


	#if ind_test==1
		free(xi_exact); free(v_exact); free(u_exact);
		free(dif_xi); free(dif_v); free(dif_u);
	#endif

	for (ii=0; ii<=NUM_OF_TR; ii++) {
		free(tr[ii]); free(ind_tr[ii]);
	}

	free(tr); free(ind_tr);
	free(S);

	return 0;
}
