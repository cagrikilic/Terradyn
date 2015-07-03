#pragma once
#include <ode/ode.h>
double *matrix_get( int, int );
void matrix_cpy( int, int, double*, double* );
void matrix_I( int, double* );
void matrix_Z( int, int, double* );
void matrix_print( int, int, double* );
void matrix_mult( int, int, int, double* ,double*, double* );
void matrix_add( int, int, double* ,double*, double* );
void matrix_sub( int, int, double* ,double*, double* );
void matrix_trans( int, int, double*, double* );
void matrix_round( int, int, int, double* );
void matrix_scale( int, int, double, double*, double* );
void mxm1( int, double* , double* , double* );
void matrix_inv( int, double*, double* );
void matrix_pinv( int, int, double*, double* );
void matrix_LU( int, double*, double*, double* );
void matrix_svd( int, int, double *, double*, double*, double* );
double matrix_mlting( int, double* );
double matrix_det( int, double* );
void matrix2dMatrix(int, double* , dReal*);
