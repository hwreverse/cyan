#ifndef CYAN_IO_H
#define CYAN_IO_H

#define IMAGE_T 0
#define CLOUD_T 1

int   save( int filetype, void* obj, char* filename ) ;
void* load( int filetype, char* filetype, int* result ) ;





int image_save_ppm(image_t* img, char* filetype ) ;
image_t* image_load_ppm(char* filetype , int* result ) ;


#endif
