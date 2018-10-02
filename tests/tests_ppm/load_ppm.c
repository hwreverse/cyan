#include <stdio.h>
#include <image/image.h>
#include <color/color.h>
#include <io/image_io.h>


int main( int argc, char** argv, char* envv ) {

    int result ;
    image_t* image = image_load_ppm( "./lena.ppm", &result ) ;
    if ( image == NULL ) {
        fprintf(stderr, "Image could not be loaded\n") ;
        return -1 ;
    }

    image_save_ppm( image, "./test.ppm") ;

    image_free( image) ;

    return 0 ;
}

