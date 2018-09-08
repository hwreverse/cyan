#ifndef CYAN_COLOR_H
#define CYAN_COLOR_H

#define COLORTYPE_NONE 	0
#define COLORTYPE_RGB  	1
#define COLORTYPE_HSV  	2
#define COLORTYPE_LAB  	3
#define COLORTYPE_XYZ  	4

#define RGB_R 0
#define RGB_G 1
#define RGB_B 2
#define HSV_H 0
#define HSV_S 1
#define HSV_V 2
#define LAB_L 0
#define LAB_A 1
#define LAB_B 2
#define XYZ_X 0
#define XYZ_Y 1
#define XYZ_Z 2

typedef struct color_s {
	float coords[3] ;
} color_t ;

void color_convert  ( int colortype_from, int colortype_to, color_t*, color_t* ) ;
void color_convert_ ( int colortype_from, int colortype_to, color_t* ) ;

void rgb2hsv ( color_t, color_t* ) ;
void rgb2lab ( color_t, color_t* ) ;
void rgb2xyz ( color_t, color_t* ) ;
void hsv2rgb ( color_t, color_t* ) ;
void hsv2lab ( color_t, color_t* ) ;
void hsv2xyz ( color_t, color_t* ) ;
void lab2rgb ( color_t, color_t* ) ;
void lab2hsv ( color_t, color_t* ) ;
void lab2xyz ( color_t, color_t* ) ;
void xyz2rgb ( color_t, color_t* ) ;
void xyz2hsv ( color_t, color_t* ) ;
void xyz2lab ( color_t, color_t* ) ;

void rgb2hsv_ ( color_t* ) ;
void rgb2lab_ ( color_t* ) ;
void rgb2xyz_ ( color_t* ) ;
void hsv2rgb_ ( color_t* ) ;
void hsv2lab_ ( color_t* ) ;
void hsv2xyz_ ( color_t* ) ;
void lab2rgb_ ( color_t* ) ;
void lab2hsv_ ( color_t* ) ;
void lab2xyz_ ( color_t* ) ;
void xyz2rgb_ ( color_t* ) ;
void xyz2hsv_ ( color_t* ) ;
void xyz2lab_ ( color_t* ) ;

#endif
