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
} cyan_rgb_workingspace ;









#endif
