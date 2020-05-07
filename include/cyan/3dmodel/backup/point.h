#ifndef CYAN_POINT_H
#define CYAN_POINT_H

typedef struct point_s {
	double coords[3];	// X, Y and Z
} point_t ;

point_t* point_new ( double X, double Y, double Z ) ;
void     point_del ( point_t* ) ;

#endif
