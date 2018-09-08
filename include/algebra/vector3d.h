#ifndef CYAN_VECTOR3D_H
#define CYAN_VECTOR3D_H

typedef struct {
	double v[3] ;
} vector3d_t ;

double vector3d_norm ( vector3d_t* ) ;

void   vector3d_sum ( vector3d_t*,vector3d_t*, vector3d_t* ) ;
void   vector3d_eprod ( double, vector3d_t*, vector3d_t* ) ;
void   vector3d_vectprod ( vector3d_t*,vector3d_t*, vector3d_t* ) ;

double vector3d_scalprod ( vector3d_t*,vector3d_t* ) ;

void   vector3d_sum_ ( vector3d_t*, vector3d_t* ) ;
void   vector3d_eprod_ ( double, vector3d_t* ) ;
void   vector3d_vectprod_ ( vector3d_t*,vector3d_t* ) ;

#endif
