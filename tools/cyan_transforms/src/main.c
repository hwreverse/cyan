#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#include <cyan/color/color.h>
#include <cyan/image/image.h>
#include <cyan/image/load_png.h>

#include <cyan/image/transforms.h>
//#include "transforms.h"

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
	image_save_ppm(grey_image, "grey_boat.ppm");

	//Computes fourier transform of the image
	image_t * ft_image = NULL;
	ft_image = FT_image_Y(image, FFT_2D, cart_to_Y);	//ft_image is the FT with sum of real and im part on each pixel
								//This seems to allow reconstruction (prob. only for real signals
	image_save_ppm( ft_image, argv[1] ) ;		


	//Computes FT of the image and saves power spectrum in power_image
	image_t * power_image = NULL;
	power_image = FT_image_Y(image, FFT_2D, cart_power_to_Y);
	image_save_ppm( power_image, "power.ppm" );

	//Computes FT of the image and saves log of the power spectrum in log_power_image
	image_t * log_power_image = NULL;
	log_power_image = FT_image_Y(image, FFT_2D, cart_log_power_to_Y);
	image_save_ppm( power_image, "log_power.ppm" );

	//Computes FT of the image and saves log of the power spectrum in log_power_image
	image_t * phase_image = NULL;
	phase_image = FT_image_Y(image, FFT_2D, cart_phase_to_Y);
	image_save_ppm( phase_image, "phase.ppm" );



	//Computes the reverse FT on ft_image
	image_t * reverse_image = NULL;
	reverse_image = FT_image_Y(ft_image, FFT_2D_reverse, cart_to_Y);
	image_save_ppm(reverse_image, "fourier.ppm");
	complex_cart_t cart_array[4];

	int n = 2;
	int N = pow(2, n);
	complex_cart_t * fft_cart = NULL;
	fft_cart = FFT_1D_cart_to_cart(cart_array, n);
	for(i=0; i < N; i++){
		fprintf(stdout, "array fft : real : %f, im : %f \n", fft_cart[i].real, fft_cart[i].im);
	}

	complex_cart_t * reverse_cart = NULL;
	reverse_cart = FFT_1D_reverse_cart_to_cart(fft_cart, n);
	for(i = 0; i < N; i++){
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


