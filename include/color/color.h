#ifndef CYAN_COLOR_H
#define CYAN_COLOR_H

typedef enum {
    CYAN_COLORTYPE_NONE,
    CYAN_COLORTYPE_RGB,
    CYAN_COLORTYPE_HSV,
    CYAN_COLORTYPE_LAB,
    CYAN_COLORTYPE_XYZ
} cyan_colorspace_t ;

#define RGB_R 0 // 0.0 - 1.0
#define RGB_G 1 // 0.0 - 1.0
#define RGB_B 2 // 0.0 - 1.0 
#define HSV_H 0 // 0.0 - 360.0
#define HSV_S 1 // 0.0 - 1.0
#define HSV_V 2 // 0.0 - 1.0
#define LAB_L 0 
#define LAB_A 1
#define LAB_B 2
#define XYZ_X 0
#define XYZ_Y 1
#define XYZ_Z 2

typedef struct {
	float coords[3] ;
} color_t ;

void color_convert  ( cyan_colorspace_t from, cyan_colorspace_t to, color_t*, color_t* ) ;
void color_convert_ ( cyan_colorspace_t from, cyan_colorspace_t to, color_t* ) ;

void rgb2hsv ( color_t, color_t* ) ;
void rgb2lab ( color_t, color_t* ) ; // TODO
void rgb2xyz ( color_t, color_t* ) ; // TODO
void hsv2rgb ( color_t, color_t* ) ; 
void hsv2lab ( color_t, color_t* ) ; // TODO
void hsv2xyz ( color_t, color_t* ) ; // TODO
void lab2rgb ( color_t, color_t* ) ; // TODO
void lab2hsv ( color_t, color_t* ) ; // TODO
void lab2xyz ( color_t, color_t* ) ; // TODO
void xyz2rgb ( color_t, color_t* ) ; // TODO
void xyz2hsv ( color_t, color_t* ) ; // TODO
void xyz2lab ( color_t, color_t* ) ; // TODO

void rgb2hsv_ ( color_t* ) ; 
void rgb2lab_ ( color_t* ) ; // TODO
void rgb2xyz_ ( color_t* ) ; // TODO
void hsv2rgb_ ( color_t* ) ;
void hsv2lab_ ( color_t* ) ; // TODO
void hsv2xyz_ ( color_t* ) ; // TODO
void lab2rgb_ ( color_t* ) ; // TODO
void lab2hsv_ ( color_t* ) ; // TODO
void lab2xyz_ ( color_t* ) ; // TODO
void xyz2rgb_ ( color_t* ) ; // TODO
void xyz2hsv_ ( color_t* ) ; // TODO
void xyz2lab_ ( color_t* ) ; // TODO

#endif
