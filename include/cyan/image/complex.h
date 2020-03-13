#ifndef COMPLEX_H
#define COMPLEX_H


typedef struct s_complex_polar_t{
	double power;
	double phase;
}complex_polar_t;

typedef struct s_complex_cart_t{
	double real;
	double im;
}complex_cart_t;

complex_polar_t * unity(int, int);

double norm_complex_cart( complex_cart_t );
double power_complex_cart( complex_cart_t z);
double phase_complex_cart( complex_cart_t);

void * polar_to_cart( complex_cart_t *, complex_polar_t);
void * cart_to_polar( complex_polar_t *, complex_cart_t);

void * assign_complex_polar( complex_polar_t *, complex_polar_t);
complex_polar_t * cart_array_to_polar( complex_cart_t * cart_array, int n);
complex_cart_t * polar_array_to_cart( complex_polar_t * polar_array, int n);


complex_cart_t * add_complex_cart(complex_cart_t * result, complex_cart_t z1, complex_cart_t z2);
complex_cart_t * substract_complex_cart(complex_cart_t * result, complex_cart_t z1, complex_cart_t z2);	

void * flip_cart(complex_cart_t * z);
void * flip_polar(complex_polar_t * z);
	
double mult_complex_polar( complex_polar_t *, complex_polar_t, complex_polar_t);
void * mult_complex_cart_t( complex_cart_t *, complex_cart_t, complex_cart_t);

double energy_complex_cart( complex_cart_t z );

double zero(complex_cart_t);
double sum(complex_cart_t z);
double log_power_complex_cart(complex_cart_t );


#endif
