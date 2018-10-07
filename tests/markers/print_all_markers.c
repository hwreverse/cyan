#include <stdio.h>
#include <image/image.h>
#include <io/image_io.h>


int main( int argc, char** argv, char* envv ) {

    int i, j ;
    int result ;
    image_t* image ; 
    color_t* couleur ;
    
    if (argc != 2 ) {
        fprintf(stderr,"Usage : %s output_file.ppm\n", argv[0] ) ;
       return -1 ;
    }
    
    image = image_new( 640, 480, COLORTYPE_RGB ) ;
    if ( image == NULL ) {
        fprintf(stderr,"image allocation failed\n") ;
        return -2 ;
    }

    for ( i=0; i<image->rows; i++ )
    for ( j=0; j<image->cols; j++ ) {
        couleur = image_get_pixel_pointer( image, j, i ) ;
        couleur->coords[0] = 1.0 ;
        couleur->coords[1] = 1.0 ;
        couleur->coords[2] = 1.0 ;
    }

    image_add_marker_uv ( image, 100.0, 100.0 ) ;
    image_add_marker_uv ( image, 50.0 , 20.0 ) ;
    image_add_marker_uv ( image, 320.0, 240.0 ) ;

    image_print_all_markers( image, 5, 0.0, 0.0, 0.0 ) ;

    result = image_save_ppm( image, argv[1] ) ; 
    if (result != 0) {
        fprintf(stderr, "cannot save file\n") ;
        return -3 ;
    }
    
    image_free( image) ;

    return 0 ;
}

