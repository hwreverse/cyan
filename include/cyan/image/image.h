#ifndef CYAN_IMAGE_H
#define CYAN_IMAGE_H

#include <cyan/config/cyan.h>
#include <cyan/color/color.h>

typedef struct {
	int rows ; 
	int cols ; 
	double* X ;                         // XYZ as defined in CIE 1976
    double* Y ;
    double* Z ;
    enum cyan_refwhite illuminant ;     // Default to CYAN_D50
    int monochrome ;                    // if set to zero (remark : isn't it the opposite ?, Leo) , only the Y plane will be used
				
	size_t pixel_data_size ;
	void*  pixel_data ;
} image_t ;

image_t* image_new( int cols, int rows ) ;
void     image_free( image_t* ) ;
image_t * image_new_empty( int cols, int rows);

int image_cat_hor( image_t ** dst, image_t * img_left, image_t * img_right );
int image_cat_ver( image_t ** dst, image_t * img_up, image_t * img_bot );

int image_crop_rows(image_t ** dst, image_t * src, int first_row, int last_row);

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
