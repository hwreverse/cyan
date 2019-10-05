#ifndef CYAN_COLOR_H
#define CYAN_COLOR_H

enum {
    CYAN_XYZ        =0,
    CYAN_xyY        =1,
    CYAN_Lab        =2,
    CYAN_LCHab      =3,
    CYAN_Luv        =4,
    CYAN_LCHuv      =5,
    CYAN_RGB        =6,
    CYAN_spectrum   =7
} cyan_colorspace ;

enum {
    CYAN_A      =0,
    CYAN_B      =1,
    CYAN_C      =2,
    CYAN_D50    =3,
    CYAN_D55    =4,
    CYAN_D65    =5,
    CYAN_D75    =6,
    CYAN_E      =7,
    CYAN_F2     =8,
    CYAN_F7     =9,
    CYAN_F11    =10,
} cyan_refwhite ;

enum {
    CYAN_RGB_ADOBE_1998      =0,
    CYAN_RGB_APPLE           =1,
    CYAN_RGB_BEST            =2,
    CYAN_RGB_BETA            =3,
    CYAN_RGB_BRUCE           =4,
    CYAN_RGB_CIE             =5,
    CYAN_RGB_COLORMATCH      =6,
    CYAN_RGB_DON_4           =7,
    CYAN_RGB_ECI             =8,
    CYAN_RGB_EKTA_SPACE_PS5  =9,
    CYAN_RGB_NTSC            =10,
    CYAN_RGB_PAL_SECAM       =11,
    CYAN_RGB_PROPHOTO        =12,
    CYAN_RGB_SMPTE_C         =13,
    CYAN_RGB_sRGB            =14,
    CYAN_RGB_WIDE_GAMUT      =15
} cyan_rgb_workspace ;

double cyan_refwhite_xyz[11][3] = { { 1.09850 , 1.00000 , 0.35585 },    // CYAN_A
                                    { 0.99072 , 1.00000 , 0.85223 },    // CYAN_B
                                    { 0.98074 , 1.00000 , 1.18232 },    // CYAN_C
                                    { 0.96422 , 1.00000 , 0.82521 },    // CYAN_D50
                                    { 0.95682 , 1.00000 , 0.92149 },    // CYAN_D55
                                    { 0.95047 , 1.00000 , 1.08883 },    // CYAN_D65
                                    { 0.94972 , 1.00000 , 1.22638 },    // CYAN_D75
                                    { 1.00000 , 1.00000 , 1.00000 },    // CYAN_E
                                    { 0.99186 , 1.00000 , 0.67393 },    // CYAN_F2
                                    { 0.95041 , 1.00000 , 1.08747 },    // CYAN_F7
                                    { 1.00962 , 1.00000 , 0.64350 } };  // CYAN_F11

void RGB_to_XYZ( enum cyan_rgb_worskpace RGB_space, double R, double G, double B, enum cyan_refwhite w, double* X, double* Y, double* Z ) ;  // TODO
void XYZ_to_RGB( enum cyan_refwhite w, double X, double Y, double Z, enum cyan_rgb_workspage RGB_space, double* R, double* G, double* B ) ;  // TODO

void xyY_to_XYZ() ;      // TODO
void XYZ_to_xyY() ;      // TODO

void Lab_to_XYZ() ;      // TODO
void XYZ_to_Lab() ;      // TODO

void LCHab_to_Lab() ;    // TODO
void Lab_to_LCHab() ;    // TODO

void Lab_to_XYZ() ;      // TODO
void XYZ_to_Lab() ;      // TODO

void Luv_to_XYZ() ;      // TODO
void XYZ_to_Luv() ;      // TODO

void LCHuv_to_Luv() ;    // TODO
void Luv_to_LCHuv() ;    // TODO

void Luv_to_XYZ() ;      // TODO
void XYZ_to_Luv() ;      // TODO

void spectrum_to_XYZ() ;    // TODO
void XYZ_to_spectrum() ;    // TODO

#endif
