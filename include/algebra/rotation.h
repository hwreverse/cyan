#ifndef CYAN_ROTATION_H
#define CYAN_ROTATION_H

#define ROT_EULER ;		// Euler angles
#define ROT_RPY ;		// Roll Pitch Yaw
#define ROT_QUATERNIONS ;	// Quaternions

#include <algebra/matrix.h>

#define ROLL 		0 
#define PITCH 		1 
#define YAW  		2 

#define RHO		0
#define TETHA		1 
#define PHI		2 

#define SINGULAR 	3 

#define ANGLE		0
#define VX		1
#define VY		2
#define VZ		3


typedef struct {
	double params[4] ;
	int rot_type ;
} rotation_t ;

rotation_t* rotation_new_euler ( double rho, double theta, double phi ) ;
rotation_t* rotation_new_rpy ( double roll, double pitch, double yaw ) ;
rotation_t* rotation_new_quaternions ( double q1, double q2, double q3, double q4 ) ;
rotation_t* rotation_new_quaternions_anglevect ( double angle, vector3d_t* ) ;

void rotation_free (rotation_t* ) ;

int rotation_is_singular ( rotation_t* ) ;
int rotation_convert ( rotation_t*, rotation_t* ) ;
int rotation_compose ( rotation_t*, rotation_t*, rotation_t* ) ;

matrix_t* rotation_2_matrix   ( rotation_t* ) ;
rotation_t* matrix_2_rotation ( int rot_type, matrix_t* ) ;

#endif

