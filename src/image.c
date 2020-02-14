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
		//whole array of zeros which should not been used 
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

int image_save_ppm(image_t * img, char *filename) {
	FILE *f = fopen(filename, "wb");
	if (f) { 
		//Writing ppm file header
		fprintf(f, "P6 %d %d 255\n", img->cols, img->rows);
		
		//Filling ppm with data
		double temp[3];
		int i,j, coord;
		for(i = 0; i< img->rows; i++){
			for(j = 0; j < img->cols; j++){
				coord = j + i * img->cols;

				XYZ_to_RGB(CYAN_RGB_BEST, img->X[coord], img->Y[coord], img->Z[coord], &(temp[0]), &(temp[1]), &(temp[2]));	
			
				temp[0] *= 255.0f;			
				temp[1] *= 255.0f;			
				temp[2] *= 255.0f;	
			
				fprintf(f, "%c%c%c", (int) temp[0], (int) temp[1], (int) temp[2]);
			}	
		}
		fclose(f);
		fprintf(stdout, "file  %s saved \n", filename);
		return 0;
	} else {
		fprintf(stderr, "ERROR saving `%s'\n", filename);
		return -1;
	}
}

