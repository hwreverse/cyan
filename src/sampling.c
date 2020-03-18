#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#include <cyan/color/color.h>
#include <cyan/image/image.h>
#include <cyan/image/load_png.h>
#include <cyan/image/complex.h>
#include <cyan/image/transforms.h>
#include <cyan/image/sampling.h>


//TODO : use this sampling function in FFT * to obtain odd and even elem 
int sub_sampling_step( void ** dst, void *  src, int number_elem, int step, size_t size, void (*assign)(void *, void *) ){
	
	if(dst == NULL){
		fprintf(stderr, "ERROR : sub_sampling_step: dst is a NULL pointer.\n");
		return -1;
	}

	if(*dst == NULL){
		fprintf(stdout, "sub_sampling_step : allocating memory ( allocated : %d, \ttotal size : %d ).\n",(number_elem/step)*size , number_elem * size );
		*dst = malloc( (number_elem/step)  * size );	
	}	
	int i = 0;
	for( i =0; i*step < number_elem; i++){
		fprintf(stdout, "sub_sampling_step : assigning data ( %d ). \n", i * step * size );
		assign( *dst + i*size, src + i * step * size );		
	}

	fprintf(stdout, "sub_sampling_step : leaving function. \n");

	return 0;
}

int sub_sampling_step_polar( complex_polar_t ** dst, complex_polar_t * src, int number_elem, int step){
	return  sub_sampling_step( (void **) dst, src, number_elem, step, sizeof(complex_polar_t), (void (*)( void *, void *) ) assign_complex_polar_ptr );
}

int sub_sampling_step_cart( complex_cart_t ** dst, complex_cart_t * src, int number_elem, int step){
	return  sub_sampling_step( (void **) dst, src, number_elem, step, sizeof(complex_cart_t), (void (*)( void *, void *) ) assign_complex_cart_ptr );
}

double window_rectangular( double x, int N ){
	if ( x >= 0.0f && x <= (double) N - 1.0f )
		return 1.0f;
	return 0.0f;
}
double window_welch( double x, int N ){
	return 1.0f - pow( (( x -0.5f * ((double) N - 1.0f ) ) / (0.5f * ( (double) N + 1.0f )  ) ), 2.0f ) ;
}
double window_triangular( double x, int N ){
	return  (2.0f / ((double) N - 1.0f) ) * ( (double) N / 2.0f - fabs( x - (float) N /2.0f ) );
}
double window_hann( double x, int N){
	return 0.5f*(1.0f - cos( 8.0f * atan(1.0f) * x / (double) N - 1.0f ) );
}
double window_hamming( double x, int N){
	return 0.54f - 0.46 * cos( 8.0f * atan(1.0f) * x / (double) N - 1.0f );
}
int double_array_through_window( double ** dst, double * src, int number_elem, double (*window)(double, int) ){
	return arb_array_through_window( (void **) dst, src, number_elem, 
					sizeof(double ),
					window,
					assign_double,
					mult_double );

}
int assign_double( void * dst, void * src ){
	*((double *) dst) = *((double *) src);
	return 0;
}
int mult_double( void * dst, double src ){
	*((double *) dst) *= src;
	return 0;
}
int cart_array_through_window( complex_cart_t ** dst, complex_cart_t * src, int number_elem, double (*window)(double, int) ){
	if(*dst == (complex_cart_t * ) NULL){
		*dst = malloc( number_elem * sizeof(complex_cart_t) );
		if(*dst == (complex_cart_t * )  NULL){
			fprintf(stderr, "array_through_window : Error allocating memory.\n");
			return -1;
		}
	}

	int i = 0;
	for(i = 0; i < number_elem; i++){
		(*dst)[i].real = src[i].real * window(i, number_elem);
		(*dst)[i].im = src[i].im * window(i, number_elem);
	}
}
int arb_array_through_window( void ** ret, void * array, int number_elem, size_t elem_size, double (*window)(double, int), int (*assign)(void *, void *), int (*mult)( void *, double) ){
	if(*ret == NULL){
		*ret = malloc( number_elem * elem_size );
		if(*ret == NULL){
			fprintf(stderr, "array_through_window : Error allocating memory.\n");
			return -1;
		}
	}

	int i = 0;
	for(i = 0; i < number_elem; i++){
		assign( *ret + i * elem_size, array + i * elem_size);
		mult( *ret + i *elem_size, window((double) i, number_elem) );
	}
	return 0;
}

int cart_array_through_window_arb( complex_cart_t ** ret, complex_cart_t * array, int N, double (*window)(double, int) ){
	return arb_array_through_window( (void **) ret, array, N, 
					sizeof(complex_cart_t ),
					window,
					assign_complex_cart_ptr_void,
					mult_scalar_complex_cart );

}

int array_2d_through_window_arb( void *** dst, void ** src, int N, int M, size_t elem_size, 
	       			double (*window)(double, int), int (*mult)(void *, double)){
 	
	int i, j;
	*dst = (void **)  malloc( N * sizeof( void *) );

	for(i = 0; i < N; i++){
		(*dst)[i] = malloc( N * elem_size );
		if( (*dst)[i] == NULL){
			fprintf(stderr, "array_2d_through_window_arb : memory allocation failed.\n");
			return -1;
		}
		
		cart_array_through_window_arb( (*dst)[i], *(src + i), M, window);	
	}
	for(j = 0; j < M; j++){
		for( i = 0; i < N; i++){
			mult( (*dst)[j] + i * elem_size, window( (double) j, N) );
		}
	}

	return 0;
}

