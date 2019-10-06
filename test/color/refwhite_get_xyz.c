#include <stdio.h>
#include <cyan/color/color.h>


int main( int argc, char** argv, char* envv ) {

    int w ;
    char name[255] ;
    double X,Y,Z ;

    for( w=0; w<11;w++) {
    refwhite_get_name( w, name, 255 ) ; 
    refwhite_get_xyz( w, &X, &Y, &Z ) ;
    printf ( "%s:\n\t{%lf , %lf , %lf } \n", name, X, Y, Z ) ;
    
    }
    return 0 ;
}

