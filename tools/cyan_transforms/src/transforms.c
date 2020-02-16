#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

#include <cyan/color/color.h>
#include <cyan/image/image.h>
#include <cyan/image/load_png.h>

#include "transforms.h"

complex_polar_t * unity(int k, int N){
	
	complex_polar_t * unit = (complex_polar_t *) malloc(sizeof(complex_polar_t));
	
	unit->power = (double) 1.0f;
	unit->phase = 2.0 * (4 * atan( (double) 1.0f)) *  (double) k / (double) N;

	return unit;
}

//FFT_1D computes the 1D Fast Fourier Transform of the sequence f of 2^n elements (i.e. {f(k)}_{k=0,...,2^n}
complex_polar_t * FFT_1D( complex_polar_t * f, complex_polar_t * buffer, int n){
	
	int N = pow(2, n);
	if(buffer == NULL){
		fprintf(stdout, "FFT_1D : Allocating the buffer.\n");
		buffer = (complex_polar_t *) malloc( N * sizeof(complex_polar_t));
	}
	if(n == 0)
		return f;
	
	complex_polar_t * W_N = unity(1, N);
	complex_polar_t * W = unity(1, 1);
	complex_polar_t * temp_polar = unity(1, 1);	
	complex_cart_t  *temp_cart1= malloc(sizeof(complex_cart_t));
	complex_cart_t  *temp_cart2= malloc(sizeof(complex_cart_t));

	complex_cart_t * f_temp_cart = malloc(sizeof(complex_cart_t));
	int i;
	//Rearranging f with the N/2 even elems, then the N/2 odd elems
	for(i = 0; i< N/2; i++){
		buffer[i] = f[2*i + 1]; //to N-2
		f[i] = f[2*i];
		f[N/2 + i] = buffer[i];
	}
	//Computing odd and even fft in buffer
	//stores similarly as f
	FFT_1D( buffer, f, n-1);
	FFT_1D( &(buffer[ N/2 + 1]), &(f[ N/2 + 1]), n-1 ); 
	int j = 0;
	for(j = 0; j< N/2; j++)
	{
		//Even part
		mult_complex_polar(temp_polar, *W, buffer[2*j + 1]);
		polar_to_cart(temp_cart1, *temp_polar);
		polar_to_cart(temp_cart2, buffer[2*j]);
		
		add_complex_cart(f_temp_cart, *temp_cart1, *temp_cart2);

		cart_to_polar(&(f[j]), *f_temp_cart);
			
		//Odd part
		temp_cart2->real *= (-1.0f);
		temp_cart2->im *=(-1.0f);
		
		add_complex_cart(f_temp_cart, *temp_cart1, *temp_cart2);
		cart_to_polar(&(f[j + N/2]),*f_temp_cart );
		
		//Updating phase factor
		mult_complex_polar(W, *W, *W_N);
	}
	return f;
}


//Returns a grey level copy of color_img
image_t * color2grey(image_t * color_img){

	fprintf(stdout, "Entering color2grey().\n");

	if(color_img == NULL){
		fprintf(stderr, "color2grey() was given a NULL pointer instead of an image.\n");
		return NULL;
	}
	
	//Saving monochrome state of color_img	
	int monochrome_backup = color_img->monochrome;
	color_img->monochrome = 1;
	
	//Making a copy of color_img w/ a monochrome state
	
	fprintf(stdout, "Cloning color_img.\n");
//	fprintf(stdout, "clone : %x, image : %x\n",image_clone( color_img ), color_img);
	
	image_t * grey_img;
	grey_img = image_clone(color_img);	

	//Restoring monochrome state in color_img in order to keep it unchanged through color2grey()
	color_img->monochrome = monochrome_backup;

	fprintf(stdout, "About to exit color2grey()");
	return grey_img;

}

//dot_product_4_f() returns the dot product of 2 vectors containing 4 floats
float dot_product_4_f(	float x1, float x2, float x3, float x4,
			float y1, float y2, float y3, float y4 ){
	return x1*y1 + x2*y2 + x3*y3 + x4*y4 ;
}

//Returns the norm 2 (euclidean) squared of a vector containing 4 floats
float norm_2_sq_4_f( float x, float y, float z, float t){
	return dot_product_4_f( x, y, z, t, x, y, z, t) ;
}

void * assign_complex_polar( complex_polar_t * result, complex_polar_t z){
	result->phase = z.phase;
	result->power = z.power;
}

double  mult_complex_polar( complex_polar_t * result, complex_polar_t z1, complex_polar_t z2){
	result->phase 	= z1.phase + z2.phase;
	result->power 	= z1.power * z2.power;

	return result->power;
}
void * mult_complex_cart( complex_cart_t * result, complex_cart_t z1, complex_cart_t z2){
	result->real 	= z1.real *  z2.real 	- z1.im * z2.im;
	result->im 	= z1.real * z2.im	+ z1.im * z2.real; 
}
complex_cart_t * add_complex_cart(complex_cart_t * result, complex_cart_t z1, complex_cart_t z2){
		
	result->real 	= z1.real + z2.real;
	result->im	= z1.im + z2.im;
	return result;
}

double norm_complex_cart( complex_cart_t z){
	return sqrt( pow(z.real, 2) + pow(z.im, 2));
}
double phase_complex_cart( complex_cart_t z){ 
	//Note : atan seems to handle infinities
	return atan( z.im / z.real );
}

void * polar_to_cart( complex_cart_t * z_cart, complex_polar_t z_pol){
	z_cart->real = z_pol.power * cos(z_pol.phase);
	z_cart->im   = z_pol.power * sin(z_pol.phase);
}
void * cart_to_polar( complex_polar_t * z_pol, complex_cart_t z_cart){
	z_pol->phase = phase_complex_cart( z_cart );
	z_pol->power = norm_complex_cart ( z_cart );
}


