#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

#include <cyan/color/color.h>
#include <cyan/image/image.h>
#include <cyan/image/load_png.h>
#include <cyan/image/transforms.h>

complex_polar_t * unity(int k, int N){
	
	complex_polar_t * unit = (complex_polar_t *) malloc(sizeof(complex_polar_t));
	
	unit->power = (double) 1.0f;
	//Rk: 4*atan(1) = 2 * pi
	unit->phase = 2.0 * (4 * atan( (double) 1.0f)) *  (double) k / (double) N;

	//fprintf(stdout, "unit phase (k, %d, N, %d) : %f\n", k, N, unit->phase);
	return unit;
}

//The function FFT_1D() is implemented as the procedure FFT(A) in the following link
//http://people.scs.carleton.ca/~maheshwa/courses/5703COMP/16Fall/FFT_Report.pdf
//FFT_1D computes (and returns in f) the 1D Fast Fourier Transform of the sequence f of 2^n elements (i.e. {f(k)}_{k=0,...,2^n}
//At this stage complexity is N * lgN in size and computations, it can be made in 2N size
static complex_polar_t * FFT_1D( complex_polar_t * f, complex_polar_t * buffer, int n){
	
	int N = pow(2, n);
	if(buffer == NULL){
		fprintf(stdout, "FFT_1D : Allocating the buffer (of size N : %d).\n", N);
		buffer = (complex_polar_t *) malloc( N * sizeof(complex_polar_t));
	}
	if(n == 0)
		return f;
	
	complex_polar_t * W_N = unity(1, N);
	complex_polar_t * W = unity(0, 1);
	
	complex_polar_t * temp_polar = unity(0, 1);	
	complex_cart_t  *temp_cart1= malloc(sizeof(complex_cart_t));
	complex_cart_t  *temp_cart2= malloc(sizeof(complex_cart_t));

	complex_cart_t * f_temp_cart = malloc(sizeof(complex_cart_t));
	int i;
	//Rearranging f with the N/2 even elems, then the N/2 odd elems
	//(A_even)_{2k} corresponds to f[0, N/2-1]
	//(A_odd)_{2k+1} corresponds to f[N/2, N-1] 
	
	complex_polar_t order_buffer[N];
	for(i = 0; i< N/2; i++){
		order_buffer[i] = f[2*i]; //to N-2
		order_buffer[N/2+i] = f[2*i + 1];	
	}
/*	for(i=0; i<N/2; i++){
		f[N/2+i] = order_buffer[ i];	
		//The following line is optional and makes it such that f and buffer contain the same elements
		//buffer[i] = f[i];	
	}*/
	//Computing odd and even fft in f
	//stores similarly as f
	//FFT_1D( f, buffer, n-1);	//f[0, N/2-1] is (Y_even)_k
	
	complex_polar_t * Y_even;
	complex_polar_t * Y_odd;
	Y_even = FFT_1D(order_buffer, NULL, n-1);
	Y_odd = FFT_1D(&(order_buffer[N/2]), NULL, n-1);
	
	//FFT_1D( &(f[ N/2 ]), &(buffer[ N/2 ]), n-1 ); //f[N/2, N-1] is (Y_odd)_k
	int j = 0;
	for(j = 0; j< N/2; j++)
	{
		//sorting values part
		mult_complex_polar(temp_polar, *W, Y_odd[ j]);	//temp_polar i.e W * Y_odd
		polar_to_cart(temp_cart1, *temp_polar);	//temp_cart 1 i.e W*Y_odd
		polar_to_cart(temp_cart2, Y_even[j]);	//temp_cart2 i.e. Y_even
		
		//Y(j) part

		add_complex_cart(f_temp_cart, *temp_cart1, *temp_cart2);
		cart_to_polar(&(buffer[j]), *f_temp_cart);
			
		//Y(j+N/2) part
		
		substract_complex_cart(f_temp_cart, *temp_cart2, *temp_cart1);
		cart_to_polar(&(buffer[j + N/2]),*f_temp_cart );
		
		//Updating phase factor
		//mult_complex_polar(temp_polar, *W, *W_N);

		W->phase += 2.0f * (4.0f * atan(1.0f)) / (double) N;	//Phase += 2*pi /N	
		//W->power = temp_polar->power;	
	}
	//double normalizer = 1.0f / pow(2.0f, n/2);
	return buffer;
}

//Takes as an input fourier_polar, the polar fourier coefficients and computes f_polar the reverse FT of fourier_polar
//
complex_polar_t * FFT_1D_reverse( complex_polar_t * fourier_polar, int n){

	complex_polar_t * f_polar;
	f_polar = FFT_1D(fourier_polar, NULL, n);

	return f_polar;
}

complex_cart_t * FFT_1D_reverse_cart_to_cart( complex_cart_t * fft, int n){
	complex_polar_t * fft_polar = NULL;
	int N = pow(2, n);
		
	fft_polar = cart_array_to_polar(fft, N);
	
	complex_polar_t * f_polar = NULL;
	
	f_polar = FFT_1D_reverse(fft_polar, n);
	unitary_ft_polar(f_polar, N);
	
	free(fft_polar);

	complex_cart_t * f_cart = NULL;
	f_cart = polar_array_to_cart(f_polar, N);

	free(f_polar);

	return f_cart;

}

complex_cart_t * FFT_1D_cart_to_cart( complex_cart_t * f, int n){
	complex_polar_t * f_polar = NULL;
	int N = pow(2, n);
		
	f_polar = cart_array_to_polar(f, N);
	
	complex_polar_t * fft_polar = NULL;

	fft_polar = FFT_1D(f_polar, NULL, n);
	unitary_ft_polar( fft_polar, N);
	
	free(f_polar);

	complex_cart_t * fft_cart = NULL;
	fft_cart = polar_array_to_cart(fft_polar, N);

	free(fft_polar);

	return fft_cart;


}

//unitary_ft_*() divide each coefficients inside *_array by 1/sqrt(N) in order to have a unitary fourier transform.
void * unitary_ft_polar(complex_polar_t * polar_array, int N){
	int i;
	for(i=0; i<N; i++)
		polar_array[i].power *= 1.0f/sqrt( (double) N);
}

void * unitary_ft_cart(complex_cart_t * cart_array, int N){
	int i;
	for(i=0; i<N; i++){
		cart_array[i].real *= 1.0f/sqrt( (double) N);
		cart_array[i].im *= 1.0f/sqrt( (double) N);
	}
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

double norm_complex_cart( complex_cart_t z){
	return sqrt(z.real*z.real + z.im*z.im);
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


