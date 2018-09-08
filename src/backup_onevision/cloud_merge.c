#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <onevision/3dmodel/cloud.h>

cloud_t* cloud_merge(cloud_t* A, cloud_t* B) {
	int i ;
	cloud_t* tmp = NULL ;
	color_t* tmp_colors = NULL ;
	void*    tmp_data = NULL ;
	
	// allocation nuage tmp

	tmp = cloud_new( A->nb_points + B->nb_points) ;
	if ( tmp == NULL ) {
		errno = ENOMEM ;
		return NULL ;
	}

	// Allocations memoires

	if ((A->color_type != B->color_type) ||
	    ( A->colors == NULL ) || 
            ( B->colors == NULL ) ){
		tmp->color_type = COLORTYPE_NONE ;
		tmp_colors= NULL ;
	} else {
		tmp->color_type = A->color_type ;
		tmp_colors = malloc( tmp->nb_points * sizeof(color_t) ) ;
	}

	if (( A->data_size != B->data_size ) || 
	    ( A->data == NULL ) || 
	    ( B->data == NULL )) {
	    	tmp->data_size = (size_t) 0 ;
	    	tmp_data=NULL ;
	} else {
		tmp->data_size = A->data_size ;
		tmp_data = malloc (tmp->nb_points * tmp->data_size);
	}

	if (((tmp_data==NULL) && (tmp->data_size!=(size_t)0)) ||
            ((tmp_colors==NULL) && (tmp->color_type!=COLORTYPE_NONE))) {
	    	free(tmp_data) ;
		free(tmp_colors);
		cloud_free( tmp ) ;
		errno = ENOMEM ;
		return NULL ;
	}

	tmp->data = tmp_data ;
	tmp->colors = tmp_colors ;

	// Copie des données

	memcpy(tmp->points, 
		A->points, 
		A->nb_points*sizeof(point_t)) ;
	memcpy(tmp->points + A->nb_points*sizeof(point_t), 
		B->points, 
		B->nb_points*sizeof(point_t)) ;

	if (tmp_colors!=NULL) {
		memcpy( tmp->colors, 
			A->colors, 
			A->nb_points*sizeof(color_t) ) ;
		memcpy( tmp->colors+A->nb_points*sizeof(color_t), 
			B->colors, 
			B->nb_points*sizeof(color_t) ) ; 
	}
	
	if (tmp_data!=NULL) {
		memcpy( tmp->data, 
			A->data, 
			A->nb_points*tmp->data_size ) ;
		memcpy( tmp->data + A->nb_points * tmp->data_size,
			B->data,
			B->nb_points*tmp->data_size ) ;
	}

	return tmp ;
}
