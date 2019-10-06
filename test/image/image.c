#include <stdio.h>
#include <cyan/image/image.h>


int main( int argc, char** argv, char* envv ) {

    int i,j,k ;
    image_t* image ; 
   
    for (k=0;k<1000;k++) {
        image = image_new(1280, 1024) ;
        if ( image == NULL ) {
            fprintf(stderr,"image allocation failed\n") ;
            return -2 ;
        }
        for ( j=0; j<image->rows; j++ ) {
            for ( i=0; i<image->cols; i++ ) {
                int coord ;
                coord = i+j*image->cols ;
                image->X[coord] = 0.0;
                image->Y[coord] = 1.0 ;
                image->Z[coord] = 0.0 ;
            }
        }
        image_free( image) ;
    }
    return 0 ;
}

