#ifndef CYAN_KDTREER_H
#define CYAN_KDTREER_H

#include <3dmodel/point.h>

typedef struct kdtreer_node_s {

	int point_id ;

	struct kdtreer_node_s*	left ;
	struct kdtreer_node_s*	right ;

} kdtreer_node_t ;

int kdtreer_build ( kdtreer_node_t**, int nb_points, point_t* points) ;
int kdtreer_search_nearest ( kdtreer_node_t* tree, point_t* point ) ;

#endif

