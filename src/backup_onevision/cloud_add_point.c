#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <onevision/3dmodel/cloud.h>

int cloud_add_point( cloud_t* cloud, point_t* point, color_t* color, void* data ) {
	
	void* alloc_points ;
	void* alloc_colors ;
	void* alloc_data ;
	
	if ( (( cloud->colors != NULL ) && ( color == NULL ))
	   || (( cloud->data != NULL ) && ( data == NULL )) ) {
		errno = EINVAL ;
		return -1 ;
	}

	alloc_points = NULL ;
	alloc_colors = NULL ;
	alloc_data = NULL ;

	alloc_points = realloc( cloud->points, (cloud->nb_points+1)*sizeof(point_t)) ;
	if (cloud->colors != NULL)
		alloc_colors = realloc( cloud->colors, (cloud->nb_points+1)*sizeof(color_t)) ;
	if (cloud->data != NULL)
		alloc_data = realloc( cloud->data, (cloud->nb_points+1)*cloud->data_size) ;

	if  ((alloc_points == NULL) ||
	      ((cloud->colors != NULL) && (alloc_colors == NULL)) ||
	      ((cloud->data != NULL) && (alloc_data == NULL ))) {
		errno = ENOMEM ;	// FIXME Memory leak here
		return -1 ;
	}
	
	cloud->points = alloc_points ;
	cloud->nb_points += 1 ;

	memcpy( &cloud->points[cloud->nb_points-1], point, sizeof(point_t) ) ;
	
	if ( cloud->colors != NULL ) {
		cloud->colors = alloc_colors ;
		memcpy( &cloud->colors[cloud->nb_points-1], color, sizeof(color_t) ) ;
	}

	if ( cloud->data != NULL ) {
		cloud->data = alloc_data ;
		memcpy( cloud->data + cloud->nb_points*cloud->data_size, data, cloud->data_size ) ;
	}

	// FIXME MAJ kdtree

	return cloud->nb_points ;
}
