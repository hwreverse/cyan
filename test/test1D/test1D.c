#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <cyan/image/sampling.h>


int main( int argc, char** argv, char* envv ) {

	int len = 43;
	int i = 0;
	double array[len];

	for(i=0, fprintf(stdout, "array : " ); i < len; i++){
		array[i] = (double) i - 42.0f /2.0f;
		fprintf(stdout, "%f\t", array[i]);
	}
	fprintf(stdout, "\n");

	normalize_and_scale_double_array(array, len, 21.0f);
	for(i=0, fprintf(stdout, "array : " ); i < len; i++){
		fprintf(stdout, "%f\t", array[i]);
	}
	fprintf(stdout, "\n");
	
	return 0;

}
