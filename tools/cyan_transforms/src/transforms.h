#ifndef TRANSFORMS_H
#define TRANSFORMS_H

typedef struct s_complex_polar_t{
	double power;
	double phase;
}complex_polar_t;

typedef struct s_complex_cart_t{
	double real;
	double im;
}complex_cart_t;

complex_polar_t * FFT_1D( complex_polar_t *, complex_polar_t *, int);

image_t * color2grey(image_t *);

float norm_2_sq_4_f( float, float , float , float );
float dot_product_4_f(	float, float, float, float, float, float, float, float );

void * assign_complex_polar( complex_polar_t *, complex_polar_t);

complex_cart_t * add_complex_cart(complex_cart_t * result, complex_cart_t z1, complex_cart_t z2);

double mult_complex_polar( complex_polar_t *, complex_polar_t, complex_polar_t);
void * mult_complex_cart_t( complex_cart_t *, complex_cart_t, complex_cart_t);

double norm_complex_cart( complex_cart_t );
double phase_complex_cart( complex_cart_t);

void * polar_to_cart( complex_cart_t *, complex_polar_t);
void * cart_to_polar( complex_polar_t *, complex_cart_t);
#endif
