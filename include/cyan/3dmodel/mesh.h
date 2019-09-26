#ifndef CYAN_MESH_H
#define CYAN_MESH_H

#include <stdlib.h>
#include <algebra/vector.h>

// FIXME le tableau normals pourrait etre une map 2D, comme pour les textures. A envisager
// FIXME les coordonnées des vertex dans les textures ont été oubliées.


typedef struct mesh_s {

	cloud_t* 	cloud ;

	int  		nb_faces ;
	int* 		faces ;

	vector3d_t*     normals ;	// normal for each point

	int		color_type ;		// color for each face
	color_t*	colors ;

	size_t 		data_size ;		// data for each face
	void* 		data ;
	
	int		texture_encoding ;	// texture for each face
	size_t		texture_size ;
	void*		textures ;

	void*		octree ;		// Gestion des collisions face ?
	void* 		manifold ;		// Gestion des remaillages ?
	
} mesh_t ;

mesh_t* mesh_new( cloud_t* ); 
void mesh_free( mesh_t* ) ;

int mesh_allocate_color( mesh_t*, int color_type, color_t* ) ;
int mesh_allocate_data ( mesh_t*, size_t data_size, void* data ) ;
int mesh_allocate_textures ( mesh_t*, int texture_encoding, size_t texture_size ) ;

int  mesh_add_point ( mesh_t* mesh, point_t ) ;
void mesh_remove_point ( mesh_t, int point ) ;

int mesh_add_face ( mesh_t* mesh, int p1, int p2, int p3 ) ;
void mesh_remove_face ( mesh_t* mesh, int face ) ;

void* mesh_get_data_pointer ( mesh_t*, int face ) ;
color_t* mesh_get_color_pointer ( mesh_t*, int face ) ;
void* mesh_get_texture_pointer ( mesh_t*, int face ) ;
vector3d_t* mesh_get_normal_pointer ( mesh_t*, int point ) ;

mesh_t* mesh_clone ( mesh_t* ) ;
mesh_t* mesh_merge ( mesh_t*, mesh_t* ) ;

int mesh_build_octree    ( mesh_t* ) ;
int mesh_build_manifold  ( mesh_t* ) ;
int mesh_build_normals   ( mesh_t* ) ;

#endif

