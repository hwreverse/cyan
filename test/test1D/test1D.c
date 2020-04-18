#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <cyan/image/image.h>
#include <cyan/image/sampling.h>

#include <cyan_fileio/save_ppm.h>

int main( int argc, char** argv, char* envv ) {

	int len = 420;
	int i = 0;
	int scale = 255;
	double array[len];

	for(i=0, fprintf(stdout, "array : " ); i < len; i++){
		array[i] = cos( 2 * M_PI * (double) i / (double) len );
		fprintf(stdout, "%f\t", array[i]);
	}
	fprintf(stdout, "\n");

	normalize_and_scale_double_array(array, len,(double) scale);
	for(i=0, fprintf(stdout, "array : " ); i < len; i++){
		fprintf(stdout, "%f\t", array[i]);
	}
	fprintf(stdout, "\n");

	int * int_array = NULL;
	double_array_to_int_array( &int_array, array, len);
	for(i=0, fprintf(stdout, "array : " ); i < len; i++){
		fprintf(stdout, "%d\t", int_array[i]);
	}
	fprintf(stdout, "\n");

	image_t * image = image_new_empty(len, scale);
	for( i = 0; i < len; i++){
		image->X[ len*(scale -int_array[ i ]) + i ] = 1.0f;
	}
	image_save_ppm(image, "image.ppm");

	image_free(image);
	free(int_array);

	return 0;

}
