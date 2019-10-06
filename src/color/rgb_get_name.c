#include "cyan/color/color.h"
#include <stdio.h>

void rgb_get_name( enum cyan_rgb_workspace rgb, char* str, size_t str_size ) {

    switch ( rgb ) {
        case CYAN_RGB_ADOBE_1998:      
            snprintf(str, str_size,"Adobe RGB (1998)" ) ;
            break;
        case CYAN_RGB_APPLE:          
            snprintf(str, str_size,"Apple RGB" ) ;
            break;
        case CYAN_RGB_BEST:          
            snprintf(str, str_size,"Best RGB" ) ;
            break;
        case CYAN_RGB_BETA:         
            snprintf(str, str_size,"Beta RGB" ) ;
            break;
        case CYAN_RGB_BRUCE:       
            snprintf(str, str_size,"Bruce RGB" ) ;
            break;
        case CYAN_RGB_CIE:        
            snprintf(str, str_size,"CIE RGB" ) ;
            break;
        case CYAN_RGB_COLORMATCH:  
            snprintf(str, str_size,"ColorMatch RGB" ) ;
            break;
        case CYAN_RGB_DON_4:      
            snprintf(str, str_size,"Don RGB 4" ) ;
            break;
        case CYAN_RGB_ECI:       
            snprintf(str, str_size,"ECI RGB v2" ) ;
            break;
        case CYAN_RGB_EKTA_SPACE_PS5: 
            snprintf(str, str_size,"Ekta Space PS5" ) ;
            break;
        case CYAN_RGB_NTSC:          
            snprintf(str, str_size,"NTSC RGB" ) ;
            break;
        case CYAN_RGB_PAL_SECAM:    
            snprintf(str, str_size,"PAL/SECAM RGB" ) ;
            break;
        case CYAN_RGB_PROPHOTO:    
            snprintf(str, str_size,"ProPhoto RGB" ) ;
            break;
        case CYAN_RGB_SMPTE_C:    
            snprintf(str, str_size,"SMPTE-C RGB" ) ;
            break;
        case CYAN_RGB_sRGB:            
            snprintf(str, str_size,"sRGB" ) ;
            break;
        case CYAN_RGB_WIDE_GAMUT: 
            snprintf(str, str_size,"Wide Gamut RGB" ) ;
            break;
        default:
            snprintf(str, str_size,"Unknown" ) ;
            break;
    }
}
