#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <cyan/color/color.h>
#include <cyan/image/image.h>

//#include "load_png.h"
#include <cyan_fileio/load_png.h>

//Basic program to open a .jpg file through cyan
//(Probably deprecated... see cyan_transforms )
int main( int argc, char** argv, char* envv ) {

	int i, j ;
	int result ;
	image_t* image ; 
	FILE * fp;


	if (argc != 3 ) {
		fprintf(stderr,"Usage : %s input_file.png output_file.ppm\n", argv[0] ) ;
		return -1 ;
	}
	fp = fopen( argv[1] , "r" );
	if( fp == NULL){
		fprintf(stderr, "Couldn't open file.\n Error : %d, (%s)\n", errno, strerror(errno));
		return -1;
	}
	image = png2image(fp);
	if ( image == NULL ) {
		fprintf(stderr,"image allocation of %s failed \n", argv[1]) ;
		return -1 ;
	}
	result = image_save_ppm( image, argv[2] ) ; 

	if (result != 0) {
		fprintf(stderr, "cannot save file\n") ;
		return -1 ;
	}

	image_free( image) ;

	fclose(fp);

    return 0 ;
}


