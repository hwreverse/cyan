#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>

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
//	grey_image = color2grey(image);

//	result = image_save_ppm( grey_image, argv[1] ) ; 

	complex_cart_t cart_array[4];
	complex_polar_t array[4];
	complex_polar_t buffer[4];

//	for(i=0; i < 8; i++){
//		cart_array[i].real = 0.0f;
//		array[i].power = 0.0f;
//	}

	cart_array[0].real = 1.0f;
	cart_array[0].im = 0.0f;
	
	cart_array[1].real = 2.0f;
	cart_array[1].im = -1.0f;
	
	cart_array[2].real = 0.0f;
	cart_array[2].im = -1.0f;
	
	cart_array[3].real = -1.0f;
	cart_array[3].im = 2.0f;
	for(i = 0; i< 4; i++){
		cart_to_polar(&(array[i]), cart_array[i]);
	}
	complex_polar_t * fft_polar;

	fft_polar = FFT_1D(array, NULL, 2); 
	
	complex_cart_t fft_array_cart[8];
	
	for(i=0; i < 4; i++){
	
//		array[i].power *= 1.0f/sqrt((double) 8);
		polar_to_cart(&(fft_array_cart[i]), fft_polar[i] );	
		fprintf(stdout, "array fft : real : %f, im : %f \n", fft_array_cart[i].real, fft_array_cart[i].im);
	}

	complex_polar_t * reverse_polar;
	reverse_polar = FFT_1D_reverse( fft_polar, 2);
	complex_cart_t reverse_cart[4];
	for(i=0; i<4; i++){
		polar_to_cart(&(reverse_cart[i]), reverse[i]);
		fprintf(stdout, "array reverse : real : %f, im : %f \n", reverse_cart[i].real, reverse_cart[i].im);

	}

	if (result != 0) {
		fprintf(stderr, "cannot save file\n") ;
		return -1 ;
	}

	image_free( image) ;

	fclose(fp);

	return 0 ;
}


