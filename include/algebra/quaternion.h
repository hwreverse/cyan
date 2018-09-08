#ifndef CYAN_QUATERNION_H
#define CYAN_QUATERNION_H

#include <onevision/algebra/matrix.h>
#include <onevision/algebra/vector3d.h>


typedef struct {

	double q[4] ;

} quaternion_t ;

double quaternion_norm( quaternion_t* ) ;

void quaternion_sum ( quaternion_t*, quaternion_t*, quaternion_t* ) ;
void quaternion_prod ( quaternion_t*, quaternion_t*, quaternion_t* ) ;
void quaternion_eprod ( double, quaternion_t*, quaternion_t* ) ;


void quaternion_sum_ ( quaternion_t*, quaternion_t* ) ;
void quaternion_prod_ ( quaternion_t*, quaternion_t* ) ;
void quaternion_eprod_ ( double, quaternion_t* ) ;

double quaternion_Re ( quaternion_t* ) ;
vector3d_t quaternion_Im ( quaternion_t* ) ;

matrix_t quaternion_matrix ( quaternion_t* ) ;

#endif
