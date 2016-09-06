#include <stdio.h>

#include "xil_types.h"

#include "colors.h"

#include "math.h"

float hue2rgb(float p, float q, float t){
    if(t < 0.0)
        t += 1;
    if(t > 1.0)
        t -= 1;

    if(t < 0.1666667)
        return (p + (q - p) * 6.0 * t);
    if(t < 0.5)
        return q;
    if(t < 0.6666667)
        return (p + (q - p) * (0.6666667 - t) * 6.0);
    return p;
}

struct rgb_t {
    float r, g, b;
};

color_rgb_t colors_convert_hsl_rgb (color_hsl_t hsl){

    float hue = hsl.h*360.0;
    float saturation = hsl.s;
    float lightness = hsl.l;

    struct rgb_t rgb1, rgbResult;

    float chroma = ( 1.0 - (float) fabs( 2.0 * lightness - 1.0 ) ) * saturation;
    float h1 = hue / 60.0;
    float x = chroma * ( 1.0 - (float) fabs( fmodf(h1, 2.0) - 1.0 ));

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

    float m = lightness - 0.5 * chroma;

    rgbResult.r = rgb1.r + m;
    rgbResult.g = rgb1.g + m;
    rgbResult.b = rgb1.b + m;

    color_rgb_t rgb ;
    rgb.r = (u8)(255.0*rgbResult.r);
    rgb.g = (u8)(255.0*rgbResult.g);
    rgb.b = (u8)(255.0*rgbResult.b);


    return rgb;

}