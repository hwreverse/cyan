#ifndef CYAN_KDTREE_H
#define CYAN_KDTREE_H

#include <3dmodel/point.h>

int* kdtree_build( int nb_points, void* points ) ;
int kdtree_search_nearest( int* kdtree, void* point) ;




#endif
