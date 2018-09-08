#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <onevision/3dmodel/cloud.h>

cloud_t* cloud_clone( cloud_t* nuage ) {
	
	cloud_t* newcloud = NULL ;
	color_t* tmp_colors = NULL ;
	void* tmp_data = NULL;

	newcloud = cloud_new( nuage->nb_points) ;
	if ( newcloud == (cloud_t*) NULL ) {
		errno = ENOMEM ;
		return NULL ;
	}
	
	newcloud->nb_points = nuage->nb_points ;
	newcloud->color_type = nuage->color_type ;
	newcloud->data_size = nuage->data_size ;
	newcloud->colors = NULL ;
	newcloud->data = NULL ;
	newcloud->tree = NULL ;
	
	if ( nuage->colors != NULL ) {	
		tmp_colors = malloc(newcloud->nb_points*sizeof(color_t)) ;
	}

	if ( nuage->data != NULL ) {
		tmp_data = malloc(newcloud->nb_points*newcloud->data_size) ;
	}

	if (((nuage->data!=NULL) && (tmp_data == NULL))||
	    ((nuage->colors!=NULL)&&(tmp_colors==NULL))) {
	    	free(tmp_colors);
		free(tmp_data);
		cloud_free(newcloud);
		errno = ENOMEM ;
		return NULL ;
	}

	newcloud->colors = tmp_colors ;
	newcloud->data = tmp_data ;

	memcpy( newcloud->points, nuage->points, nuage->nb_points*sizeof(point_t) ) ;

	if ( nuage->colors != NULL ) {
		memcpy( newcloud->colors, 
			nuage->colors, 
			newcloud->nb_points*sizeof(color_t)) ;
	}

	if ( nuage->data != NULL ) {
		memcpy( newcloud->data, 
			nuage->data, 
			newcloud->nb_points * newcloud->data_size ) ;           
	}

	return newcloud ;
}

