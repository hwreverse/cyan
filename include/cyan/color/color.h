#ifndef CYAN_COLOR_H
#define CYAN_COLOR_H

enum cyan_colorspace {
    CYAN_XYZ        =0,
    CYAN_xyY        =1,
    CYAN_Lab        =2,
    CYAN_LCHab      =3,
    CYAN_Luv        =4,
    CYAN_LCHuv      =5,
    CYAN_RGB        =6,
    CYAN_spectrum   =7
} ;

enum cyan_refwhite {
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
} ;

enum cyan_rgb_workspace {
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
} ;

// All colorspace conversions are made for
// D_50 XYZ space

void RGB_to_XYZ( enum cyan_rgb_workspace RGB_space, double R, double G, double B, double* X, double* Y, double* Z ) ;  // TODO
void XYZ_to_XYZ( enum cyan_rgb_workspace RGB_space, double X, double Y, double Z, double* R, double* G, double* B ) ;  // TODO

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
