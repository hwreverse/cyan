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


#endif
