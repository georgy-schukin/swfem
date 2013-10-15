#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <math.h>

#include "My_def.h"

extern double radius,g,omega,tau,tau1;

//1D
//function fills vector by value
void fill_vector_by_value(double vector[],const double val,const int now_n)
{
	register int i;

	for (i=0; i<=now_n; i++)
		vector[i]=val;

}


//copy vector to vector
void copy_vect_to_vect(double *vec,double *c_vec, const int now_n)
{
	register int i;

	for (i=0; i<=now_n; i++)
		c_vec[i]=vec[i];
}


//exact solution is calculated
void exact_solution(double *H, double *lmbd, double *phi,
					double *exact_u, double *exact_v, double *exact_xi,
					const double tt, const int now_n)
{
	register int i;

	double lmbd0=0., lmbd1=PI/18., phi0=PI/2., phi1=PI/2.+PI/18.;
	double ex_k=4., ex_l=4.;
//	double T_x=(lmbd1-lmbd0)/(PI*ex_k),  T_y=(phi1-phi0)/(PI*ex_l);
	double T_x=1./72.,  T_y=1./72.;

	double t1,t11,t13,t17;
	double t2;
	double t4,t5,t6,t8;	

	t1 = 1000.0+tt;
	t2 = pow(t1,0.3333333333333333);
	t6 = 72.;
	t11 = 72.;
	t4 = 72.*72.;
	t5 = 72.*72.;

	for (i=1; i<=now_n; i++){
		t8 = sin((lmbd[i]-lmbd0)*t6);
		t13 = cos((phi[i]-phi0)*t11);
		exact_u[i]=100000.0*t8*t13*t6/3.0/t2/t1/H[i];

		t8 = cos((lmbd[i]-lmbd0)*t6);
		t13 = sin((phi[i]-phi0)*t11);
		t17 = sin(phi[i]);
		exact_v[i]=100000.0*t8*t13*t11/3.0/t2/t1/H[i]/t17;

		t13 = cos((lmbd[i]-lmbd0)*t6);
		t8 = cos((phi[i]-phi0)*t11);
		exact_xi[i]=-100000.0*(t4+t5)*t13*t8/t2/radius/t17;
	}	
}




// initialization deviation of ocean level from the unperturbed surface on the current
void initial_xi_okh(double *xi, double *lmbd, double *phi, const int now_n)
{
	register int i;
	int i0=14575;
	double lmbd0=2.602285915, phi0=2.497566160;
	double A=2.,D=0.006;

	for (i=1; i<=now_n; i++)
		xi[i]=A*exp((-(lmbd[i]-lmbd[i0])*(lmbd[i]-lmbd[i0])-(phi[i]-phi[i0])*(phi[i]-phi[i0]))/4./D/D);
}

// initialization deviation of ocean level from the unperturbed surface on the current
void initial_xi_tst(double *xi, double *lmbd, double *phi, const int now_n)
{
	register int i;
	int i0=5;
	double A=2.,D=0.006;

	for (i=1; i<=now_n; i++)
		xi[i]=A*exp((-(lmbd[i]-lmbd[i0])*(lmbd[i]-lmbd[i0])-(phi[i]-phi[i0])*(phi[i]-phi[i0]))/4./D/D);

//	xi[3]=2;
}

//xi which are observed is defined
void def_xi_obs(double *xi, double *lmbd, double *phi, int **tr, int **ind_tr,
				double *xi_obs, const int NUM_OF_TR)
{
	double A=10.,D=400;
#if ind_test==2 && ind_problem==1
	register int i;
	// sin on the left boundary of rectangle, grid 51 X 51
	for (i=1; i<=NUM_OF_TR; i++){
		if (ind_tr[i][0]<=-7) {
			xi_obs[tr[i][0]]=A*sin(D*phi[tr[i][0]]);
			xi_obs[tr[i][1]]=A*sin(D*phi[tr[i][1]]);
		}
		if (ind_tr[i][1]<=-7) {
			xi_obs[tr[i][1]]=A*sin(D*phi[tr[i][1]]);
			xi_obs[tr[i][2]]=A*sin(D*phi[tr[i][2]]);
		}
		if (ind_tr[i][2]<=-7) {
			xi_obs[tr[i][2]]=A*sin(D*phi[tr[i][2]]);
			xi_obs[tr[i][0]]=A*sin(D*phi[tr[i][0]]);
		}
	}

#elif ind_test==2 && ind_problem==0
	//for simple grid 5 X 5
	xi[6]=2.; xi[16]=-2.; xi_obs[6]=2.; xi_obs[16]=-2.;
#endif

}

//friction is calculated
void def_friction(double *RR, double *H, double *lmbd, double *phi, double *u, double *v, const int now_n)
{
	register int i;
	for (i=1; i<=now_n; i++)
		RR[i]=1.e-5;
//		RR[i]=rf*sqrt(u[i]*u[i]+v[i]*v[i])/H[i];
}


//W_1, W_2, W_3 is defined FROM MAPLE
void W_def(double *H, double *lmbd, double *phi,
		   double *W1, double *W2, double *W3, double *R,
		   const double tt, const int now_n)
{
	register int i;
	double lmbd0=0., lmbd1=PI/18., phi0=half_PI , phi1=half_PI+PI/18.;
	double ex_k=4., ex_l=4.;
	double T_x=1./72.,  T_y=1./72.;
//	double T_x=(lmbd1-lmbd0)/(PI*ex_k),  T_y=(phi1-phi0)/(PI*ex_l);

	double t1,t12,t13,t14,t15,t16,t17,t18,t19;
	double t2,t20,t23,t24,t26,t27,t28,t29;
	double t3,t36,t38,t42,t44,t47,t49;
	double t7;
	double t8;
	double t9;
	//FILE* fff;
	double z1,z2,z3,z4;

	t1 = 1000.0+tt;
	t2 = t1*t1;
	t3 = pow(t1,0.3333333333333333);
	t7 = 1/T_x;
	t12 = 1/T_y;


    for (i=1; i<=now_n; i++) {
		t8 = (lmbd[i]-lmbd0)*t7;
	    t9 = sin(t8);
		t13 = (phi[i]-phi0)*t12;
		t14 = cos(t13);
		t15 = 1/H[i];
		t17 = t14*t15*t7;
		t20 = cos(phi[i]);
		t23 = 1/t3/t1;
		t24 = cos(t8);
		t27 = sin(t13);
		t29 = sin(phi[i]);
		t36 = T_x*T_x;
		t38 = T_y*T_y;
		t44 = radius*radius;
		t47 = t29*t29;
		W1[i]=-400000.0*t9*t17/9.0/t3/t2
			  +200000.0*omega*t20*t23*t24*t27*t15*t12/3.0/t29
			  -100000.0*g*(1/t36+1/t38)*t9*t7*t14/t3/t44/t47
			  +100000.0*R[i]*t23*t9*t17/3.0;
//		printf("%14.6le\n", W1[i]);
	}


	for (i=1; i<=now_n; i++) {
		t8 = (lmbd[i]-lmbd0)*t7;
		t9 = cos(t8);
		t13 = (phi[i]-phi0)*t12;
	    t14 = sin(t13);
		t16 = 1/H[i];
		t18 = sin(phi[i]);
		t19 = 1/t18;
		t23 = cos(phi[i]);
		t26 = 1/t3/t1;
		t28 = sin(t8);
		t29 = cos(t13);
		t36 = T_x*T_x;
		t38 = T_y*T_y;
		t42 = 1/t3*(1/t36+1/t38)*t9;
		t44 = 1/radius;
		t49 = t18*t18;
		W2[i]=-400000.0*t9*t14*t16*t12*t19/9.0/t3/t2
			  -200000.0*omega*t23*t26*t28*t29*t16*t7/3.0
			  -100000.0*g*t44*(t42*t14*t12*t44*t19+t42*t29*t44/t49*t23)
			  +100000.0/3.0*R[i]*t26*t9*t14*t16*t12*t19;


//		printf("%14.6le * %14.6le * %14.6le * %14.6le * %14.6le\n", (-400000.0*t9*t14*t16*t12*t19/9.0/t3/t2),
//			(-200000.0*omega*t23*t26*t28*t29*t16*t7/3.0),
//		    (-100000.0*g*t44*(t42*t14*t12*t44*t19+t42*t29*t44/t49*t23)),
//			(100000.0/3.0*R[i]*t26*t9*t14*t16*t12*t19),W2[i]);

		W3[i]=0.;
	}
}



//The coefficients of local matrix and right-hand side
//which are not depend on time in discrete problem (without diagonal)
void coef(double *H, double *b1, double *c1, double *c2, double *e0,
		  double *gamma1, double *gamma2, double *phi, const int now_n)
{
/* ***************************************************************** */
/*         Fill up some parametr of numerical problem                */
/*         b1(lmbd,phi)=-H*R*R*sin(phi)*2*omega*cos(phi)             */
/*         b2(lmbd,phi)=b1(lmbd,phi)                                 */
/*         b3(lmbd,phi)=H*R*g                                        */
/*         c1(lmbd,phi)=b3(lmbd,phi)                                 */
/*         c2(lmbd,phi)=R*H*g*sin(phi)                               */
/*         c3(lmbd,phi)=c2(lmbd,phi)                                 */
/*         e0(lmbd,phi)=H*R*R*sin(phi)/tau                           */
/*         e4(lmbd,phi)=a3(lmbd,phi)                                 */
/*         gamma1(lmbd,phi)=beta*g*sqrt(g*H)                         */
/*         gamma2(lmbd,phi)=g*sqrt(g*H)                              */
/* ***************************************************************** */

	register int i;
	double sin_phi, r_sin, r_h_sin;

	b1[0]=0.; c1[0]=0.; c2[0]=0.;
	e0[0]=0.; gamma1[0]=0.; gamma2[0]=0.;

	for (i=1; i<=now_n; i++){

		sin_phi=sin(phi[i]);
		r_sin=radius*sin_phi;
		r_h_sin=r_sin*H[i];

		b1[i]=-r_h_sin*omega2*cos(phi[i]);
		c1[i]=H[i]*g;
		c2[i]=H[i]*sin_phi*g;
		e0[i]=r_h_sin*tau1;
		gamma2[i]=g*sqrt(g*H[i]);
		gamma1[i]=gamma2[i]*beta;
	}

}

//The diagonal of local matrix in discrete problem
void diag(double *H, double *RR, double *a1, double *a3,
		  double *phi, const int now_n)
{
/* ***************************************************************** */
/*         Fill up some parametr of numerical problem                */
/*         a1(lmbd,phi)=H*R*R*sin(phi)*(1/tau+RR)                    */
/*         a2(lmbd,phi)=a1(lmbd,phi)                                 */
/*         a3(lmbd,phi)=R*R*sin(phi)*g/tau                           */
/* ***************************************************************** */

	register int i;
	double sin_phi, r_sin, r_h_sin, bracket;

	a1[0]=0.; a3[0]=0.;

	for (i=1; i<=now_n; i++){

		sin_phi=sin(phi[i]);
		r_sin=radius*sin_phi;
		r_h_sin=r_sin*H[i];
		bracket=tau1+RR[i];

		a1[i]=r_h_sin*bracket;
		a3[i]=r_sin*g*tau1;

	}

}

//The coefficients of local vector of right-hand side which are depend on time in discrete problem
void right_hand_side(double *H, double *W1, double *W2, double *W3,
		  double *e1, double *e2, double *e3, double *phi, const int now_n)
{
/* ***************************************************************** */
/*         Fill up some parametr of numerical problem                */
/*         e1(lmbd,phi)=H*R*R*sin(phi)*W1                            */
/*         e2(lmbd,phi)=H*R*R*sin(phi)*W2                            */
/*         e3(lmbd,phi)=R*R*g*sin(phi)*W3                            */
/*         e4(lmbd,phi)=a3(lmbd,phi)                                 */
/* ***************************************************************** */

	register int i;
	double sin_phi, r_sin, r_h_sin;

	e1[0]=0.; e2[0]=0.; e3[0]=0.;

	for (i=1; i<=now_n; i++){

		sin_phi=sin(phi[i]);
		r_sin=radius*sin_phi;
		r_h_sin=r_sin*H[i];

		e1[i]=r_h_sin*W1[i];
		e2[i]=r_h_sin*W2[i];
		e3[i]=r_sin*g*W3[i];
	}

}


//The diagonal for Jacoby's iteration
void diag_global(double *diagu, double *diagv, double *diagxi,
			double *S, double *a1, double *a3, double *gamma1, double *gamma2,
			double *lmbd, double *phi, int **tr, int **ind_tr, const int num_tr, FILE *file_w)
{
	register int j,i,k;
	double hlp1,hlp2,hlp3;

//access on triangle
//
//   (1)   -----   (3)         phi /\
//	      |    /  	  	           |
//	      |  /                     |
//   (2)  |/                        ----> lambda
//


	for (i=1; i<=num_tr; i++){ // the triangulation cycle
		for (j=0; j<=2; j++){ // the points in triangle cycle
//The first equation
			diagu[tr[i][j]]=diagu[tr[i][j]]+a1[tr[i][j]]*S[i];
//The second equation
			diagv[tr[i][j]]=diagv[tr[i][j]]+a1[tr[i][j]]*S[i];
//The third equation
			diagxi[tr[i][j]]=diagxi[tr[i][j]]+a3[tr[i][j]]*S[i];
			k=(j+1)%3;
			if ((ind_tr[i][j]==-1) || (ind_tr[i][j]==-7))
			{
				hlp1=phi[tr[i][k]]-phi[tr[i][j]];
				hlp2=(lmbd[tr[i][k]]-lmbd[tr[i][j]])*sin(phi[tr[i][j]]);
				hlp3=fabsl(sqrtl(hlp1*hlp1+hlp2*hlp2))/2;

				diagxi[tr[i][j]]=diagxi[tr[i][j]]+hlp3*gamma1[tr[i][j]];
			}

		}

	}

}


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
				 int **tr, int **ind_tr, const int num_tr, FILE *file_w)

{
	register int j,i,k;
	double sum1=0, sum2=0, sum3=0;
	double hlp1,hlp2,hlp3,hlp4,hlp5;


//access on triangle
//
//   (1)   -----   (3)         phi /\
//	      |    /  	  	           |
//	      |  /                     |
//   (2)  |/                        ----> lambda
//

	for (i=1; i<=num_tr; i++){ // the triangulation cycle
		for (j=0; j<=2; j++){ // the points in triangle cycle
//The first equation
			u_new[tr[i][j]]=u_new[tr[i][j]]
					+u[tr[i][j]]*a1[tr[i][j]]*S[i]
					-v[tr[i][j]]*b1[tr[i][j]]*S[i]
					-((phi[tr[i][1]]-phi[tr[i][2]])*xi[tr[i][0]]
					+ (phi[tr[i][2]]-phi[tr[i][0]])*xi[tr[i][1]] //!
					+ (phi[tr[i][0]]-phi[tr[i][1]])*xi[tr[i][2]])*c1[tr[i][j]]/6
					-S[i]*(e1[tr[i][j]]+u_prev[tr[i][j]]*e0[tr[i][j]]);

//The second equation
			sum1=(lmbd[tr[i][2]]-lmbd[tr[i][1]])*xi[tr[i][0]]
					+(lmbd[tr[i][0]]-lmbd[tr[i][2]])*xi[tr[i][1]]
					+(lmbd[tr[i][1]]-lmbd[tr[i][0]])*xi[tr[i][2]];

			v_new[tr[i][j]]=v_new[tr[i][j]]
				+v[tr[i][j]]*a1[tr[i][j]]*S[i]
				+u[tr[i][j]]*b1[tr[i][j]]*S[i]
				-sum1*c2[tr[i][j]]/6
				-S[i]*(e2[tr[i][j]]+v_prev[tr[i][j]]*e0[tr[i][j]]);
		}

//The third equation
		sum2=(c1[tr[i][0]]*u[tr[i][0]]+c1[tr[i][1]]*u[tr[i][1]]+c1[tr[i][2]]*u[tr[i][2]])/6;
		sum3=(c2[tr[i][0]]*v[tr[i][0]]+c2[tr[i][1]]*v[tr[i][1]]+c2[tr[i][2]]*v[tr[i][2]])/6;

			xi_new[tr[i][0]]=xi_new[tr[i][0]]
				+xi[tr[i][0]]*a3[tr[i][0]]*S[i]
				+sum2*(phi[tr[i][1]]-phi[tr[i][2]])
				+sum3*(lmbd[tr[i][2]]-lmbd[tr[i][1]])
				-S[i]*(e3[tr[i][0]]+xi_prev[tr[i][0]]*a3[tr[i][0]]);

			xi_new[tr[i][1]]=xi_new[tr[i][1]]
				+xi[tr[i][1]]*a3[tr[i][1]]*S[i]
				+sum2*(phi[tr[i][2]]-phi[tr[i][0]])
				+sum3*(lmbd[tr[i][0]]-lmbd[tr[i][2]])
				-S[i]*(e3[tr[i][1]]+xi_prev[tr[i][1]]*a3[tr[i][1]]);

			xi_new[tr[i][2]]=xi_new[tr[i][2]]
				+xi[tr[i][2]]*a3[tr[i][2]]*S[i]
				+sum2*(phi[tr[i][0]]-phi[tr[i][1]])
				+sum3*(lmbd[tr[i][1]]-lmbd[tr[i][0]])
				-S[i]*(e3[tr[i][2]]+xi_prev[tr[i][2]]*a3[tr[i][2]]);

			for (j=0; j<=2; j++){ // the side of triangle cycle
				k=(j+1)%3;
				if ((ind_tr[i][j]==-1) || (ind_tr[i][j]==-7))
				{
					hlp1=phi[tr[i][k]]-phi[tr[i][j]];
					hlp2=(lmbd[tr[i][k]]-lmbd[tr[i][j]])*sin(phi[tr[i][j]]);
					hlp3=fabsl(sqrtl(hlp1*hlp1+hlp2*hlp2))/2;
					hlp4=(lmbd[tr[i][k]]-lmbd[tr[i][j]])*sin(phi[tr[i][k]]);
					hlp5=fabsl(sqrtl(hlp1*hlp1+hlp4*hlp4))/2;

					xi_new[tr[i][j]]=xi_new[tr[i][j]]
							+xi[tr[i][j]]*hlp3*gamma1[tr[i][j]]
							-hlp3*D_BC[tr[i][j]]*gamma2[tr[i][j]];

					xi_new[tr[i][k]]=xi_new[tr[i][k]]
							+xi[tr[i][k]]*hlp5*gamma1[tr[i][k]]
							-hlp5*D_BC[tr[i][k]]*gamma2[tr[i][k]];
				}

			}

	}
}


//matrix A multiply by vector of unknowns minus right-hand side
//j.e residial
void mult_adjoint(double *u_new, double *v_new, double *xi_new,
				  double *u, double *v, double *xi,
				  double *u_prev, double *v_prev, double *xi_prev,
				  double *S, double *a1, double *a3,
				  double *b1, double *c1, double *c2, double *e0,
				  double *gamma1, double *gamma2,
				  double *lmbd, double *phi, double *D_hat,
				  int **tr, int **ind_tr, const int num_tr, FILE *file_w)

{
	register int j,i,k;
	double sum1=0, sum2=0, sum3=0;
	double hlp1,hlp2,hlp3,hlp4,hlp5;


//access on triangle
//
//   (1)   -----   (3)         phi /\
//	      |    /  	  	           |
//	      |  /                     |
//   (2)  |/                        ----> lambda
//

	for (i=1; i<=num_tr; i++){ // the triangulation cycle
		for (j=0; j<=2; j++){ // the points in triangle cycle
//The first equation
			u_new[tr[i][j]]=u_new[tr[i][j]]
					+u[tr[i][j]]*a1[tr[i][j]]*S[i]
					+v[tr[i][j]]*b1[tr[i][j]]*S[i]
					+((phi[tr[i][1]]-phi[tr[i][2]])*xi[tr[i][0]]
					+ (phi[tr[i][2]]-phi[tr[i][0]])*xi[tr[i][1]] //!
					+ (phi[tr[i][0]]-phi[tr[i][1]])*xi[tr[i][2]])*c1[tr[i][j]]/6
					-S[i]*u_prev[tr[i][j]]*e0[tr[i][j]];//!

//The second equation
			sum1=(lmbd[tr[i][2]]-lmbd[tr[i][1]])*xi[tr[i][0]]
					+(lmbd[tr[i][0]]-lmbd[tr[i][2]])*xi[tr[i][1]]
					+(lmbd[tr[i][1]]-lmbd[tr[i][0]])*xi[tr[i][2]];

			v_new[tr[i][j]]=v_new[tr[i][j]]
				+v[tr[i][j]]*a1[tr[i][j]]*S[i]
				-u[tr[i][j]]*b1[tr[i][j]]*S[i]
				+sum1*c2[tr[i][j]]/6
				-S[i]*v_prev[tr[i][j]]*e0[tr[i][j]];//!
		}

//The third equation
		sum2=(c1[tr[i][0]]*u[tr[i][0]]+c1[tr[i][1]]*u[tr[i][1]]+c1[tr[i][2]]*u[tr[i][2]])/6;
		sum3=(c2[tr[i][0]]*v[tr[i][0]]+c2[tr[i][1]]*v[tr[i][1]]+c2[tr[i][2]]*v[tr[i][2]])/6;

		xi_new[tr[i][0]]=xi_new[tr[i][0]]
			+xi[tr[i][0]]*a3[tr[i][0]]*S[i]
			-sum2*(phi[tr[i][1]]-phi[tr[i][2]])
			-sum3*(lmbd[tr[i][2]]-lmbd[tr[i][1]])
			-S[i]*xi_prev[tr[i][0]]*a3[tr[i][0]];//!

		xi_new[tr[i][1]]=xi_new[tr[i][1]]
			+xi[tr[i][1]]*a3[tr[i][1]]*S[i]
			-sum2*(phi[tr[i][2]]-phi[tr[i][0]])
			-sum3*(lmbd[tr[i][0]]-lmbd[tr[i][2]])
			-S[i]*xi_prev[tr[i][1]]*a3[tr[i][1]];//!

		xi_new[tr[i][2]]=xi_new[tr[i][2]]
			+xi[tr[i][2]]*a3[tr[i][2]]*S[i]
			-sum2*(phi[tr[i][0]]-phi[tr[i][1]])
			-sum3*(lmbd[tr[i][1]]-lmbd[tr[i][0]])
			-S[i]*xi_prev[tr[i][2]]*a3[tr[i][2]];//!

		for (j=0; j<=2; j++){ // the side of triangle cycle
			k=(j+1)%3;
			if ((ind_tr[i][j]==-1) || (ind_tr[i][j]==-7))
			{
				hlp1=phi[tr[i][k]]-phi[tr[i][j]];
				hlp2=(lmbd[tr[i][k]]-lmbd[tr[i][j]])*sin(phi[tr[i][j]]);
				hlp3=fabsl(sqrtl(hlp1*hlp1+hlp2*hlp2))/2;
				hlp4=(lmbd[tr[i][k]]-lmbd[tr[i][j]])*sin(phi[tr[i][k]]);
				hlp5=fabsl(sqrtl(hlp1*hlp1+hlp4*hlp4))/2;
			}

			if (ind_tr[i][j]==-1)
			{
				xi_new[tr[i][j]]=xi_new[tr[i][j]]
						+xi[tr[i][j]]*hlp3*gamma1[tr[i][j]];

				xi_new[tr[i][k]]=xi_new[tr[i][k]]
						+xi[tr[i][k]]*hlp5*gamma1[tr[i][k]];
			}

			if (ind_tr[i][j]==-7)
			{
				xi_new[tr[i][j]]=xi_new[tr[i][j]]
						+xi[tr[i][j]]*hlp3*gamma1[tr[i][j]]
						-hlp3*D_hat[tr[i][j]]*gamma2[tr[i][j]];

				xi_new[tr[i][k]]=xi_new[tr[i][k]]
						+xi[tr[i][k]]*hlp5*gamma1[tr[i][k]]
						-hlp5*D_hat[tr[i][k]]*gamma2[tr[i][k]];
			}

		}

	}
}




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
			const int now_n, const int num_tr, FILE *file_w)
{
	register int i,num=0;
	double err,err_max=1,residial,residial_max;
	//double *ptr;
	//FILE* fff;
//	char help_ch;


	while (err_max>exact_jac) {
		num=num+1; err=0; err_max=0;
		residial_max=0; residial=0;

		fill_vector_by_value(u_new,0.,now_n);
		fill_vector_by_value(v_new,0.,now_n);
		fill_vector_by_value(xi_new,0.,now_n);

		if (ind_task == 0) { // using FEM residual is calculated
			mult_direct(u,u_new,v,v_new,xi,xi_new,u_prev,v_prev,xi_prev,S,a1,a3,b1,c1,c2,e1,e2,e3,e0,gamma1,gamma2,
				lmbd,phi,D_BC,tr,ind_tr,num_tr,file_w);
		}
		else {
			mult_adjoint(u_new,v_new,xi_new,u,v,xi,u_prev,v_prev,xi_prev,S,a1,a3,b1,c1,c2,e0,gamma1,gamma2,
				lmbd,phi,D_hat,tr,ind_tr,num_tr,file_w);
		}			

		for (i=1; i<=now_n; i++){
			if (fabs(u_new[i])>fabs(residial_max)) residial_max=fabs(u_new[i]);
			residial=u_new[i]/diagu[i];
			u_new[i]=u[i]-residial;
			err=fabsl(u_new[i]-u[i]);
			if (err>err_max) err_max=err;

			if (fabs(v_new[i])>fabs(residial_max)) residial_max=fabs(v_new[i]);
			residial=v_new[i]/diagv[i];
			v_new[i]=v[i]-residial;
			err=fabsl(v_new[i]-v[i]);
			if (err>err_max) err_max=err;

			if (fabs(xi_new[i])>fabs(residial_max)) residial_max=fabs(xi_new[i]);
			residial=xi_new[i]/diagxi[i];
			xi_new[i]=xi[i]-residial;
			err=fabsl(xi_new[i]-xi[i]);
			if (err>err_max) err_max=err;
		}		

		copy_vect_to_vect(u_new,u,now_n);
		copy_vect_to_vect(v_new,v,now_n);
		copy_vect_to_vect(xi_new,xi,now_n);

		printf("%e\n", err_max);
	}

}


//analysis of solution
void analyse_solution(double *u, double *v, double *xi,
					  double *max, double *min, double *L_2_norm,
					  double *phi, double *H, double *S,
					  int **tr, int *max_num, int *min_num,
					  const int num_tr, const int now_n)
{

	register int i,j;
	double l_2_u,l_2_v,l_2_xi,l_2_all,
		hlp_u,hlp_v,hlp_xi,hlp_all;

	max[1]=u[1];  min[1]=u[1];
	max[2]=v[1];  min[2]=v[1];
	max[3]=xi[1]; min[3]=xi[1];
	max[0]=0;  min[0]=0;

	for (i=0; i<4; i++) {
		L_2_norm[i]=0;
		max_num[i]=1; min_num[i]=1;
	}

	for (i=1; i<=now_n; i++) {

		if (u[i]>max[1]) {max[1]=u[i]; max_num[1]=i;}
		if (u[i]<min[1]) {min[1]=u[i]; min_num[1]=i;}
		if (v[i]>max[2]) {max[2]=v[i]; max_num[2]=i;}
		if (v[i]<min[2]) {min[2]=v[i]; min_num[2]=i;}
		if (xi[i]>max[3]) {max[3]=xi[i]; max_num[3]=i;}
		if (xi[i]<min[3]) {min[3]=xi[i]; min_num[3]=i;}
	}

	for (i=1; i<=num_tr; i++){ // the triangulation cycle
		l_2_all=0; l_2_u=0; l_2_v=0; l_2_xi=0;
		for (j=0; j<=2; j++) {// the points in triangle cycle

			hlp_u=u[tr[i][j]]*u[tr[i][j]];
			hlp_v=v[tr[i][j]]*v[tr[i][j]];
			hlp_xi=xi[tr[i][j]]*xi[tr[i][j]];

			hlp_all=H[tr[i][j]]*(hlp_u+hlp_v)+g*hlp_xi;

			l_2_u=l_2_u+sin(phi[tr[i][j]])*H[tr[i][j]]*hlp_u;
			l_2_v=l_2_v+sin(phi[tr[i][j]])*H[tr[i][j]]*hlp_v;
			l_2_xi=l_2_xi+sin(phi[tr[i][j]])*g*hlp_xi;

			l_2_all=l_2_all+sin(phi[tr[i][j]])*hlp_all;
		}
		l_2_all=l_2_all*S[i];

		l_2_u=l_2_u*S[i];
		l_2_v=l_2_v*S[i];
		l_2_xi=l_2_xi*S[i];

		L_2_norm[0]=L_2_norm[0]+l_2_all;

		L_2_norm[1]=L_2_norm[1]+l_2_u;
		L_2_norm[2]=L_2_norm[2]+l_2_v;
		L_2_norm[3]=L_2_norm[3]+l_2_xi;
	}
	L_2_norm[0]=radius*sqrt(L_2_norm[0]);
	L_2_norm[1]=radius*sqrt(L_2_norm[1]);
	L_2_norm[2]=radius*sqrt(L_2_norm[2]);
	L_2_norm[3]=radius*sqrt(L_2_norm[3]);
}



//uniform norm of vector ((u,v,xi)-(u_old,v_old,xi_old)) difference is calculated
void uniform_norm(double *u, double *v, double *xi, double *u_old, double *v_old, double *xi_old,
			 double *max, int *max_num, double *min, int *min_num, const int now_n)
{
	register int i;
	double err;

	max[1]=fabsl(u[1]-u_old[1]);  min[1]=fabsl(u[1]-u_old[1]);
	max[2]=fabsl(v[1]-v_old[1]);  min[2]=fabsl(v[1]-v_old[1]);
	max[3]=fabsl(xi[1]-xi_old[1]);  min[3]=fabsl(xi[1]-xi_old[1]);
	max[0]=max[1];  min[0]=min[1];

	for (i=0; i<4; i++) {max_num[i]=1; min_num[i]=1;}

	for (i=1; i<=now_n; i++) {

		err=fabsl(u[i]-u_old[i]);
		if (err>max[1]) {max[1]=err; max_num[1]=i;}
		if (err<min[1]) {min[1]=err; min_num[1]=i;}
		if (err>max[0]) {max[0]=err; max_num[0]=i;}
		if (err<min[0]) {min[0]=err; min_num[0]=i;}

		err=fabsl(v[i]-v_old[i]);
		if (err>max[2]) {max[2]=err; max_num[2]=i;}
		if (err<min[2]) {min[2]=err; min_num[2]=i;}
		if (err>max[0]) {max[0]=err; max_num[0]=i;}
		if (err<min[0]) {min[0]=err; min_num[0]=i;}

		err=fabsl(xi[i]-xi_old[i]);
		if (err>max[3]) {max[3]=err; max_num[3]=i;}
		if (err<min[3]) {min[3]=err; min_num[3]=i;}
		if (err>max[0]) {max[0]=err; max_num[0]=i;}
		if (err<min[0]) {min[0]=err; min_num[0]=i;}
	}

}

//uniform norm of vector ((u,v,xi)-(u_old,v_old,xi_old)) difference exclusive of solid boundary is calculated
void be_uniform_norm(double *lmbd, double *phi, double *u, double *v, double *xi,
					 double *u_old, double *v_old, double *xi_old,
                     double *max, int *max_num, const int now_n)
{
	register int i;
	double err;
	double k=0.771812080134228,
		b=42.500000006,
		lmbd_0=146.6,
		phi_0=42.500000006;

	max[1]=fabsl(u[1]-u_old[1]);
	max[2]=fabsl(v[1]-v_old[1]);
	max[3]=fabsl(xi[1]-xi_old[1]);
	max[0]=max[1];

	for (i=0; i<4; i++) max_num[i]=1;

	for (i=1; i<=now_n; i++) {
		if (k*(lmbd[i]-lmbd_0)+b-phi[i]>0){
            err=fabsl(u[i]-u_old[i]);
			if (err>max[1]) {max[1]=err; max_num[1]=i;}
			if (err>max[0]) {max[0]=err; max_num[0]=i;}

			err=fabsl(v[i]-v_old[i]);
			if (err>max[2]) {max[2]=err; max_num[2]=i;}
			if (err>max[0]) {max[0]=err; max_num[0]=i;}

			err=fabsl(xi[i]-xi_old[i]);
			if (err>max[3]) {max[3]=err; max_num[3]=i;}
			if (err>max[0]) {max[0]=err; max_num[0]=i;}
		}
	}

}


//compare with exact solution
void cmp_solutions(double *u, double *v, double *xi, double *exact_u, double *exact_v, double *exact_xi,
				   double *difference, double *dif_u, double *dif_v, double *dif_xi, double *L_2_norm,
				   double *phi, double *H, double *S, int **tr, int *max_num,
				   const int num_tr, const int now_n)
{
	register int i,j;
	double dif,l_2_u,l_2_v,l_2_xi,l_2_all,
		hlp_u,hlp_v,hlp_xi,hlp_all;

	for (i=0; i<4; i++) {
		difference[i]=0;
		L_2_norm[i]=0;
		max_num[i]=0;
	}

	for (i=1; i<=now_n; i++) {
		dif=fabs(u[i]-exact_u[i]);
		if (dif>difference[1]) {
			difference[1]=dif;
			max_num[1]=i;
		}
		if (dif>difference[0]) {
			difference[0]=dif;
			max_num[0]=i;
		}
		dif_u[i]=dif;

		dif=fabs(v[i]-exact_v[i]);
		if (dif>difference[2]) {
			difference[2]=dif;
			max_num[2]=i;
		}
		if (dif>difference[0]) {
			difference[0]=dif;
			max_num[0]=i;
		}
		dif_v[i]=dif;

		dif=fabs(xi[i]-exact_xi[i]);
		if (dif>difference[3]) {
			difference[3]=dif;
			max_num[3]=i;
		}
		if (dif>difference[0]) {
			difference[0]=dif;
			max_num[0]=i;
		}
		dif_xi[i]=dif;
	}

	for (i=1; i<=num_tr; i++){ // the triangulation cycle
		l_2_all=0; l_2_u=0; l_2_v=0; l_2_xi=0;
		for (j=0; j<=2; j++) {// the points in triangle cycle

			hlp_u=(u[tr[i][j]]-exact_u[tr[i][j]])*(u[tr[i][j]]-exact_u[tr[i][j]]);
			hlp_v=(v[tr[i][j]]-exact_v[tr[i][j]])*(v[tr[i][j]]-exact_v[tr[i][j]]);
			hlp_xi=(xi[tr[i][j]]-exact_xi[tr[i][j]])*(xi[tr[i][j]]-exact_xi[tr[i][j]]);

			hlp_all=H[tr[i][j]]*(hlp_u+hlp_v)+g*hlp_xi;

			l_2_u=l_2_u+sin(phi[tr[i][j]])*H[tr[i][j]]*hlp_u;
			l_2_v=l_2_v+sin(phi[tr[i][j]])*H[tr[i][j]]*hlp_v;
			l_2_xi=l_2_xi+sin(phi[tr[i][j]])*g*hlp_xi;

			l_2_all=l_2_all+sin(phi[tr[i][j]])*hlp_all;
		}
		l_2_all=l_2_all*S[i];

		l_2_u=l_2_u*S[i];
		l_2_v=l_2_v*S[i];
		l_2_xi=l_2_xi*S[i];

		L_2_norm[0]=L_2_norm[0]+l_2_all;

		L_2_norm[1]=L_2_norm[1]+l_2_u;
		L_2_norm[2]=L_2_norm[2]+l_2_v;
		L_2_norm[3]=L_2_norm[3]+l_2_xi;
	}
	L_2_norm[0]=radius*sqrt(L_2_norm[0]);
	L_2_norm[1]=radius*sqrt(L_2_norm[1]);
	L_2_norm[2]=radius*sqrt(L_2_norm[2]);
	L_2_norm[3]=radius*sqrt(L_2_norm[3]);

}




