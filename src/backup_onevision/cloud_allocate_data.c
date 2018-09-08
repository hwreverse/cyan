#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <onevision/3dmodel/cloud.h>

int cloud_allocate_data( cloud_t* nuage, size_t size, void* data ) {
	int i ;
	nuage->data_size = size ;
	nuage->data = malloc ( nuage->nb_points * size ) ;
	if ( nuage->points == NULL ) {
		errno = ENOMEM ;
		return -1 ;
	}
	for (i=0; i<nuage->nb_points; i++)
		memcpy( nuage->data + i*nuage->data_size, data, size ) ;	
	return nuage->nb_points ;
}

