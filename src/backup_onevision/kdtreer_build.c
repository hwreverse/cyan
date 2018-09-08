#define _GNU_SOURCE

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <onevision/structs/kdtreer.h>


int kdtreer_build_rec( kdtreer_node_t **tree, int cutting_dim, int nb_points, int *tab_indices, point_t *points);



int kdtreer_build(kdtreer_node_t **tree, int nb_points, point_t *points)
{
	int i;
	int depth;
	int *tab_indices = NULL;

	if (*tree != NULL) {
		errno = EINVAL;
		return 0;
	}

	tab_indices = malloc(nb_points * sizeof(int));
	if (tab_indices == NULL) {
		errno = ENOMEM;
		return 0;	// FIXME
	}

	for (i = 0; i < nb_points; i++) {
		tab_indices[i] = i;
	}

	depth = kdtreer_build_rec(tree, 0, nb_points, tab_indices, points);
	
	free(tab_indices);

	return depth;
}



int compare_fct( const void* arg1, const void* arg2, void* data ) {
	
	const int* iarg1 = arg1 ;
	const int* iarg2 = arg2 ;
	point_t* points = ((void**)data)[0] ;			// FIXME Cas du -1 ??????
	int* cutting_dim = ((void**)data)[1] ;
	return ( points[*iarg1].coords[*cutting_dim] < points[*iarg2].coords[*cutting_dim] ) ;
}


int kdtreer_build_rec(kdtreer_node_t **tree, int dimension, int nb_points, 
			 int *tab_indices, point_t *points) {

	kdtreer_node_t* new_node ;
	int pivot ;
	int left_depth ;
	int right_depth ;
	int cutting_dim ;
	void** data ;
	data[0] = points ;
	data[1] = &cutting_dim ;

	if ( nb_points == 0 ) {
		(*tree) = NULL  ;
		return 0 ;
	}

	new_node = malloc( sizeof( kdtreer_node_t ) ) ;
	if ( new_node == NULL ) {
		errno = ENOMEM ;
		return 0 ;		// FIXME should warn the caller in some way
	}

	qsort_r( tab_indices, nb_points, sizeof(int), compare_fct, points ) ;
	
	pivot = (nb_points/2) ;
	cutting_dim = (dimension+1)%3 ;
	
	new_node->point_id = pivot ;
	*tree = new_node ;	

	left_depth = kdtreer_build_rec( &(new_node->left),   cutting_dim, 
					pivot, tab_indices, points ) ;
	right_depth = kdtreer_build_rec( &(new_node->right), cutting_dim, 
					nb_points-pivot, tab_indices+(pivot+1)*sizeof(int), points ) ;

	return 1 + (left_depth<right_depth)?right_depth:left_depth;
}
