#include <image/image.h>
#include <color/color.h>
#include <io/image_io.h>


int main( int argc, char** argv, char* envv ) {

    int result ;
    image_t* image = image_load_ppm( "./Lenna.ppm", &result ) ;
    image_free( image) ;

    return 0 ;
}

