#include <math.h>
#include "cyan/color/color.h"


#include <stdio.h>

void XYZ_to_RGB(
        enum cyan_rgb_workspace RGB_space,
        double X, double Y, double Z,
        double* R, double* G,double* B) {

    // R,G,B must be in the nominal range [0,1]
    // X,Y,Z will also be in the range[0,1]
    // Ref white for XYZ is D_50 illuminant

    double r,g,b ;  // RGB components made linear to energy
    double k ;      // Used in L* Gamma

    switch( RGB_space ) {
        case CYAN_RGB_ADOBE_1998:
            // Gamma^-1 : 1/2.2 = 0.454545
            // Ref White: D65
            // Adaptation Method : Bradford

		r = 	1.9624274 * X	 - 0.6105343 * Y	- 0.3413404 * Z;
		g = 	- 0.9787684 * X  + 1.9161415 * Y	+ 0.0334540 * Z;
		b = 	0.0286869 * X	 - 0.1406752 * Y	+ 1.3487655 * Z;	
		
		//TODO ????		
		if(g<0.0)
			g *= (-1);

		*R = pow(r, 0.454545);
		*G = pow(g, 0.454545); 
		*B = pow(b, 0.454545); 
            	break ;
	
       	case CYAN_RGB_APPLE:
            // Gamma^-1 : 1/1.8 = 0.5555555
            // Ref White: D65
            // Adaptation Method : Bradford
		r = 	2.8510695 * X	 - 1.3605261 * Y	- 0.4708281 * Z;
		g =	- 1.0927680 * X	 + 2.0348871 * Y	- 0.0227598 * Z;
		b =	 0.1027403 * X	 - 0.2964984 * Y	+ 1.4510659 * Z;	
		
		//TODO ????		
		if(g<0.0)
			g *= (-1);

		*R = pow(r, 0.555555);
		*G = pow(g, 0.555555); 
		*B = pow(b, 0.555555); 
            	break ;

	 case CYAN_RGB_BEST:
            // Gamma^-1 : 1/2.2 = 0.454545
            // Ref White: D50
            // Adaptation Method : None
			    
		r = 	1.7552599 * X	 - 0.4836786 * Y	 - 0.2530000 * Z;
		g = 	- 0.5441336 * X  + 1.5068789 * Y	 + 0.0215528 * Z;
		b = 	 0.0063467 * X	 - 0.0175761 *Y 	 + 1.2256959 * Z;		
		
		//TODO ????		
		if(g<0.0)
			g *= (-1);

		*R = pow(r, 0.454545);
		*G = pow(g, 0.454545); 
		*B = pow(b, 0.454545); 
            	break ;
	 default:
		fprintf(stderr, "XYZ_to_RGB() : colortype asked not implemented yet.\n");
		break ;
    }
}
