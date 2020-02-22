#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <image/image.h>
#include <io/image_io.h>
#include <color/color.h>

#include <math.h>

#include "load_png.h"
#include "cluster.h"

int main( int argc, char** argv, char* envv ) {

    int i, j ;
    int result ;
    image_t* image ; 
    color_t* couleur ;
	FILE * fp;
       
	fp = fopen("datasets/lena/lena.png", "r");
	if(fp == NULL){	
		fprintf(stderr, "Couldn't open file.\n Error : %d, (%s)\n", errno, strerror(errno));
		return -4;
	}


    if (argc != 2 ) {
        fprintf(stderr,"Usage : %s output_file.ppm\n", argv[0] ) ;
       return -1 ;
    }
  
//	image = image_new(480, 480, COLORTYPE_RGB); 
//	draw_circle(image, 241); 

  	image = png2image(fp);
    if ( image == NULL ) {
        fprintf(stderr,"image allocation failed\n") ;
        return -2 ;
    }

    	//BLACK MAGIC ALERT : if threshold < 0, nonsense happens (different values obtained when computing distance...
	//TODO : FIX THIS
    	float threshold = 0.1;
	unsigned int count = 42;
	
	//count = erase_similar_color_xy(image, image->rows/2, image->cols/2, (float) threshold);
	cluster_smooth(image, image->rows/2, image->cols/2, threshold, erase);
	//fprintf(stdout, "Have succesfully been erased : %d pixels.\n", count);

/*    for ( i=0; i<image->rows; i++ )
    for ( j=0; j<image->cols; j++ ) {
        couleur = image_get_pixel_pointer( image, j, i ) ;
        couleur->coords[0] = 1.0 ;
        couleur->coords[1] = 1.0 ;
        couleur->coords[2] = 1.0 ;
    }
*/
 /*   image_add_marker_uv ( image, 100.0, 100.0 ) ;
    image_add_marker_uv ( image, 50.0 , 20.0 ) ;
    image_add_marker_uv ( image, 320.0, 240.0 ) ;

    image_print_all_markers( image, 5, 1, 0.0, 0.0 ) ;
*/
    //draw_circle(image, 120); 
    result = image_save_ppm( image, argv[1] ) ; 
    if (result != 0) {
        fprintf(stderr, "cannot save file\n") ;
        return -3 ;
    }
    
    image_free( image) ;

	fclose(fp);

    return 0 ;
}

//Sets the b_val value to 0 for all pixel in image 
int init_img_bool(image_t * image){
	if(!image){
		fprintf(stderr, "Null pointer for image in init_img_bool().\n");
		return -1;
	}

	int i,j;
	color_t * couleur;

	for ( i=0; i<image->rows; i++ )
		for ( j=0; j<image->cols; j++ ) {
			couleur = image_get_pixel_pointer( image, j, i ) ;
			couleur->b_val = 0;
		}
	return 0;
}

//Explore image using recursive BFS and applies fct() on nodes when color distance with color at coord (x,y) is smaller than threshold
//Applies fct() to each node added
//WARNING: cluster_cmp uses a recursive function, if the cluster under evaluation is too large, stack gets too big, resulting in segmentation fault
//TODO : write an iterative cluster_cmp()
int cluster_cmp(image_t * image, unsigned int x, unsigned int y, float threshold, int (*fct)( color_t *)){
	init_img_bool(image);

	color_t * couleur;
	couleur = image_get_pixel_pointer(image, y, x);;     

	return cluster_bfs_rec_cmp(image, x, y, threshold, couleur, fct);
}

//Explore image using recursive BFS and applies fct() on nodes when color distance with neighbour is smaller than threshold
//NOTE : neighbour is the node used to reach node evaluated, hence result depends of the order in which bfs_parse_smooth explores the image
//Applies fct() to each node added
//WARNING: cluster_smooth uses a recursive function, if the cluster under evaluation is too large, stack gets too big, resulting in segmentation fault
//TODO : write an iterative cluster_smooth() function
int cluster_smooth(image_t * image, unsigned int x, unsigned int y, float threshold, int (*fct)( color_t *)){
	init_img_bool(image);

	color_t * couleur = NULL;

	return cluster_bfs_rec_smooth(image, x, y, threshold, couleur, fct);
}
//Returns the number of times fct has been applied
//TODO : x or y being out of screen results in segfault 
int cluster_bfs_rec_cmp(image_t * image, unsigned int y, unsigned int x, float threshold, color_t * couleur_cmp, int (*fct)( color_t *) ){
	
	color_t * couleur = NULL;

	float dist;

	couleur = image_get_pixel_pointer_safe(image, y, x + 1);
	if(couleur)
		if(!couleur->b_val){
			couleur->b_val = 1;
			dist = color_distance_euclid(couleur, couleur_cmp);
			if(dist < threshold){
				cluster_bfs_rec_cmp(image, y, x + 1 , threshold, couleur_cmp, fct);
				fct(couleur);
			}	
		}	

	couleur = image_get_pixel_pointer_safe(image, y, x - 1);
	if(couleur)
		if(!couleur->b_val){
			couleur->b_val = 1;
			dist = color_distance_euclid(couleur, couleur_cmp);
			if(dist < threshold){
				cluster_bfs_rec_cmp(image, y, x - 1 , threshold, couleur_cmp, fct);
				fct(couleur);
			}
		}

	couleur = image_get_pixel_pointer_safe(image, y + 1, x);
	if(couleur)
		if(!couleur->b_val){
			couleur->b_val = 1;
			dist = color_distance_euclid(couleur, couleur_cmp);
			if(dist < threshold){
				cluster_bfs_rec_cmp(image, y + 1, x, threshold, couleur_cmp, fct);
				fct(couleur);
			}
		}

	couleur = image_get_pixel_pointer_safe(image, y - 1, x);
	if(couleur)
		if(!couleur->b_val){
			couleur->b_val = 1;
			dist = color_distance_euclid(couleur, couleur_cmp);
			if(dist < threshold){
				cluster_bfs_rec_cmp(image, y - 1, x, threshold, couleur_cmp, fct);
				fct(couleur);
			}
		}
}
int cluster_bfs_rec_smooth(image_t * image, unsigned int y, unsigned int x, float threshold, color_t * couleur_cmp, int (*fct)( color_t *) ){

	if(!couleur_cmp){
		couleur_cmp = image_get_pixel_pointer(image, y, x);
	}

	color_t * couleur;

	couleur = image_get_pixel_pointer_safe(image, y, x + 1);
	if(couleur)
		if(!couleur->b_val){
			couleur->b_val = 1;
			if(color_distance_euclid(couleur, couleur_cmp) < threshold){
				cluster_bfs_rec_smooth(image, y, x + 1, threshold, couleur, fct);
				fct(couleur);
			}
		}
	
	couleur = image_get_pixel_pointer_safe(image, y, x - 1);
	if(couleur)
		if(!couleur->b_val){
			couleur->b_val = 1;
			if(color_distance_euclid(couleur, couleur_cmp) < threshold){
				cluster_bfs_rec_smooth(image, y, x - 1, threshold, couleur, fct);
				fct(couleur);
			}
		}
	
	couleur = image_get_pixel_pointer_safe(image, y + 1, x);
	if(couleur)
		if(!couleur->b_val){
			couleur->b_val = 1;
			if(color_distance_euclid(couleur, couleur_cmp) < threshold){
				cluster_bfs_rec_smooth(image, y + 1, x, threshold, couleur, fct);
				fct(couleur);
			}
		}
	
	couleur = image_get_pixel_pointer_safe(image, y - 1, x);
	if(couleur)
		if(!couleur->b_val){
			couleur->b_val = 1;
			if(color_distance_euclid(couleur, couleur_cmp) < threshold){
				cluster_bfs_rec_smooth(image, y - 1, x, threshold, couleur, fct);
				fct(couleur);
			}
		}	
}


int erase(color_t * couleur){
	couleur->coords[0] = 1.0 ;
	couleur->coords[1] = 1.0 ;
	couleur->coords[2] = 1.0 ;

	return 1;
}

unsigned int erase_similar_color(image_t * image, float threshold, color_t * couleur_cmp){

	color_t * couleur; 
	
	float dist = 0;

	int i,j;
	unsigned int count = 0;

	for ( i=0; i<image->rows; i++ )
		for ( j=0; j<image->cols; j++ ) {
        		couleur = image_get_pixel_pointer( image, j, i );
			dist = color_distance_euclid(couleur_cmp, couleur); 
	
			//fprintf(stdout, "dist : %f.\n", dist);

			if(dist > threshold){
				couleur->coords[0] = 1.0 ;
				couleur->coords[1] = 1.0 ;
				couleur->coords[2] = 1.0 ;

				count++;
			}
		}
	return count;
}

unsigned int erase_similar_color_xy(image_t * image, unsigned int x, unsigned int y, float threshold){

	color_t * couleur;
	couleur = image_get_pixel_pointer( image, y, x );

	return erase_similar_color(image, threshold, couleur);
}

//Computes Euclidean color distance between color1 and color 2
//WARNING : This is not the euclidean distance (L2 norm), it is its square (SED) (a divergence)
float color_distance_euclid(color_t * color1, color_t * color2){
	if(!color1){
		fprintf(stdout, "In color_distance_euclid(), color1 is a NULL pointer.\n");
		return (float) -1;
	}
	if(!color2){
		fprintf(stdout, "In color_distance_euclid(), color1 is a NULL pointer.\n");
		return (float) -1;
	}


	int i;
	float dist_sq = 0.0;
	for(i=0; i<=2; i++)
		dist_sq+=  (color1->coords[i] - color2->coords[i])*(color1->coords[i] - color2->coords[i]);
	
	return dist_sq;
}

int draw_circle(image_t * image , int radius){
	
	int i,j;	
    	color_t* couleur ;
	
	for ( i=0; i<image->rows; i++ )
	    for ( j=0; j<image->cols; j++ ) 
		if( in_circle( i, j, image->cols/2, image->rows/2, radius) )	 	
			image_add_marker_uv ( image, i, j ) ;
	
    	image_print_all_markers( image, 5, 1, 0.0, 0.0 ) ;
	return 0;
}

int in_circle(int x, int y, int x_0, int y_0, int radius){
//Returns 1 if (x,y) is in the circle C( (x_0, y_0), radius )
//Returns 0 otherwise

	if( (x-x_0)*(x-x_0) + (y-y_0)*(y-y_0) - radius*radius >= 0)
		return 0;
	return 1;
}


