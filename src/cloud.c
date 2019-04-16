#include "cloud.h"

cloud_t* cloud_new( int nb_points ) {
    cloud_t* tmp ;
    tmp = (cloud_t*) malloc ( sizeof(cloud_t) ) ;
    if ( tmp == (cloud_t*) NULL ) {
        fprintf(stderr, "cloud_new : malloc 1 failed \n") ;
        return NULL ;
    }
    tmp->nb_points = nb_points ;
    tmp->color_type = COLORTYPE_NONE ;
    tmp->data_size = (size_t) 0 ;
    tmp->points = (point_t*) malloc( nb_points*sizeof(point_t)) ;
    if ( tmp->points == (point_t*) NULL ) {
        fprintf(stderr, "cloud_new: malloc 2 failed \n") ;
        free(tmp) ;
        return NULL ;
    }
    tmp->colors = (color_t*) NULL ;
    tmp->data = (void*) NULL ;
    tmp->tree = (void*) NULL ;
    return tmp ;
}

void cloud_free( cloud_t* nuage ) {
    free( nuage->points ) ;
    if ( nuage->colors != (color_t*) NULL )
        cloud_strip_colors( nuage ) ;
    if ( nuage->data != (void*) NULL )
        cloud_strip_data( nuage ) ;
    if ( nuage->tree != (void*) NULL )
        cloud_strip_tree( nuage ) ;
    free(nuage) ;
}

int cloud_allocate_color( cloud_t* nuage, int color_type, color_t default_color ) {
    nuage->color_type = color_type ;
    nuage->colors = ( color_t*) malloc( nuage->nb_points * sizeof(color_t) ) ;
    if ( nuage->colors == (color_t*) NULL ) {
        fprintf(stderr,"cloud_allocate_color: malloc failed\n") ;
        return -1 ;
    }
    // TODO : recopier dans le tableau la valeur par defaut


}
