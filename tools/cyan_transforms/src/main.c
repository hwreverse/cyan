#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <cyan/color/color.h>
#include <cyan/image/image.h>
#include <cyan/image/load_png.h>

#include "transforms.h"

int main( int argc, char** argv, char* envv ) {

	int i, j ;
	int result ;
	image_t * image ;	
	image_t * grey_image;
	FILE * fp;

	fp = fopen("lena.png", "r");
	if(fp == NULL){	
		fprintf(stderr, "Couldn't open file.\n Error : %d, (%s)\n", errno, strerror(errno));
		return -1;
	}


	if (argc != 2 ) {
		fprintf(stderr,"Usage : %s output_file.ppm\n", argv[0] ) ;
		return -1 ;
	}
	image = png2image(fp);
	if ( image == NULL ) {
		fprintf(stderr,"image allocation failed\n") ;
		return -1 ;
	}	
	grey_image = color2grey(image);

	result = image_save_ppm( image, argv[1] ) ; 

	fprintf(stdout, "image monochrome : %d\n", grey_image->monochrome);
	if (result != 0) {
		fprintf(stderr, "cannot save file\n") ;
		return -1 ;
	}

	image_free( image) ;

	fclose(fp);
	
	return 0 ;
}


