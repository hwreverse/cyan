#ifndef SAMPLING_H
#define SAMPLING_H

void * sub_sampling_step( void *, void *, int, int, size_t, void (*)(void *, void * ) );

complex_polar_t * sub_sampling_step_polar(complex_polar_t *, complex_polar_t *, int, int);
complex_cart_t * sub_sampling_step_cart(complex_cart_t *, complex_cart_t *, int, int);

double window_rectangular( double x, int N );
double window_welch( double x, int N );
double window_triangular( double x, int N );
double window_hann( double x, int N);
double window_hamming( double x, int N);

int cart_array_through_window( complex_cart_t * ret, complex_cart_t * array, int number_elem, double (*window)(double, int) );
void * arb_array_through_window( void * ret, void * array, int number_elem, size_t elem_size, double (*window)(double, int), int (*assign)(void *, void *), int (*mult)( void *, double) );
void * cart_array_through_window_arb( complex_cart_t * ret, complex_cart_t * array, int N, double (*)(double, int) );

#endif

