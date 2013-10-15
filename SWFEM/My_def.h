#define ind_test 1	// the tests indicator
					// 1 - with exact solution
					// 2 - on rectangle grid
					// 3 - for Ohotskhoe sea

#define ind_problem 0	// the tests indicator
						// 0 - direct problem is only solved
						// 1 - direct and adjoint problems are solved

#define ind_prn 0	// the printing of adjoint solution indicator
						// 0 - adjoint solution isn't printed
						// 1 - adjoint solution is printed

#define ind_W 1	// the source functions indicator
				// 0 - W1=W2=W3=0
				// 1 - W1, W2, W3 are defined in the function W_def

#define ind_obs 1	// 0 - observation data is calculated by procedure
					// 1 - observation data is calculated by direct problem

#define ind_d 1		// 1 - d define as constant
					// 2 - d define for simple grid with cut of angle (see function def_D_BC_fun !!!)
					// 3 - d define as sinus (see function def_D_BC_fun !!!)

#define ind_grad 1	// 0 - data for grid points is given in radian
					// 1 - data for grid points is given in grade

#define ind_diag 0	// 0 using all points
					// 1 using points exclusive of solid boundary neighborhood

#define ind_plot 0	// 0 don't out for gnuplot
					// 1 out for gnuplot

#define ind_rich 0// 0 don't out for Richardson
					// 1 out for Richardson

#define PI (double)(4.*atanl(1))
#define half_PI (double)(2.*atanl(1))
#define PI_DIV_180 (double)((4.*atanl(1))/180.)

#define rf (double)0.//2.60e-3 // constant for frictions define
#define beta (double)1. // parameter in the boundary conditions
#define alpha (double)1.e-3 // parameter before d^m in iteration for d
#define p (double)0.8 // parameter at gamma_opt
//#define gamma (double)0.4 // parameter at gamma_opt

//#define gamma (double)0.2 // parameter in in iteration for d

#define omega2 (double)2*omega

// The time parameters
#define NUMBER_OF_TIME (int)1// the number of time step
#define tau_fix (double)1.0 //the step by time is tau_fix secund

// The numerical methods parameters
#define exact_jac (double)1.e-10 // this is an exactness of Jacoby method now
#define exact_d (double)2.e-3 // this is an exactness for d determination !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define exact_solv (double)5.e-5 // this is an exactness for determination of steady-state solution

#define s1 (int)1 // every s1 iteration - to out to terminal
#define s2 (int)1 // every s2 iteration - to out to result file
#define s3 (int)1 // every s3 iteration - to out to statistic file
#define sm (int)1 // every sm d-iteration - out put to result file


/* ***************************************************************************** */
/*                                                                               */
/*                         Prptotypes of functions                               */
/*                                                                               */
/* ***************************************************************************** */
//service functions

//function fills vector by value
void fill_vector_by_value(double vector[],const double val,
						  const int now_n);
//copy vector to vector
void copy_vect_to_vect(double *vec,double *c_vec, const int now_n);

//Solver

//exact solution is calculated
void exact_solution(double *H, double *lmbd, double *phi,
					double *exact_u, double *exact_v, double *exact_xi,
					const double tt, const int now_n);
// initialization a deviation of ocean level from the unperturbed surface on the current
void initial_xi_okh(double *xi, double *lmbd, double *phi, const int now_n);
void initial_xi_tst(double *xi, double *lmbd, double *phi, const int now_n);
//xi which are observed is defined
void def_xi_obs(double *xi, double *lmbd, double *phi, int **tr, int **ind_tr,
				double *xi_obs, const int NUM_OF_TR);
//friction is calculated
void def_friction(double *RR, double *H, double *lmbd, double *phi,
				  double *u, double *v, const int now_n);
//W_1, W_2, W_3 is defined
void W_def(double *H, double *lmbd, double *phi,
		   double *W1, double *W2, double *W3, double *R,
		   const double tt, const int now_n);
//The coefficients of local matrix and right-hand side
//which are not depend on time in discrete problem (without diagonal)
void coef(double *H, double *b1, double *c1, double *c2, double *e0,
		  double *gamma1, double *gamma2, double *phi, const int now_n);
//The diagonal of local matrix in discrete problem
void diag(double *H, double *RR, double *a1, double *a3,
		  double *phi, const int now_n);
//The coefficients of local vector of right-hand side which are depend on time in discrete problem
void right_hand_side(double *H, double *W1, double *W2, double *W3,
		  double *e1, double *e2, double *e3, double *phi, const int now_n);


//The diagonal for Jacoby's iteration
void diag_global(double *diagu, double *diagv, double *diagxi,
			double *S, double *a1, double *a3, double *gamma1, double *gamma2,
			double *lmbd, double *phi, int **tr, int **ind_tr,
			const int num_tr, FILE *file_w);
//matrix A multiply by vector of unknowns minus right-hand side
//j.e residial
void mult_direct(double *u, double *u_new, double *v,
				 double *v_new, double *xi, double *xi_new,
				 double *u_prev, double *v_prev, double *xi_prev,
				 double *S, double *a1, double *a3,
				 double *b1, double *c1, double *c2,
				 double *e1, double *e2, double *e3, double *e0,
				 double *gamma1, double *gamma2,
				 double *lmbd, double *phi, double *D_BC,
				 int **tr, int **ind_tr, const int num_tr, FILE *file_w);
void mult_adjoint(double *u_new, double *v_new, double *xi_new,
				  double *u, double *v, double *xi,
				  double *u_prev, double *v_prev, double *xi_prev,
				  double *S, double *a1, double *a3,
				  double *b1, double *c1, double *c2, double *e0,
				  double *gamma1, double *gamma2,
				  double *lmbd, double *phi, double *D_hat,
				  int **tr, int **ind_tr, const int num_tr, FILE *file_w);
// Jacoby iteration
void Jacoby(double *u, double *v, double *xi,
			double *u_prev, double *v_prev, double *xi_prev,
			double *u_new, double *v_new, double *xi_new,
			double *diagu, double *diagv, double *diagxi,
			double *a1, double *a3, double *b1, double *c1, double *c2,
			double *e1, double *e2, double *e3, double *e0,
		    double *gamma1, double *gamma2, double *lmbd, double *phi,
		    int **tr, int **ind_tr, int ind_task,
			double *S, double *D_BC, double *D_hat,
			const int now_n, const int num_tr, FILE *file_w);
//analysis of solution
void analyse_solution(double *u, double *v, double *xi,
					  double *max, double *min, double *L_2_norm,
					  double *phi, double *H, double *S,
					  int **tr, int *max_num, int *min_num,
					  const int num_tr, const int now_n);
//uniform norm of vector ((u,v,xi)-(u_old,v_old,xi_old)) difference is calculated
void uniform_norm(double *u, double *v, double *xi, double *u_old, double *v_old, double *xi_old,
			 double *max, int *max_num, double *min, int *min_num, const int now_n);
//uniform norm of vector ((u,v,xi)-(u_old,v_old,xi_old)) difference exclusive of solid boundary is calculated
void be_uniform_norm(double *lmbd, double *phi, double *u, double *v, double *xi,
					 double *u_old, double *v_old, double *xi_old,
                     double *max, int *max_num, const int now_n);
//compare with exact solution
void cmp_solutions(double *u, double *v, double *xi, double *exact_u, double *exact_v, double *exact_xi,
				   double *difference, double *dif_u, double *dif_v, double *dif_xi, double *L_2_norm,
				   double *phi, double *H, double *S, int **tr, int *max_num,
				   const int num_tr, const int now_n);

void prn_result(double *lmbd, double *phi,
				double *vec1, double *vec2, double *vec3, double *vec4, double *vec5, double *vec6,
				double *max, double *min, double *L_2_norm, int *max_num, int *min_num,
				char *fix1, char *ext, const int num, const int n, const int m, const int pr,
				char *text,char *head);
void prn_analise(double *max, double *min, double *L_2_norm, int *max_num, int *min_num, char *text, FILE *file_w);
void prn_pic(double *lmbd, double *phi, double *vec1, double *vec2, double *vec3,
             int **tr, const int now_n, const int num_tr,
			 const int num_pic, const int num_t, const int iter, const int ind);
void prn_rich(double *lmbd, double *phi,
				double *vec1, double *vec2, double *vec3, double *vec4, double *vec5, double *vec6, double *vec7,
				char *fix1, char *ext, const int num, const int n, const int m);


