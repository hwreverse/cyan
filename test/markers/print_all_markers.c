#include <stdio.h>
#include <cyan/image.h>


int main( int argc, char** argv, char* envv ) {

    int i, j ;
    int result ;
    image_t* image ; 
    
    if (argc != 2 ) {
        fprintf(stderr,"Usage : %s output_file.ppm\n", argv[0] ) ;
       return -1 ;
    }
    
    image = image_new(640, 480) ;
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
    }}

    image_add_marker_uv ( image, 100.0, 100.0 ) ;
    image_add_marker_uv ( image, 50.0 , 20.0 ) ;
    image_add_marker_uv ( image, 320.0, 240.0 ) ;

    image_print_all_markers( image, 5, 0.0, 0.0, 0.0 ) ;

    // result = image_save( image, argv[1] ) ; 
    // if (result != 0) {
    //    fprintf(stderr, "cannot save file\n") ;
    //    return -3 ;
    //}
    image_free( image) ;
    return 0 ;
}

