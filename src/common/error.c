#include "cyan/common/error.h"

const char* error_get_text ( int error_code ) {
    switch ( error_code ) {
        case ERR_OK:
            return "OK" ;
        case ERR_MALLOC:
            return "Memory allocation failed" ;    
        case ERR_NULL:
            return "NULL pointer was given" ;
        case ERR_INVALID_ARG:
            return "Given argument is invalid or has wrong value" ;
    }
    return "Unknown error" ;
}
