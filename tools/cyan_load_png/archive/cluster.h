#ifndef CLUSTER_H
#define CLUSTER_H

int draw_circle(image_t * , int );
int in_circle(int x, int y, int x_0, int y_0, int radius);


int basic_cluster(image_t * image, unsigned int x, unsigned int y, float threshold);
int * cluster_rec(image_t * image, unsigned int x, unsigned int y, float threshold, color_t * couleur);

unsigned int erase_similar_color(image_t * image, float threshold, color_t * couleur_cmp);
unsigned int erase_similar_color_xy(image_t * image, unsigned int x, unsigned int y, float threshold);

float color_distance_euclid(color_t * color1, color_t * color2);

int cluster_cmp(image_t * image, unsigned int x, unsigned int y, float threshold, int (*fct)( color_t *));
int cluster_smooth(image_t * image, unsigned int x, unsigned int y, float threshold, int (*fct)( color_t *));

int cluster_bfs_rec_cmp(image_t * image, unsigned int x, unsigned int y, float threshold, color_t * couleur_cmp, int (*fct)( color_t *) );
int cluster_bfs_rec_smooth(image_t * image, unsigned int x, unsigned int y, float threshold, color_t * couleur_cmp, int (*fct)( color_t *) );

int erase(color_t * couleur);
#endif
