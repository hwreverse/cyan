#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <color/color.h>
#include <image/image.h>
#include <io/image_io.h>

#include <netpbm/pam.h>
    
#include "../config.h"

image_t *image_load_ppm(char *filename, int *result) {
	image_t *img;
    int rows ;
    int cols ;
    xelval maxval ;
    int format ;
    int i,j ;
    gray r,g,b ;
    
    pm_init("cyan", 0);

    FILE *fichier = fopen(filename, "r");
    if(fichier == NULL) {
        fprintf(stderr, "Cannot open file \n") ;
        *result = 0 ;
        return NULL;
    }

    pnm_readpnminit( fichier, &cols, &rows, &maxval, &format ); 

    printf("%d x %d \n", cols, rows ) ;
    printf("Maxval : %d \n", maxval ) ;
    printf("Format : %s \n", (char*) &format ) ;

    pixel * pixel_row = ppm_allocrow(cols);
    
    img = image_new( cols, rows, COLORTYPE_RGB ) ; 
    if ( img == NULL ) {
        fprintf(stderr, "Cannot allocate image \n" ) ;
        *result = 0 ;
        return NULL ;
    }

    for (i=0; i<rows; i++) {
        ppm_readppmrow(fichier, pixel_row, cols, maxval, format);
        for (j=0;j<cols; j++){
            r = pixel_row[j].r ;
            g = pixel_row[j].g ;
            b = pixel_row[j].b ;
        }
    }

    fclose(fichier) ;
    
    return img;
}
