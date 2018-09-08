#include <stdio.h>
#include "mafct.h"

int main( int argc, char** argv, char** envv ) {

    int A ;
    int B ;

    A = 1 ;
    B = 2 ;

    printf("%d\n", mafct(A,B) ) ;
    printf("coucou\n") ;

    return 0 ; 
}
