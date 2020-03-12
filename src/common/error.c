#include "cyan/common/error.h"

#if HAVE_GETTEXT
    
    #include <libintl.h>
    #define _(STRING) dgettext ( "cyan", STRING )

#else

    #define _(STRING) STRING

#endif


// TODO:
//
// Mettre dans la fonction init()
// bindtextdomain ("cyan", "/usr/share/locale";


const char* error_get_text ( int error_code ) {
    switch ( error_code ) {
        case ERR_OK:
            return _("OK") ;
        case ERR_MALLOC:
            return _("Memory allocation failed") ;    
        case ERR_NULL:
            return _("NULL pointer was given") ;
        case ERR_INVALID_ARG:
            return _("Given argument is invalid or has wrong value") ;
    }
    return _("Unknown error") ;
}

