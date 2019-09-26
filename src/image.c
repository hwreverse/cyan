#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <cyan/image.h>

/**
 * \fn image_t *image_new(int cols, int rows, cyan_colorspace_t colorspace) 
 *
 * \brief Fonction de construction de l'objet image_t.
 *
 * \param cols nombre de colonnes de pixels ("largeur")
 * \param rows nombre de lignes de pixels ("hauteur")
 * \param colorspace espace colorimétrique choisi
 *
 * \return Adresse de l'image_t allouée, NULL en cas d'erreur. 
 *
 * \ingroup image
 * \relates image_t
 */


image_t *image_new(int cols, int rows, cyan_colorspace_t colorspace) {

	image_t *tmp;
	tmp = (image_t *) malloc(sizeof(image_t));
	if (tmp == NULL) {
		fprintf(stderr, "image_new : malloc error\n");
		return NULL;
	}
	tmp->rows = rows;
	tmp->cols = cols;
	tmp->colorspace = colorspace;
	tmp->pixels = (color_t *) malloc(rows * cols * sizeof(color_t));
	if (tmp->pixels == NULL) {
		fprintf(stderr, "image_new : pixels allocation error \n");
		free(tmp);
		return NULL;
	}
	tmp->data_size = (size_t) 0;
	tmp->data = (void *) NULL;
	tmp->nb_markers = 0;
	tmp->markers = (marker_t *) NULL;

	return tmp;
}

/**
 * \fn void image_free(image_t * img) {
 *
 * \brief Fonction de désallocation de la structure image_t.
 *
 * \param img adresse de l'image qui doit être désallouée
 *
 * \ingroup image
 * \relates image_t
 */

void image_free(image_t * img) {
	if (img->data != (void *) NULL) {
		free(img->data);
		img->data_size = 0;
	}
	if (img->markers != (marker_t *) NULL) {
		free(img->markers);
		img->nb_markers = 0;
		img->tab_marker_size = 0;
	}
	free(img->pixels);
	free(img);
}

int image_allocate_data_default(image_t * img, size_t size, void *data_array) {
	int i;
	if (img == (image_t *) NULL) {
		fprintf(stderr,
			"image_allocate_data_default: image is a NULL pointer\n");
		return -1;
	}
	if (img->data != (void *) NULL) {
		fprintf(stderr,
			"image_allocate_data_default : img->data is not NULL \n");
		return -1;
	}
	img->data_size = size;
	img->data = (void *) malloc(img->rows * img->cols * size);
	if (img->data == NULL) {
		fprintf(stderr,
			"image_allocate_data_default : data allocation error \n");
		img->data_size = 0;
		return 0;
	}
	for (i = 0; i < img->rows * img->cols; i++) {
		memcpy(img->data + i * size, data_array, size);
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
	if (img->data != (void *) NULL) {
		fprintf(stderr,
			"image_allocate_data_fct : img->data is not NULL \n");
		return -1;
	}
	img->data_size = size;
	img->data = (void *) malloc(img->rows * img->cols * size);
	if (img->data == NULL) {
		fprintf(stderr,
			"image_allocate_data_fct : data allocation error \n");
		img->data_size = 0;
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
	if (img->data != (void *) NULL) {
		fprintf(stderr,
			"image_import_data : img->data is not NULL \n");
		return -1;
	}
	img->data_size = data_size;
	memcpy(img->data, data, img->cols * img->rows * data_size);
	return img->cols * img->rows;
}

void *image_get_data_pointer(image_t * img, int i, int j) {
	return img->data + (i + j * img->cols) * img->data_size;
}

color_t *image_get_pixel_pointer(image_t * img, int i, int j) {
	return &(img->pixels[i + j * img->cols]);
}

image_t *image_clone(image_t * img) {
	image_t *clone;
	clone = image_new(img->cols, img->rows, img->colorspace);
	memcpy(clone->pixels, img->pixels,
	       img->rows * img->cols * sizeof(color_t));
	if (img->data != (void *) NULL) {
		image_import_data(clone, img->data_size, img->data);
	}
	if (img->nb_markers != 0) {
		clone->nb_markers = img->nb_markers;
		clone->tab_marker_size = img->nb_markers;
		clone->markers =
		    (marker_t *) malloc(img->nb_markers *
					sizeof(marker_t));
	}
	return clone;
}

int image_add_marker(image_t * img, marker_t m) {
	marker_t *tmp;
	if (img->nb_markers == img->tab_marker_size) {
		tmp =
		    (marker_t *) malloc((img->tab_marker_size + 10) *
					sizeof(marker_t));
		if (img->markers != (marker_t *) NULL) {
			memcpy(tmp, img->markers,
			       img->tab_marker_size * sizeof(marker_t));
			free(img->markers);
		}
		img->markers = tmp;
		img->tab_marker_size += 10;
	}
	img->markers[img->nb_markers].u = m.u;
	img->markers[img->nb_markers].v = m.v;
	img->nb_markers++;
	return 1;
}

int image_add_marker_uv(image_t * img, double u, double v) {
	marker_t *tmp;
	if (img->nb_markers == img->tab_marker_size) {
		tmp =
		    (marker_t *) malloc((img->tab_marker_size + 10) *
					sizeof(marker_t));
		if (img->markers != (marker_t *) NULL) {
			memcpy(tmp, img->markers,
			       img->tab_marker_size * sizeof(marker_t));
			free(img->markers);
		}
		img->markers = tmp;
		img->tab_marker_size += 10;
	}
	img->markers[img->nb_markers].u = u;
	img->markers[img->nb_markers].v = v;
	img->nb_markers += 1;
	return 1;
}

int image_del_marker(image_t * img, int position) {
	if ((img->nb_markers <= position) || (position < 0)) {
		fprintf(stderr, "del_marker: invalid position\n");
		return 0;
	}
	if (position != img->nb_markers - 1) {
		img->markers[position].u =
		    img->markers[img->nb_markers - 1].u;
		img->markers[position].v =
		    img->markers[img->nb_markers - 1].v;
	}
	img->nb_markers -= 1;
	return 1;
}

int image_print_all_markers( image_t* img, int size, float colorcmp1, float colorcmp2, float colorcmp3 ) {
    int i ;
    int j ;
    int u,v ;
    int count ;
    count = 0 ;
    if ( img->colorspace != CYAN_COLORTYPE_RGB )              // FIXME
        return -1 ;
    for (i=0; i<img->nb_markers; i++) {
        u = (int) img->markers[i].u ;
        v = (int) img->markers[i].v ;
        if ((u>size) && (u<img->cols-size) && (v>size) && (v<img->rows-size)) {
            for (j=-size; j<=size;j++ ) {
                img->pixels[v*img->cols+(u+j)].coords[0] = colorcmp1 ;
                img->pixels[v*img->cols+(u+j)].coords[1] = colorcmp2 ;
                img->pixels[v*img->cols+(u+j)].coords[2] = colorcmp2 ;
                img->pixels[(v+j)*img->cols+u].coords[0] = colorcmp1 ;
                img->pixels[(v+j)*img->cols+u].coords[1] = colorcmp2 ;
                img->pixels[(v+j)*img->cols+u].coords[2] = colorcmp3 ;
            }
                count++ ;
        }
    }
    return count ;
}
