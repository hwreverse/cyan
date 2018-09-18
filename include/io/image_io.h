#ifndef CYAN_IMAGE_IO_H
#define CYAN_IMAGE_IO_H

#include <image/image.h>

int image_save_ppm(image_t* img, char* filename ) ;
image_t* image_load_ppm(char* filename , int* result ) ;

#if IMAGEMAGICK

// FIXME ajout ici des imports/exports pour le type image

#endif


#endif
