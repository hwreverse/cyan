#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <cyan/image/image.h>

image_t* image_new(int cols, int rows) {
	image_t *tmp;
	tmp = (image_t *) malloc(sizeof(image_t));
	if (tmp == NULL) {
		fprintf(stderr, "image_new : malloc error\n");
		return NULL;
	}
	tmp->rows = rows;
	tmp->cols = cols;
    tmp->monochrome = 0 ;
    tmp->illuminant = CYAN_D50 ;
	tmp->X = (double *) malloc(rows * cols * sizeof(double));
	tmp->Y = (double *) malloc(rows * cols * sizeof(double));
	tmp->Z = (double *) malloc(rows * cols * sizeof(double));
	if ( (tmp->X == NULL) || (tmp->Y == NULL) || (tmp->Z == NULL) ) {
		fprintf(stderr, "image_new : pixels allocation error \n");
		free(tmp);
		return NULL;
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


//Concatenates two image horizontally
//img_left and img_right must have the same number of rows
int image_cat_hor( image_t ** dst, image_t * img_left, image_t * img_right ){
	if(dst == NULL || img_left == NULL ||img_right == NULL){
		fprintf(stderr, "ERR : image_cat_hor : an argument is NULL.\n");
		return -1;
	}
	if(img_left->rows != img_right->rows){
		fprintf(stderr, "ERR: image_cat_hor : img_left and img_right do not have the same number of rows ( resp. %d\t%d) \n", img_left->rows, img_right->rows);
		return -1;
	}
	
	if(*dst == NULL){
		fprintf(stdout, "image_cat_hor : dst is pointing to a NULL, allocating new image (size : %d).\n", (img_left->cols + img_right->cols) * img_left->rows * sizeof(double) );
		*dst = image_new( img_left->cols + img_right->cols, img_left->rows);
		if( *dst == NULL){
			fprintf(stderr, "ERR: image_cat_hor: Image allocation failed.\n");
			return -1;
		}	
	}


	int i = 0;

	for(i = 0; i < (*dst)->rows; i++){
		fprintf(stdout, "copying left... %d/%d \n", i, (*dst)->rows);
		//Copying left image
		memcpy( &((*dst)->X[i*(*dst)->cols]), &(img_left->X[i * img_left->cols]), img_left->cols*sizeof(double)  );
		memcpy( &((*dst)->Y[i*(*dst)->cols]), &(img_left->Y[i * img_left->cols]), img_left->cols*sizeof(double)  );
		memcpy( &((*dst)->Z[i*(*dst)->cols]), &(img_left->Z[i * img_left->cols]), img_left->cols*sizeof(double)  );

		fprintf(stdout, "copying right... %d/%d \n", i, img_left->rows);
		//Copying right image
		memcpy( &((*dst)->X[i*(*dst)->cols + img_left->cols]), &(img_right->X[i*img_right->cols]), img_right->cols*sizeof(double)); 
		memcpy( &((*dst)->Y[i*(*dst)->cols + img_left->cols]), &(img_right->Y[i*img_right->cols]), img_right->cols*sizeof(double)); 
		memcpy( &((*dst)->Z[i*(*dst)->cols + img_left->cols]), &(img_right->Z[i*img_right->cols]), img_right->cols*sizeof(double)); 
	}

	fprintf(stdout, "image_cat_hor : Success\n");

	return 0;

}

int image_allocate_data_default(image_t * img, size_t size, void *data_array) {
	int i;
	if (img == (image_t *) NULL) {
		fprintf(stderr,
			"image_allocate_data_default: image is a NULL pointer\n");
		return -1;
	}
	if (img->pixel_data != (void *) NULL) {
		fprintf(stderr,
			"image_allocate_data_default : img->pixel_data is not NULL \n");
		return -1;
	}
	img->pixel_data_size = size;
	img->pixel_data = (void *) malloc(img->rows * img->cols * size);
	if (img->pixel_data == NULL) {
		fprintf(stderr,
			"image_allocate_data_default : data allocation error \n");
		img->pixel_data_size = 0;
		return 0;
	}
	for (i = 0; i < img->rows * img->cols; i++) {
		memcpy(img->pixel_data + i * size, data_array, size);
	}
	return i;
}

int image_allocate_data_fct(image_t * img, size_t size, int (*fill_fct) (image_t *, int, int, void *), void *context) {
	int i, j, ret;
	if (img == (image_t *) NULL) {
		fprintf(stderr,
			"image_allocate_data_fct: image is a NULL pointer\n");
		return -1;
	}
	if (img->pixel_data != (void *) NULL) {
		fprintf(stderr,
			"image_allocate_data_fct : img->pixel_data is not NULL \n");
		return -1;
	}
	img->pixel_data_size = size;
	img->pixel_data = (void *) malloc(img->rows * img->cols * size);
	if (img->pixel_data == NULL) {
		fprintf(stderr,
			"image_allocate_data_fct : data allocation error \n");
		img->pixel_data_size = 0;
		return 0;
	}
	ret = 0;
	for (j = 0; j < img->rows; j++)
		for (i = 0; i < img->cols; i++) {
			ret += fill_fct(img, i, j, context);
		}
	return ret;
}

int image_import_data(image_t * img, size_t data_size, void *data) {
	if (img == (image_t *) NULL) {
		fprintf(stderr,
			"image_import_data: image is a NULL pointer\n");
		return -1;
	}
	if (img->pixel_data != (void *) NULL) {
		fprintf(stderr,
			"image_import_data : img->pixel_data is not NULL \n");
		return -1;
	}
	img->pixel_data_size = data_size;
	memcpy(img->pixel_data, data, img->cols * img->rows * data_size);
	return img->cols * img->rows;
}

void *image_get_data_pointer(image_t * img, int i, int j) {
	return img->pixel_data + (i + j * img->cols) * img->pixel_data_size;
}

image_t *image_clone(image_t * img) {
	image_t *clone;
	clone = image_new(img->cols, img->rows);
    clone->monochrome = img->monochrome ;
    clone->illuminant = img->illuminant ;
    fprintf(stdout, "Inside image_clone().\n");
    memcpy(clone->Y, img->Y, img->rows * img->cols * sizeof(double));
	if ( img->monochrome ) {
		//HOTFIX
		//There should be a better way to do this (i.e, without allocating a
		//whole array of zeros which should not be used 
        	//Assigning a NULL pointer to either of these causes segmentation fault upon allocation after exiting image_clone()
	clone->X = calloc(img->rows*img->cols, sizeof(double)) ;
        clone->Z = clone->X;
    } else {
	    memcpy(clone->X, img->X, img->rows * img->cols * sizeof(double));
	    memcpy(clone->Z, img->Z, img->rows * img->cols * sizeof(double));
    }
    if (img->pixel_data != (void *) NULL) {
		image_import_data(clone, img->pixel_data_size, img->pixel_data);
	}
    fprintf(stdout, "About to exit image_clone().\n");
	return clone;
}

