#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <cyan/color/color.h>
#include <cyan/image/image.h>

#include "load_png.h"


int main( int argc, char** argv, char* envv ) {

    int i, j ;
    int result ;
    image_t* image ; 
    FILE * fp;
       
	fp = fopen("lena.png", "r");
	if(fp == NULL){	
		fprintf(stderr, "Couldn't open file.\n Error : %d, (%s)\n", errno, strerror(errno));
		return -4;
	}


    if (argc != 2 ) {
        fprintf(stderr,"Usage : %s output_file.ppm\n", argv[0] ) ;
       return -1 ;
    }
  	image = png2image(fp);
    if ( image == NULL ) {
        fprintf(stderr,"image allocation failed\n") ;
        return -2 ;
    }
	result = image_save_ppm( image, argv[1] ) ; 
    
	if (result != 0) {
        fprintf(stderr, "cannot save file\n") ;
        return -3 ;
    }
    
    image_free( image) ;

	fclose(fp);

    return 0 ;
}


