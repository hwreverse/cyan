#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#include <onevision/structs/kdtree.h>

int* kdtree_build( int nb_points, void* points ) {
	int i ;
	int size ;
	int depth ;
	int* tab_indices = NULL ;
	
	depth = (int) ceil(((log( nb_points+1.0)/log(2.0))-1.0)) ; 
	size = pow(2.0,depth+1)-1 ;

	printf("nb_points: %d\n", nb_points ) ;
	printf("depth: %d\n", depth) ;
	printf("array size: %d\n", size);

	tab_indices = malloc(size * sizeof(int));
	if (tab_indices == NULL) {
		errno = ENOMEM;
		return NULL;
	}

	for (i = 0; i < size; i++) {
		if (i<nb_points)
			tab_indices[i] = i;
		else
			tab_indices[i] = -1 ;
	}







	return tab_indices ;
}

