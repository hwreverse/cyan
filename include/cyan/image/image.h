#ifndef CYAN_IMAGE_H
#define CYAN_IMAGE_H

#include <cyan/common/config.h>
#include <cyan/color/color.h>

typedef struct {
	int rows ; 
	int cols ; 
	double* X ;                         // XYZ as defined in CIE 1976
    	double* Y ;
    	double* Z ;
    	enum cyan_refwhite illuminant ;     // Default to CYAN_D50
    	int monochrome ;                    // if set to zero, only the Y plane will be used
    	size_t pixel_data_size ;
	void*  pixel_data ;
} image_t ;

image_t* image_new( int cols, int rows, int monochrome ) ;
void     image_free( image_t* ) ;

int image_allocate_data_default  ( image_t*, size_t size, void* default_data ) ;
int image_allocate_data_fct( image_t*, 
                 size_t datasize, 
			     int (*fill_fct) (image_t*, int, int, void*),
			     void* context ) ;

int image_import_data   ( image_t*, size_t data_size, void* data ) ;

int image_get_data_pointer  ( image_t*, int i, int j, void** ) ;

int image_clone ( image_t*, image_t** ) ;
int image_resize ( image_t*, int cols, int rows, int monochrome, void* default_pixel_data ) ;  

int image_save(image_t* img, char* filename ) ;         // TODO
image_t* image_load(char* filename , int* result ) ;    // TODO

int image_strip_data(image_t*) ;

#endif
