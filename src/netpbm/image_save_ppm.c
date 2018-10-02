#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <color/color.h>
#include <image/image.h>
#include <io/image_io.h>

#include <netpbm/pam.h>

#include "../config.h"

int image_save_ppm(image_t * img, char *filename) {

    int i,j ;
    FILE* fichier ;

    if ( img == NULL ) {
        fprintf(stderr,"image_save_ppm: cannot save NULL image \n");
        return -1 ;
    }

    if ((img->rows==0)||(img->cols==0)) {
        fprintf(stderr,"image_save_ppm: one of the dimension of the image is zero\n");
        return -2 ;
    }

    fichier = fopen( filename, "w") ;
    if ( fichier == NULL ) {
        fprintf(stderr, "image_save_ppm: cannot open file %s for writing \n", filename) ;
        return -3 ;
    }

    pnm_writepnminit( fichier, img->cols, img->rows, (xelval) 255, PPM_TYPE, 1 );  

    xel* pixel_row = ppm_allocrow( img->cols ) ;

    for (i=0; i<img->rows;i++) {
        for (j=0;j<img->cols;j++) {
            pixel_row[j].r = (int) (255.0 * img->pixels[i*img->cols+j].coords[0]) ;
            pixel_row[j].g = (int) (255.0 * img->pixels[i*img->cols+j].coords[1]) ;
            pixel_row[j].b = (int) (255.0 * img->pixels[i*img->cols+j].coords[2]) ;

        }
        pnm_writepnmrow( fichier, pixel_row, img->cols, (xelval) 255, PPM_TYPE, 1 );
    }

    fclose(fichier) ;

}
