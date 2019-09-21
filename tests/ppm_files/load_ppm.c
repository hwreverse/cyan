#include <stdio.h>
#include <image.h>


int main( int argc, char** argv, char* envv ) {

    int result ;
    image_t* image ;
    
    if ( argc != 3 ) {
        fprintf(stderr, "Usage : %s input_file output_file.ppm \n", argv[0] ) ;
        return -1 ;
    }

    image = image_load_ppm( argv[1], &result ) ;
    if ( image == NULL ) {
        fprintf(stderr, "Image could not be loaded\n") ;
        return -2 ;
    }

    result=image_save_ppm( image, argv[2]) ;
    if (  result != 0 ) {
        fprintf(stderr, "Cannot save file\n");
        return -3 ;
    }

    image_free( image) ;

    return 0 ;
}

