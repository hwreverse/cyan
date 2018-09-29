#include <image/image.h>
#include <color/color.h>
#include <io/image_io.h>


int main( int argc, char** argv, char* envv ) {

    int i, j ;

    image_t* image = image_new( 640, 480, COLORTYPE_RGB ) ;
    color_t* couleur ;

    for ( i=0; i<image->rows; i++ )
    for ( j=0; j<image->cols; j++ ) {
        couleur = image_get_pixel_pointer( image, j, i ) ;
        couleur->coords[0] = 1.0 - ((float)i) /((float) image->rows) ;
        couleur->coords[1] = 1.0 - ((float)j) /((float) image->cols) ;
    couleur->coords[2] = 1.0 - ((float)i*j)/((float) image->rows * image->cols) ;
    }

    image_save_ppm( image, "./test.ppm") ; 

    image_free( image) ;

    return 0 ;
}

