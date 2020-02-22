#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>

#include <png.h>

#include "load_png.h"

image_t* png2image(FILE * fp) {
	
	image_t * image;
	color_t* couleur ;
	
	if(!fp){
		fprintf(stderr, "Empty file pointer in png2image().\n");
		return NULL;
	}
    png_structp	png_ptr;
    png_infop info_ptr;
    png_uint_32 width;
    png_uint_32 height;
    int bit_depth;
    int color_type;
    int interlace_method;
    int compression_method;
    int filter_method;
    int i,j;
    png_bytepp rows;

    png_ptr = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (! png_ptr) {
	return NULL;
    }
    info_ptr = png_create_info_struct (png_ptr);
    if (! png_ptr) {
	return NULL;
    }

    //TODO : check what happens if a non .png file is given
    //There exists a function to check if the file is a real .png

    png_init_io (png_ptr, fp);
    png_read_png (png_ptr, info_ptr, 0, 0);
    png_get_IHDR (png_ptr, info_ptr, & width, & height, & bit_depth,
		  & color_type, & interlace_method, & compression_method,
		  & filter_method);
	if(color_type != PNG_COLOR_TYPE_RGB){
		fprintf(stderr, "PNG color type is not RGB, not handled (yet).");
		//TODO Add this case
		return NULL;
	    }
	if(interlace_method != 0){
		fprintf(stderr, "Behaviour could be unexpected in the following");
		//TODO See why ? Fix ? Who doesn't like a surprise ?Electrique
	}

    //Uncomment the following line if you want to ignore the alpha channel (never tested)
    //   png_set_strip_alpha(png_ptr);	
    image = image_new(width, height, COLORTYPE_RGB);
	if(!image){
		fprintf(stderr, "The image couldn't be created\n");
		return NULL;
	}	
    rows = png_get_rows (png_ptr, info_ptr);
    printf ("Width is %d, height is %d\n", width, height);
    
    int rowbytes;
    rowbytes = png_get_rowbytes (png_ptr, info_ptr);
    printf ("Row bytes = %d\n", rowbytes);
    
       for (i = 0; i < height; i++) {
	   	for (j = 0; j < width ; j++) {
			couleur = image_get_pixel_pointer( image, j, i ) ;
			couleur->coords[0] = rows[i][3*j]/(float) 255 ;
			couleur->coords[1] = rows[i][3*j+1]/ (float) 255 ;
			couleur->coords[2] = rows[i][3*j+2]/ (float) 255 ;
			
			//printf("%f %f %f\n ",  couleur->coords[0],  couleur->coords[1], couleur->coords[2]);
		}  
	} 

	png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);	
    
	return image;

}

static void
fatal_error (const char * message, ...)
{
    va_list args;
    va_start (args, message);
    vfprintf (stderr, message, args);
    va_end (args);
    exit (EXIT_FAILURE);
}

