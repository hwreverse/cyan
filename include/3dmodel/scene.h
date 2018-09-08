#ifndef CYAN_SCENE_H
#define CYAN_SCENE_H

#include <stdlib.h>
#include <algebra/transmatrix.h>

typedef enum { 
		UNKNOWN,
		SCENE,
		CLOUD,
		MESH,
		CAMERA
} primitive_t ;


typedef struct {

	int	display_aabb ;
	aabb_t	aabb ;
	int	display_frame ;
	size_t  data_size ;
	void*	data ;

} display_t ;


typedef struct scene_s {
	
	int	allocation_size ;
	int 	nb_objects ;

	void** 	   objects ;
	tmatrix_t* trans_matrices ;
	display_t* options ;

} scene_t ;


scene_t* scene_new( int allocation_size ) ;
void	 scene_free( scene_t* ) ;

int scene_add_object ( scene_t*, primitive_t, void* object, 
			tmatrix_t* trans_matrix, int display_aabb, 
			int display_frame, size_t datasize, void* data ) ;
			
int scene_del_object ( scene_t*, int object ) ;


#endif
