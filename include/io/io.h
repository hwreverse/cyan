#ifndef CYAN_IO_H
#define CYAN_IO_H

#define IMAGE_T 0
#define CLOUD_T 1

int   save( int filetype, void* obj, char* filename ) ;
void* load( int filetype, char* filetype, int* result ) ;


#endif
