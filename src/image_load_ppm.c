#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <color/color.h>
#include <image/image.h>
#include <io/image_io.h>

#include "config.h"

typedef struct {
    FILE*   handle ;
    char*   line ;
    size_t  allocated_mem ;     // taille allouée pour le tableau line
    ssize_t line_length ;       // nbre de caractères contenus dans line ( incluant \n )
    int first_token ;
} ppm_file_t ;

ppm_file_t* ppm_file_new( char* filename ) ;
void ppm_file_free( ppm_file_t* fichier ) ;
ssize_t ppm_file_read_line( ppm_file_t* fichier ) ;
char* ppm_file_get_next_token( ppm_file_t* fichier ) ;

ppm_file_t* ppm_file_new( char* filename ) {
    ppm_file_t* fichier = malloc ( sizeof(ppm_file_t) ) ;
    fichier->handle = fopen( filename, "r" ) ;
    if ( fichier->handle == (FILE*) NULL ) {
        return NULL ;
    }
    fichier->line = (char*) NULL ;
    fichier->allocated_mem = (size_t) 0 ;
    fichier->line_length = (ssize_t) 0 ;
    fichier->first_token = 1 ;
    return fichier ;
}

void ppm_file_free( ppm_file_t* fichier ) {
    fclose( fichier->handle ) ;
    if ( line != (char*) NULL )
        free( line ) ;
    free(fichier) ; 
}

ssize_t ppm_file_read_line( ppm_file_t* fichier ) {
    fichier->first_token = 1 ;
    fichier->line_length = getline( &(fichier->line), &(fichier->allocated_mem), fichier->handle);
    if ( fichier->line_length > 0 )
        if ( fichier->line[0] == '#' )
            return ppm_file_read_line(fichier) ;
    return (int) fichier->line_length ;
}

char* ppm_file_get_next_token( ppm_file_t* fichier ) {
    char delimiters[3] = { ' ', '\t', '\0' }
    char* chaine ;
    char* result ;
    if (fichier->first_token)
        chaine = fichier->line ;
    else
        chaine = NULL ;
    result = strtok( chaine, delimiters ) ;
    if ( result == NULL ) {
        ppm_file_read_line( fichier ) ;
        result = ppm_file_get_next_token(fichier ) ;
    }
    return result ;
}


image_t* image_load_ppm(char* filename , int* result ) {

    int width ;
    int height ;
    int maxvalue ;
    image_t* img ;

    

    // voir avec la fonction getline, dans stdio.h


    fclose( handle ) ;

}


