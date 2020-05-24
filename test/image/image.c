#include <stdio.h>
#include <cyan/image/image.h>


int main( int argc, char** argv, char* envv ) {

    int i,j,k ;
    image_t* image ; 
    image = image_new( 255, 255, 0) ;
    image_save(image, "./output.image.cyan") ;    
    image_free( image) ;
    
    return 0 ;
}

