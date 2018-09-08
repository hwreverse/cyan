#include <stdlib.h>
#include <stdio.h>

#include <vision/pinhole.h>

pinhole_t* pinhole_new() {
    pinhole_t* cam ;
    cam = (pinhole_t*) malloc ( sizeof( pinhole_t ) ) ;
    if ( cam == (pinhole_t*) NULL ) {
        fprintf(stderr, "pinhole_new: allocation error\n") ;
        return NULL ;
    }

    // TODO init des parametres de camera pour une cam unitaire

    return ( pinhole_t* ) cam ;
}
