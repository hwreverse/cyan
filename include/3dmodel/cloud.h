#ifndef CYAN_CLOUD_H
#define CYAN_CLOUD_H

#include <stdlib.h>
#include <3dmodel/point.h>
#include <color/color.h>

typedef struct cloud_s {
	
	int nb_points ;
	int color_type ;
	size_t data_size ;
	
	point_t* points ;
	color_t* colors ;
	void*    data ;

	void*	tree ;

} cloud_t ;

#define cloud_get_data_pointer( nuage, i ) 	(nuage->data+i*nuage->data_size)
#define cloud_get_color_pointer( nuage, i )	(nuage->colors+i)
#define cloud_get_point_pointer( nuage, i )	(nuage->points+i)

cloud_t* cloud_new( int nb_points ) ;
void cloud_free( cloud_t* ) ;

int cloud_allocate_color ( cloud_t*, int color_type, color_t default_color ) ;
int cloud_allocate_data  ( cloud_t*, size_t size,  void* default_data ) ;

cloud_t* cloud_clone ( cloud_t* ) ;
cloud_t* cloud_merge ( cloud_t*, cloud_t* ) ;

int cloud_add_point( cloud_t* cloud, point_t* point, color_t* color, void* data ) ; 
void cloud_remove_point ( cloud_t* cloud, int point ) ;

void cloud_strip_colors ( cloud_t*) ;
void cloud_strip_data   ( cloud_t*) ;
void cloud_strip_tree   ( cloud_t*) ;

int cloud_build_tree   ( cloud_t* ) ;
int cloud_search_nearest ( cloud_t*, point_t ) ;


#endif
