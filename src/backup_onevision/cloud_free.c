#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <onevision/3dmodel/cloud.h>


void cloud_free(cloud_t* nuage) {
	if ( nuage->points != (point_t*) NULL )
		free ( nuage->points ) ;
	if ( nuage->colors != (color_t*) NULL )
		free ( nuage->colors ) ;
	if ( nuage->data != (void*) NULL )
		free ( nuage->data ) ;
	if ( nuage->tree != (void*) NULL )
		cloud_strip_tree( nuage ) ;
	free (nuage) ;
}
