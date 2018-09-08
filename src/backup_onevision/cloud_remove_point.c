#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <onevision/3dmodel/cloud.h>

void cloud_remove_point ( cloud_t* nuage, int point ) {

	point_t* tmp_points = NULL ;
	color_t* tmp_colors = NULL ;
	void*	 tmp_data = NULL ;

	memcpy( nuage->points+point*sizeof(point_t),
		nuage->points+nuage->nb_points*sizeof(point_t),
		sizeof(point_t) ) ;
	tmp_points = realloc( nuage->points, 
		 	      (nuage->nb_points-1)*sizeof(point_t)) ;

	if (nuage->colors!=NULL) {
		memcpy( nuage->colors+point*sizeof(color_t),
			nuage->colors+nuage->nb_points*sizeof(color_t),
			sizeof(color_t));
		tmp_colors = realloc( nuage->colors, (nuage->nb_points-1)*sizeof(color_t)) ;
	}

	if ( nuage->data!=NULL) {
		memcpy( nuage->data+point*nuage->data_size,
			nuage->data+nuage->nb_points*nuage->data_size,
			nuage->data_size) ;
		tmp_data = realloc( nuage->data, (nuage->nb_points-1)*nuage->data_size) ;
	}

	nuage->nb_points -= 1 ;
	nuage->points = tmp_points ;
	nuage->colors = tmp_colors ;
	nuage->data = tmp_data ;

	// FIXME MAJ kdtree !!!!!
}


