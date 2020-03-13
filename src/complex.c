#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#include <cyan/color/color.h>
#include <cyan/image/image.h>
#include <cyan/image/load_png.h>
#include <cyan/image/transforms.h>
#include <cyan/image/fourier.h>
#include <cyan/image/complex.h>


complex_polar_t * unity(int k, int N){
	
	complex_polar_t * unit = (complex_polar_t *) malloc(sizeof(complex_polar_t));
	
	unit->power = (double) 1.0f;
	//Rk: 4*atan(1) = 2 * pi
	unit->phase = 2.0 * (4 * atan( (double) 1.0f)) *  (double) k / (double) N;

	//fprintf(stdout, "unit phase (k, %d, N, %d) : %f\n", k, N, unit->phase);
	return unit;
}
double norm_complex_cart( complex_cart_t z){
	return sqrt(z.real*z.real + z.im * z.im);
}
double power_complex_cart(complex_cart_t z){	
	return fabs(z.real) + fabs(z.im);
}
double phase_complex_cart( complex_cart_t z){ 
	//Note : atan seems to handle infinities
	return atan2( z.im, z.real );
}

void * polar_to_cart( complex_cart_t * z_cart, complex_polar_t z_pol){
	if(z_pol.power != 0.0f){
		z_cart->real = z_pol.power * cos(z_pol.phase);
		z_cart->im   = z_pol.power * sin(z_pol.phase);
	}else{
		z_cart->real 	= 0.0f;
		z_cart->im	= 0.0f;
	}
}
void * cart_to_polar( complex_polar_t * z_pol, complex_cart_t z_cart){
	z_pol->phase = phase_complex_cart( z_cart );
	z_pol->power = norm_complex_cart ( z_cart );
}


void * assign_complex_polar( complex_polar_t * result, complex_polar_t z){
	result->phase = z.phase;
	result->power = z.power;
}
//Returns an array of size N containing polar values of values contained in cart_array
complex_polar_t * cart_array_to_polar( complex_cart_t * cart_array, int N){
	complex_polar_t * polar_array;
	polar_array = (complex_polar_t *) malloc(N * sizeof(complex_polar_t));
	int i;

	for(i = 0; i< N; i++)
		cart_to_polar(&(polar_array[i]), cart_array[i]); 
		
	return polar_array;
}

//Returns an array of size N containing cartesian values of values contained in polar_array
complex_cart_t * polar_array_to_cart( complex_polar_t * polar_array, int N){
	complex_cart_t * cart_array;
	cart_array = (complex_cart_t *) malloc(N * sizeof(complex_cart_t));
	int i;

	for(i = 0; i< N; i++)
		polar_to_cart(&(cart_array[i]), polar_array[i]); 
		
	return cart_array;
}

complex_cart_t * add_complex_cart(complex_cart_t * result, complex_cart_t z1, complex_cart_t z2){	
	result->real 	= z1.real + z2.real;
	result->im	= z1.im + z2.im;
	
	return result;
}
complex_cart_t * substract_complex_cart(complex_cart_t * result, complex_cart_t z1, complex_cart_t z2){	
	result->real 	= z1.real - z2.real;
	result->im	= z1.im - z2.im;
	
	return result;
}


double  mult_complex_polar( complex_polar_t * result, complex_polar_t z1, complex_polar_t z2){
	result->phase 	= z1.phase + z2.phase;
	
	if(z1.power != 0.0f && z2.power != 0.0f)
		result->power 	= z1.power * z2.power;
	else
		result->power = 0.0f;

	return result->power;
}
void * flip_cart(complex_cart_t * z){
	z->real = -(z->real);
	z->im = -(z->im);
}
void * flip_polar(complex_polar_t * z){
	z->phase = - (z->phase) ;
}
void * mult_complex_cart( complex_cart_t * result, complex_cart_t z1, complex_cart_t z2){
	result->real 	= z1.real *  z2.real 	- z1.im * z2.im;
	result->im 	= z1.real * z2.im	+ z1.im * z2.real; 	
}

double energy_complex_cart( complex_cart_t z){
	return z.real*z.real + z.im*z.im;
}
double zero(complex_cart_t z){
	return 0.0f;
}
double sum(complex_cart_t z){
	return z.real + z.im;
}
double log_power_complex_cart(complex_cart_t z){
	return log(power_complex_cart( z) );
}

