#include <stdio.h>
#include <color/color.h>

int main ( int argc, char** argv, char** envv ) {

    color_t rgb ;
    color_t hsv ;

    hsv.coords[HSV_H] = 174.8 ;
    hsv.coords[HSV_S] = 0.281 ;
    hsv.coords[HSV_V] = 0.645 ;

    fprintf( stdout, "hsv2rgb(%f, %f, %f) \n", hsv.coords[HSV_H],hsv.coords[HSV_S], hsv.coords[HSV_V]);
    hsv2rgb( hsv, &rgb ) ;
    fprintf( stdout, "\t R : %f ( %f ) \n", rgb.coords[RGB_R], 0.464 ) ;
    fprintf( stdout, "\t G : %f ( %f ) \n", rgb.coords[RGB_G], 0.645 ) ;
    fprintf( stdout, "\t B : %f ( %f ) \n", rgb.coords[RGB_B], 0.629 ) ;
    fprintf( stdout, "\n") ;

    fprintf( stdout, "hsv2rgb_(%f, %f, %f) \n", hsv.coords[HSV_H],hsv.coords[HSV_S], hsv.coords[HSV_V]);
    hsv2rgb_( &hsv ) ; 
    fprintf( stdout, "\t R : %f ( %f ) \n", hsv.coords[RGB_R], 0.464 ) ;
    fprintf( stdout, "\t G : %f ( %f ) \n", hsv.coords[RGB_G], 0.645 ) ;
    fprintf( stdout, "\t B : %f ( %f ) \n", hsv.coords[RGB_B], 0.629 ) ;

    return 0 ;
}
