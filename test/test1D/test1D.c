#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <cyan/image/image.h>
#include <cyan/image/sampling.h>

#include <cyan/color/color.h>

#include <cyan_fileio/save_ppm.h>

int main( int argc, char** argv, char* envv ) {

	int len = 420;
	int i = 0;
	int scale = 255;
	double array[len];

	for(i=0; i < len; i++)
		array[i] = cos( 2 * M_PI * (double) i / (double) len );
	
	normalize_and_scale_double_array(array, len, (double) scale);
	
	int * int_array = NULL;
	double_array_to_int_array( &int_array, array, len);
	
	image_t * image = image_new_empty(len, scale);
	
	color_t color;
	color_assign( &color, 1.0f, 1.0f, 1.0f, 0);

	image_set_color_to_coordinates(image, color, int_array, 1);

	image_save_ppm(image, "image.ppm");
	
	image_free(image);
	free(int_array);

	return 0;

}
