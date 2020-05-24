#include <string.h>
#include "cyan/common/error.h"
#include "cyan_file.h"


int write_header( FILE* fd, const char header[] ) {
    int ret ;
    ret=fwrite( header, strlen(header), 1, fd ) ;
    if ( ret != 1 ) {
        CYAN_ERROR( ERR_FILE ) ;
        return ERR_FILE ;
    }
    
    return ERR_OK ;
}

int read_header( FILE* fd, const char header[] ) {
    char buff[10]={'\0'} ;
    
    if ( fread(buff, strlen(header),1,fd ) != strlen(header) ) {
        CYAN_ERROR( ERR_FILE ) ;
        return ERR_FILE ;
    }

    if ( strcmp( buff, header ) != 0 ) {
        CYAN_ERROR( ERR_FILE ) ;
        return ERR_FILE ;
    }

    return ERR_OK ;

}
