#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <onevision/3dmodel/cloud.h>

void cloud_strip_data ( cloud_t* nuage) {
	nuage->data_size = (size_t) 0 ;
	free(nuage->data) ;
	nuage->data = NULL ;
}
