#ifndef CYAN_IMAGE_H
#define CYAN_IMAGE_H

#include <color/color.h>
#include <image/marker.h>

typedef struct {

	int rows ;
	int cols ;
	
	int colortype ;
	color_t* pixels ;
	
	size_t data_size ;
	void*    data ;

	int nb_markers ;
	void* markers ;

} image_t ;

image_t* image_new( int rows, int cols, int colortype ) ;
void     image_free( image_t* ) ;

int image_allocate_data_default  ( image_t*, size_t size, void* default_data ) ;

int image_allocate_data_fct( image_t*, size_t datasize, 
			     int (*fill_fct) (image_t*, int, int, void*),
			     void* context ) ;

int image_import_data   ( image_t*, size_t data_size, void* data ) ;

void*    image_get_data_pointer  ( image_t*, int i, int j ) ;
color_t* image_get_pixel_pointer ( image_t*, int i, int j ) ;

image_t* image_clone ( image_t* ) ;
void image_resize ( image_t*, int rows, int cols ) ;
void image_apply_fct ( image_t*, void (*fct)( image_t*,int i, int j, void* ctx),
			void* context ) ;

int add_marker( image_t*, marker_t ) ;
int add_marker_uv ( image_t*, double U, double V ) ;
int del_marker( image_t*, int position) ;

#endif
