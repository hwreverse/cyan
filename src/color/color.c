#include <stdlib.h>
#include <stdio.h>

#include <cyan/color/color.h>


int color_assign( color_t * dst, double X, double Y, double Z, int monochrome ){
	if(dst == NULL){
		fprintf(stderr, "assign_color: dst is a NULL pointer\n");
		return -1;
	}
	dst->monochrome = monochrome;
	if( monochrome ){		//Quite unclear what to do with monochrome, so i'm doing this...
		dst->Y = Y;
		return 0;
	}
	dst->X = X;
	dst->Y = Y;
	dst->Z = Z;
	
	return 0;
}
