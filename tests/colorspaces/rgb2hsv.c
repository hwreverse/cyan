#include <stdio.h>
#include <cyan/color.h>

int main ( int argc, char** argv, char** envv ) {

    color_t rgb ;
    color_t hsv ;

    rgb.coords[RGB_R] = 0.563 ;
    rgb.coords[RGB_G] = 0.261 ;
    rgb.coords[RGB_B] = 0.539 ;


    fprintf(stdout, "rgb2hsv(%f, %f, %f) \n", rgb.coords[RGB_R],rgb.coords[RGB_G], rgb.coords[RGB_G]);
    rgb2hsv( rgb, &hsv ) ;
    fprintf(stdout, "\t H : %f ( %f ) \n", hsv.coords[HSV_H], 304.8 ) ;
    fprintf(stdout, "\t S : %f ( %f ) \n", hsv.coords[HSV_S], 0.537 ) ;
    fprintf(stdout, "\t V : %f ( %f ) \n", hsv.coords[HSV_V], 0.563 ) ;
    fprintf(stdout,"\n") ;

    fprintf(stdout, "rgb2hsv_(%f, %f, %f) \n", rgb.coords[RGB_R],rgb.coords[RGB_G], rgb.coords[RGB_G]);
    rgb2hsv_( &rgb ) ; 
    fprintf(stdout, "\t H : %f ( %f ) \n", rgb.coords[HSV_H], 304.8 ) ;
    fprintf(stdout, "\t S : %f ( %f ) \n", rgb.coords[HSV_S], 0.537 ) ;
    fprintf(stdout, "\t V : %f ( %f ) \n", rgb.coords[HSV_V], 0.563 ) ;

    return 0 ;
}
