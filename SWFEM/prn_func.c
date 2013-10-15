#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <math.h>

#include "My_def.h"

extern double radius,g,omega,tau,tau1;


void prn_result(double *lmbd, double *phi,
				double *vec1, double *vec2, double *vec3, double *vec4, double *vec5, double *vec6,
				double *max, double *min, double *L_2_norm, int *max_num, int *min_num,
				char *fix1, char *ext, const int num, const int n, const int m, const int pr,
				char *text,char *head)
{// m - number of arrays which have to printed
 // n - time lavel
 // p - indicator of analise data printed
	register int i;
	FILE *out_file;
	char name[30];
	double lmbd_grad, phi_grad;


//file name
	sprintf(name,"%s-%d.%s",fix1,n,ext);
//file open for writing
	if ((out_file=fopen(name, "w"))==NULL) {
		printf("Error at opening of the file.\n");
		exit(1);
	}

	fprintf(out_file, "#%s\n",head);
	for (i=1; i<=num; i++){
        lmbd_grad=lmbd[i]/PI_DIV_180;
		phi_grad=phi[i]/PI_DIV_180;
//		phi_grad=(phi[i]-half_PI)/PI_DIV_180;

		switch (m) {
				case 3:
					fprintf(out_file, "%5i %20.12le %20.12le %20.12le %20.12le %20.12le\n",
						i,lmbd_grad,phi_grad,vec1[i],vec2[i],vec3[i]);
					break;
				case 4:
					fprintf(out_file, "%5i %20.12le %20.12le %20.12le %20.12le %20.12le %20.12le\n",
						i,lmbd_grad,phi_grad,vec1[i],vec2[i],vec3[i],vec4[i]);
					break;
				case 5:
					fprintf(out_file, "%5i %20.12le %20.12le %20.12le %20.12le %20.12le %20.12le %20.12le\n",
						i,lmbd_grad,phi_grad,vec1[i],vec2[i],vec3[i],vec4[i],vec5[i]);
					break;
				case 6:
					fprintf(out_file, "%5i %20.12le %20.12le %20.12le %20.12le %20.12le %20.12le %20.12le %20.12le\n",
						i,lmbd_grad,phi_grad,vec1[i],vec2[i],vec3[i],vec4[i],vec5[i],vec6[i]);
					break;
			}
	}

	fprintf(out_file,"\n");

	if (pr == 1) prn_analise(max,min,L_2_norm,max_num,min_num,text,out_file);

	fclose(out_file);
}

void prn_analise(double *max, double *min, double *L_2_norm, int *max_num, int *min_num, char *text, FILE *file_w)
{

#if ind_test==1
	fprintf(file_w,"%s\n\n",text);

	fprintf(file_w,"max u =  %20.12le   in point %5i\n", max[1],max_num[1]);
	fprintf(file_w,"L_2 norm u =  %20.12le \n", L_2_norm[1]);

	fprintf(file_w,"max v =  %20.12le   in point %5i\n", max[2],max_num[2]);
	fprintf(file_w,"L_2 norm v =  %20.12le \n", L_2_norm[2]);

	fprintf(file_w,"max xi =  %20.12le   in point %5i\n", max[3],max_num[3]);
	fprintf(file_w,"L_2 norm xi =  %20.12le \n", L_2_norm[3]);

	fprintf(file_w,"\n%s\n\n\n", " *************** ");
	fprintf(file_w,"max all =  %20.12le   in point %5i\n", max[0],max_num[0]);
	fprintf(file_w,"L_2 norm all =  %20.12le \n", L_2_norm[0]);
	fprintf(file_w,"\n%s\n\n\n", " *************** ");


	fprintf(file_w,"UNIFORM NORM\n\n");

	fprintf(file_w,"%20.12le\n", max[1]);
	fprintf(file_w,"%20.12le\n", max[2]);
	fprintf(file_w,"%20.12le\n", max[3]);
	fprintf(file_w,"%20.12le\n\n\n", max[0]);

	fprintf(file_w,"L_2 NORM\n\n");

	fprintf(file_w,"%20.12le\n", L_2_norm[1]);
	fprintf(file_w,"%20.12le\n", L_2_norm[2]);
	fprintf(file_w,"%20.12le\n", L_2_norm[3]);
	fprintf(file_w,"%20.12le\n", L_2_norm[0]);

#else
	fprintf(file_w,"%s\n\n",text);

	fprintf(file_w,"min u =  %20.12le   in point %5i\n", min[1],min_num[1]);
	fprintf(file_w,"max u =  %20.12le   in point %5i\n", max[1],max_num[1]);
	fprintf(file_w,"L_2 norm u =  %20.12le \n", L_2_norm[1]);

	fprintf(file_w,"min v =  %20.12le   in point %5i\n", min[2],min_num[2]);
	fprintf(file_w,"max v =  %20.12le   in point %5i\n", max[2],max_num[2]);
	fprintf(file_w,"L_2 norm v =  %20.12le \n", L_2_norm[2]);

	fprintf(file_w,"min xi =  %20.12le   in point %5i\n", min[3],min_num[3]);
	fprintf(file_w,"max xi =  %20.12le   in point %5i\n", max[3],max_num[3]);
	fprintf(file_w,"L_2 norm xi =  %20.12le \n", L_2_norm[3]);

	fprintf(file_w,"\n%s\n\n\n", " *************** ");
	fprintf(file_w,"L_2 norm all =  %20.12le \n", L_2_norm[0]);
	fprintf(file_w,"\n%s\n\n\n", " *************** ");
#endif

}

void prn_pic(double *lmbd, double *phi, double *vec1, double *vec2, double *vec3,
             int **tr, const int now_n, const int num_tr,
			 const int num_pic, const int num_t, const int iter, const int ind)
{
	register int i,j;
	FILE *out_f;
	char name[30];
	double lmbd_grad,phi_grad;


//file name
	switch (ind){
		case 0: sprintf(name,"%d-obs_pic-%d.dat",iter,num_pic); break;
		case 1: sprintf(name,"%d-dir_pic-%d.dat",iter,num_pic); break;
		case 2: sprintf(name,"%d-adj_pic-%d.dat",iter,num_pic); break;
		case 3: sprintf(name,"%d-end_pic-%d.dat",iter,num_pic); break;
	}
//file open for writing
	if ((out_f=fopen(name, "w"))==NULL) {
		printf("Error at opening of the file.\n");
		exit(1);
	}

	fprintf(out_f, "#time %5i  *****  iter %5i",num_t,iter);

	for (i=1; i<=num_tr; i++){
		for (j=0; j<3; j++){
			lmbd_grad=lmbd[tr[i][j]]/PI_DIV_180;
			phi_grad=(phi[tr[i][j]]-half_PI)/PI_DIV_180;

			fprintf(out_f, "%5i  %20.12le  %20.12le  %20.12le  %20.12le  %20.12le  %5i\n",
                tr[i][j],lmbd_grad,phi_grad,vec1[tr[i][j]],vec2[tr[i][j]],vec3[tr[i][j]],i);
		}
		lmbd_grad=lmbd[tr[i][0]]/PI_DIV_180;
		phi_grad=(phi[tr[i][0]]-half_PI)/PI_DIV_180;

		fprintf(out_f, "%5i  %20.12le  %20.12le  %20.12le  %20.12le  %20.12le  %5i\n\n",
                tr[i][0],lmbd_grad,phi_grad,vec1[tr[i][0]],vec2[tr[i][0]],vec3[tr[i][0]],i);
	}

	fclose(out_f);
}

void prn_rich(double *lmbd, double *phi,
				double *vec1, double *vec2, double *vec3, double *vec4, double *vec5, double *vec6, double *vec7,
				char *fix1, char *ext, const int num, const int n, const int m)
{// m - number of arrays which have to printed
 // n - time lavel
 // p - indicator of analise data printed
	register int i;
	FILE *out_file;
	char name[30];

//file name
	sprintf(name,"%s-%d.%s",fix1,n,ext);
//file open for writing
	if ((out_file=fopen(name, "w"))==NULL) {
		printf("Error at opening of the file.\n");
		exit(1);
	}

	fprintf(out_file,"%i\n",num);

	for (i=1; i<=num; i++){

		switch (m) {
				case 3:
					fprintf(out_file, "%5i %20.12le %20.12le %20.12le %20.12le %20.12le\n",
						i,lmbd[i],phi[i],vec1[i],vec2[i],vec3[i]);
					break;
				case 4:
					fprintf(out_file, "%5i %20.12le %20.12le %20.12le %20.12le %20.12le %20.12le\n",
						i,lmbd[i],phi[i],vec1[i],vec2[i],vec3[i],vec4[i]);
					break;
				case 5:
					fprintf(out_file, "%5i %20.12le %20.12le %20.12le %20.12le %20.12le %20.12le %20.12le\n",
						i,lmbd[i],phi[i],vec1[i],vec2[i],vec3[i],vec4[i],vec5[i]);
					break;
				case 6:
					fprintf(out_file, "%5i %20.12le %20.12le %20.12le %20.12le %20.12le %20.12le %20.12le %20.12le\n",
						i,lmbd[i],phi[i],vec1[i],vec2[i],vec3[i],vec4[i],vec5[i],vec6[i]);
					break;
				case 7:
					fprintf(out_file, "%5i %20.12le %20.12le %20.12le %20.12le %20.12le %20.12le %20.12le %20.12le %20.12le\n",
						i,lmbd[i],phi[i],vec1[i],vec2[i],vec3[i],vec4[i],vec5[i],vec6[i],vec7[i]);
					break;
			}
	}

	fclose(out_file);
}
