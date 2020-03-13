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

int sub_sampling_step( void * sample, void *  array, int length, size_t size, void (*assign)(void *, void *) ){
	
	if(sample == NULL){
		sample = malloc( length * size );
	}	

	int i = 0;
	for( i =0; i < length; i++){
		assign( sample + i * size,  array + i*size );
	}

	return 0;
}

