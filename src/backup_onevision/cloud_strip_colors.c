#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <onevision/3dmodel/cloud.h>

void cloud_strip_colors ( cloud_t* nuage) {
	nuage->color_type = COLORTYPE_NONE ;
	free(nuage->colors) ;
	nuage->colors = NULL ;
}
