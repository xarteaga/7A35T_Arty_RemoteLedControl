#include <stdio.h>

#include "xil_types.h"

#include "colors.h"

#include "math.h"

struct rgb_t {
    double r, g, b;
};

color_rgb_t colors_convert_hsl_rgb (color_hsl_t hsl){

    double hue = hsl.h*360.0;
    double saturation = hsl.s;
    double lightness = hsl.l;

    struct rgb_t rgb1, rgbResult;

    double chroma = ( 1.0 - fabs( 2.0 * lightness - 1.0 ) ) * saturation;
    double h1 = hue / 60.0;
    double x = chroma * ( 1.0 - fabs( fmodf(h1, 2.0) - 1.0 ));

    if ( ( 0 <= h1 ) && ( h1 < 1 ) ) {
        rgb1.r = chroma;
        rgb1.g = x;
        rgb1.b = 0.0;
    } else if ( ( 1 <= h1 ) && ( h1 < 2 ) ) {
        rgb1.r = x;
        rgb1.g = chroma;
        rgb1.b = 0.0;
    } else if ( ( 2 <= h1 ) && ( h1 < 3 ) ) {
        rgb1.r = 0.0;
        rgb1.g = chroma;
        rgb1.b = x;
    } else if ( ( 3 <= h1 ) && ( h1 < 4 ) ) {
        rgb1.r = 0.0;
        rgb1.g = x;
        rgb1.b = chroma;
    } else if ( ( 4 <= h1 ) && ( h1 < 5 ) ) {
        rgb1.r = x;
        rgb1.g = 0.0;
        rgb1.b = chroma;
    } else if ( ( 5 <= h1 ) && ( h1 < 6 ) ) {
        rgb1.r = chroma;
        rgb1.g = 0;
        rgb1.b = x;
    } else {
        rgb1.r = 0.0;
        rgb1.g = 0.0;
        rgb1.b = 0.0;
    }

    double m = lightness - 0.5 * chroma;

    rgbResult.r = rgb1.r + m;
    rgbResult.g = rgb1.g + m;
    rgbResult.b = rgb1.b + m;

    color_rgb_t rgb ;
    rgb.r = (u8)(255.0*rgbResult.r);
    rgb.g = (u8)(255.0*rgbResult.g);
    rgb.b = (u8)(255.0*rgbResult.b);


    return rgb;

}