#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <onevision/3dmodel/cloud.h>

cloud_t* cloud_new( int nb_points) {
	cloud_t* nuage = malloc( sizeof( cloud_t)) ;
	if ( nuage == NULL ) {
		errno = ENOMEM ;
		return NULL ;
	}
	nuage->points = malloc(nb_points*sizeof(point_t)) ;
	if ( nuage->points == NULL ) {
		free (nuage) ;
		errno = ENOMEM ;
		return NULL ;
	}
	nuage->nb_points = nb_points ;
	nuage->color_type = COLORTYPE_NONE ;
	nuage->data_size = (size_t) 0 ;
	nuage->colors = (color_t*) NULL ;
	nuage->data = (void*) NULL ;
	nuage->tree = (void*) NULL ;
	return nuage ;
}
