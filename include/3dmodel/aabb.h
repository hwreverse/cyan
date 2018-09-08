#ifndef CYAN_AABB_H
#define CYAN_AABB_H

#include <3dmodel/point.h>
#include <3dmodel/cloud.h>


typedef struct aabb_s {
	double xmin ;
	double xmax ;
	double ymin ;
	double ymax ;
} aabb_t ;

void aabb_expand_point ( aabb_t*, point_t* ) ;
void aabb_expand_cloud ( aabb_t*, cloud_t* ) ;
// TODO void aabb_expand_mesh
// TODO void aabb_expand_cylinder, rect, etc.

#endif
