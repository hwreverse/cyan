#include <stdio.h>
#include <cyan/color/color.h>


int main( int argc, char** argv, char* envv ) {

    int rgb ;
    char name[255] ;
    double X,Y,Z ;
    double R,G,B ;

    R = 0.7 ;
    G = 0.4 ;
    B = 0.2 ;

    for( rgb=0; rgb<16;rgb++) {
    rgb_get_name( rgb, name, 255 ) ; 
    RGB_to_XYZ( rgb, R,G,B, &X, &Y, &Z ) ;
    printf ( "%s:\n\t{%lf , %lf , %lf } \n", name, X, Y, Z ) ;
    
    }
    return 0 ;
}

