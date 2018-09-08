#ifndef CYAN_TMATRIX_H
#define CYAN_TMATRIX_H

#include <algebra/vector3d.h>
#include <algebra/rotation.h>

typedef struct {

	double coeffs[12] ;

	rotation_t* rotation ;
	vector3d_t* translation ;

} tmatrix_t ;

tmatrix_t* tmatrix_new ( double R11, double R12, double R13,
                         double R21, double R22, double R23,
                         double R31, double R32, double R33,
                         double Tx, double Ty, double Tz ) ;

tmatrix_t* tmatrix_new_identity () ;
tmatrix_t* tmatrix_new_rottrans ( rotation_t* rot, vector3d_t* vector ) ;
tmatrix_t* tmatrix_new_DH ( double d, double theta, double r, double alpha   ) ;	// Denavit Hartenberg
tmatrix_t* tmatrix_new_KK ( double d, double theta, double r, double alpha   ) ;	// Khalil Kleinfinger
tmatrix_t* tmatrix_new_matrix ( matrix_t* ) ;					

void tmatrix_free( tmatrix_t* ) ;

rotation_t* tmatrix_get_rotation( tmatrix_t*, int rot_type ) ;
vector3d_t* tmatrix_get_translation( matrix_t* ) ;

int tmatrix_set_rotation( tmatrix_t*, rotation_t* ) ;
int tmatrix_set_translation( matrix_t*, vector3d_t* ) ;
void tmatrix_set ( tmatrix_t*, rotation_t*, vector3d_t* ) ;

matrix_t*  tmatrix2matrix ( tmatrix_t* ) ;
tmatrix_t* tmatrix_prod( tmatrix_t*, tmatrix_t* ) ;

void matrix_get_rotation_ ( tmatrix_t*, int rot_type, rotation_t* ) ;
void matrix_get_translation_ ( tmatrix_t*, vector3d_t* ) ;
void tmatrix_prodleft_  ( tmatrix_t* A, tmatrix_t* B ) ;			// A <- B.A
void tmatrix_prodright_ ( tmatrix_t* A, tmatrix_t* B ) ;			// A <- A.B
void tmatrix2matrix_ ( tmatrix_t*, matrix_t* ) ;

#endif
