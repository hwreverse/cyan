#ifndef CYAN_CAMERA_H
#define CYAN_CAMERA_H

typedef struct camera_s {

	double focal_length ;
	double aspect_ratio ;	
	double u0 ;
	double v0 ;
	double skew ;

	int    lens_enable ;
	double lens_radial[3] ;
	double lens_tangential[2] ;

    // Ajouter matrice de projection

} camera_t ;

camera_t* camera_new(double focal_length, double aspect_ratio,
		     double u0, double v0, double skew ) ;
void camera_free() ;

void camera_set_lens( double r1, double r2, double r3, double t1, double t2 ) ;

void camera_proj_coords( camera_t*, marker_t*, point_t ) ;

#endif
