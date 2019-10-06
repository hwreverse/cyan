#include "cyan/color/color.h"
#include <stdio.h>

void refwhite_get_name( enum cyan_refwhite w, char* str, size_t str_size ) {

    switch ( w ) {
        case CYAN_A:  
            snprintf(str, str_size,"A" ) ;
            break;
        case CYAN_B:  
            snprintf(str, str_size,"B" ) ;
            break;
        case CYAN_C:  
            snprintf(str, str_size,"C" ) ;
            break;
        case CYAN_D50:
            snprintf(str, str_size,"D50" ) ;
            break;
        case CYAN_D55:
            snprintf(str, str_size,"D55" ) ;
            break;
        case CYAN_D65:
            snprintf(str, str_size,"D65" ) ;
            break;
        case CYAN_D75:
            snprintf(str, str_size,"D75" ) ;
            break;
        case CYAN_E:  
            snprintf(str, str_size,"E" ) ;
            break;
        case CYAN_F2: 
            snprintf(str, str_size,"F2" ) ;
            break;
        case CYAN_F7: 
            snprintf(str, str_size,"F7" ) ;
            break;
        case CYAN_F11:
            snprintf(str, str_size,"F11" ) ;
            break;
        default:
            snprintf(str, str_size,"Unknown" ) ;
            break;
    }
}
