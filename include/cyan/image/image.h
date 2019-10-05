#ifndef CYAN_IMAGE_H
#define CYAN_IMAGE_H

#include <cyan/color/color.h>
#include <cyan/image/marker.h>

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

image_t* image_new( int cols, int rows ) ;
void     image_free( image_t* ) ;

int image_allocate_data_default  ( image_t*, size_t size, void* default_data ) ;
int image_allocate_data_fct( image_t*, 
                 size_t datasize, 
			     int (*fill_fct) (image_t*, int, int, void*),
			     void* context ) ;

int image_import_data   ( image_t*, size_t data_size, void* data ) ;

void*    image_get_data_pointer  ( image_t*, int i, int j ) ;

image_t* image_clone ( image_t* ) ;
void image_resize ( image_t*, int rows, int cols ) ;
void image_apply_fct ( image_t*, 
                        void (*fct)( image_t*,int i, int j, void* ctx),
            			void* context ) ;

int image_save(image_t* img, char* filename ) ;
image_t* image_load(char* filename , int* result ) ;

#endif
