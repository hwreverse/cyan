#ifndef CYAN_IMAGE_H
#define CYAN_IMAGE_H

/**
 * @defgroup image
 *
 * @brief Primitives pour le traitement d'images bitmap
 *
 * Ce module contient les structures et fonctions nécessaires pour
 * le traitement d'images stockées sous forme de grille 2D. La structure 
 * de base utilisée est image_t, qui permet de représenter un plan de pixels.
 *
 */

#include <stdlib.h>
#include <color.h>
#include <marker.h>

/**
 * \struct image_t 
 *
 * \brief Image de type bitmap
 *
 * image_t est une structure permettant de stocker un plan de pixels
 * dans le format colorimetrique de votre choix
 *
 * \ingroup image
 */

typedef struct {

	int rows ;                        ///< Nombre de lignes du bitmap
	int cols ;                        ///< Nombre de colonnes du bitmap 
	cyan_colorspace_t colorspace;     ///< Colorspace used
	color_t* pixels ;
	
	size_t data_size ;
	void*    data ;

	int nb_markers ;
	marker_t* markers ;
    int tab_marker_size ;   

} image_t ;

image_t* image_new( int cols, int rows, cyan_colorspace_t colorspace ) ;
void     image_free( image_t* ) ;

int image_allocate_data_default  ( image_t*, size_t size, void* default_data ) ;

int image_allocate_data_fct( image_t*, size_t datasize, 
			     int (*fill_fct) (image_t*, int, int, void*),
			     void* context ) ;

int image_import_data   ( image_t*, size_t data_size, void* data ) ;

void*    image_get_data_pointer  ( image_t*, int i, int j ) ;
color_t* image_get_pixel_pointer ( image_t*, int i, int j ) ;

image_t* image_clone ( image_t* ) ;
void image_resize ( image_t*, int rows, int cols ) ;
void image_apply_fct ( image_t*, void (*fct)( image_t*,int i, int j, void* ctx),
			void* context ) ;

int image_add_marker( image_t*, marker_t ) ;
int image_add_marker_uv ( image_t*, double U, double V ) ;
int image_del_marker( image_t*, int position) ;
int image_print_all_markers( image_t*, int size, float colorcmp1, float colorcmp2, float colorcmp3 ) ;


int image_save_ppm(image_t* img, char* filename ) ;
image_t* image_load_ppm(char* filename , int* result ) ;

#endif
