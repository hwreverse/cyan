#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <cyan/color/color.h>
#include <cyan/image/image.h>
#include <cyan/image/load_png.h>

#include "transforms.h"

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

