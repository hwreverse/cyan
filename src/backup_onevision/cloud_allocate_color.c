#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <onevision/3dmodel/cloud.h>

int cloud_allocate_color( cloud_t* nuage, int color_type ) {
	int i ;
	nuage->color_type = color_type ;
	nuage->colors = calloc ( nuage->nb_points, sizeof(color_t) ) ;
	if( nuage->colors == (color_t*) NULL ) {
		errno = ENOMEM ;
		return -1 ;
	}
	return nuage->nb_points ;
}
