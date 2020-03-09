#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "cyan/common/error.h"
#include "cyan/image/image.h"

image_t* image_new(int cols, int rows) {
	image_t *tmp;
	tmp = (image_t *) malloc(sizeof(image_t));
	if (tmp == NULL) {
		CYAN_ERROR( ERR_MALLOC ) ;
		return NULL;
	}
	tmp->rows = rows;
	tmp->cols = cols;
    tmp->monochrome = 0 ;
    tmp->illuminant = CYAN_D50 ;
	tmp->X = (double *) malloc(rows * cols * sizeof(double));
    if ( tmp->X == NULL ) {
        CYAN_ERROR( ERR_MALLOC ) ;
        return NULL ;
    }
	tmp->Y = (double *) malloc(rows * cols * sizeof(double));
    if ( tmp->Y == NULL ) {
        CYAN_ERROR( ERR_MALLOC ) ;
        return NULL ;
    }
	tmp->Z = (double *) malloc(rows * cols * sizeof(double));
    if ( tmp->Z == NULL ) {
        CYAN_ERROR( ERR_MALLOC ) ;
        return NULL ;
    }
	tmp->pixel_data_size = (size_t) 0;
	tmp->pixel_data = (void *) NULL;
	return tmp;
}

void image_free(image_t * img) {
	if (img->pixel_data != (void *) NULL) {
		free(img->pixel_data);
		img->pixel_data_size = 0;
	}
	if (img->X != (double *) NULL) {
		free(img->X);
	}
	if (img->Y != (double *) NULL) {
		free(img->Y);
	}
	if (img->Z != (double *) NULL) {
		free(img->Z);
	}
	free(img);
}

int image_allocate_data_default(image_t * img, size_t size, void *data_array) {
	int i;
	if (img == (image_t *) NULL) {
        CYAN_ERROR( ERR_NULL ) ;
		return ERR_NULL ;
	}
	if (img->pixel_data != (void *) NULL) {
		CYAN_ERROR( ERR_INVALID_ARG ) ;
        return ERR_INVALID_ARG ;
	}
	img->pixel_data_size = size;
	img->pixel_data = (void *) malloc(img->rows * img->cols * size);
	if (img->pixel_data == NULL) {
		CYAN_ERROR( ERR_MALLOC ) ;
        return ERR_MALLOC ;
	}
	for (i = 0; i < img->rows * img->cols; i++) {
		memcpy(img->pixel_data + i * size, data_array, size);
	}
	return ERR_OK ;
}

int image_allocate_data_fct(image_t * img, size_t size, int (*fill_fct) (image_t *, int, int, void *), void *context) {
	int i, j, ret;
	if (img == (image_t *) NULL) {
        CYAN_ERROR( ERR_NULL ) ;
		return ERR_NULL ;
	}
	if (img->pixel_data != (void *) NULL) {
		CYAN_ERROR( ERR_INVALID_ARG ) ;
        return ERR_INVALID_ARG ;
	}
	img->pixel_data_size = size;
	img->pixel_data = (void *) malloc(img->rows * img->cols * size);
	if (img->pixel_data == NULL) {
		CYAN_ERROR( ERR_MALLOC ) ;
        return ERR_MALLOC ;
    }
	ret = 0;
	for (j = 0; j < img->rows; j++)
		for (i = 0; i < img->cols; i++) {
			ret += fill_fct(img, i, j, context);
		}
	return ERR_OK ;
}

int image_import_data(image_t * img, size_t data_size, void *data) {
	if (img == (image_t *) NULL) {
        CYAN_ERROR( ERR_NULL ) ;
		return ERR_NULL ;
	}
	if (img->pixel_data != (void *) NULL) {
		CYAN_ERROR( ERR_INVALID_ARG ) ;
        return ERR_INVALID_ARG ;
	}
	img->pixel_data_size = data_size;
	memcpy(img->pixel_data, data, img->cols * img->rows * data_size);
	return ERR_OK ;
}

int image_get_data_pointer(image_t * img, int i, int j, void** data_ptr) {
	if ((i<0)||(i>=img->cols)||(j<0)||(j>=img->rows)) {
        CYAN_ERROR( ERR_INVALID_ARG ) ;
        return ERR_INVALID_ARG ;
    }
    *data_ptr=img->pixel_data+(i+j*img->cols)*img->pixel_data_size;
    return ERR_OK ;
}

int image_clone(image_t * img, image_t** dest) {
	*dest = image_new(img->cols, img->rows);
    (*dest)->monochrome = img->monochrome ;
    (*dest)->illuminant = img->illuminant ;
    memcpy((*dest)->Y, img->Y, img->rows * img->cols * sizeof(double));
	if ( img->monochrome ) {
        (*dest)->X = NULL ;
        (*dest)->Z = NULL ;
    } else {
	    memcpy((*dest)->X, img->X, img->rows * img->cols * sizeof(double));
	    memcpy((*dest)->Z, img->Z, img->rows * img->cols * sizeof(double));
    }
    if (img->pixel_data != (void *) NULL) {
		image_import_data( *dest, img->pixel_data_size, img->pixel_data);
	}
	return ERR_OK ;
}

