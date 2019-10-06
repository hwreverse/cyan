#include <cyan/color/color.h>

void refwhite_get_xyz( enum cyan_refwhite w, double* X, double* Y,double* Z) {
    switch( w ) {
        case CYAN_A: 
            *X=1.09850 ;
            *Y=1.00000 ; 
            *Z=0.35585 ; 
            break;
        case CYAN_B: 
            *X=0.99072 ; 
            *Y=1.00000 ; 
            *Z=0.85223 ;
            break;
        case CYAN_C:
            *X=0.98074 ;
            *Y=1.00000 ;
            *Z=1.18232 ;
            break;
        case CYAN_D50:
            *X=0.96422 ; 
            *Y=1.00000 ; 
            *Z=0.82521 ;
            break;
        case CYAN_D55: 
            *X=0.95682 ; 
            *Y=1.00000 ; 
            *Z=0.92149 ;
            break;
        case CYAN_D65:
            *X=0.95047 ;
            *Y=1.00000 ; 
            *Z=1.08883 ;
            break;
        case CYAN_D75: 
            *X=0.94972 ; 
            *Y=1.00000 ; 
            *Z=1.22638 ;
            break;
        case CYAN_E: 
            *X=1.00000 ; 
            *Y=1.00000 ; 
            *Z=1.00000 ;
            break;
        case CYAN_F2: 
            *X=0.99186 ; 
            *Y=1.00000 ; 
            *Z=0.67393 ; 
            break;
        case CYAN_F7: 
            *X=0.95041 ; 
            *Y=1.00000 ; 
            *Z=1.08747 ; 
            break;
        case CYAN_F11: 
            *X=1.00962 ; 
            *Y=1.00000 ; 
            *Z=0.64350 ;
            break;
        default:
            *X=0.0 ;
            *Y=0.0 ;
            *Z=0.0 ;
            break;
    }
}
