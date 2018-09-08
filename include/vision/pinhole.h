#ifndef CYAN_PINHOLE_H
#define CYAN_PINHOLE_H

typedef struct {

    double s ;
    double f ;
    double u0 ;
    double v0 ;
    double r ;

    // TODO ajouter matrice de projection
    // TODO ajouter modele pour les deformations d'optique

} pinhole_t ;

#endif
