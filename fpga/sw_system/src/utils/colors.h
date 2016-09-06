
#ifndef SW_SYSTEM_COLORS_H
#define SW_SYSTEM_COLORS_H

typedef struct {
    float h;    /* Hue        */
    float s;    /* Saturation */
    float l;    /* Lightness  */
} color_hsl_t;

typedef struct {
    u8 r;    /* Reg        */
    u8 g;    /* Green      */
    u8 b;    /* Blue       */
} color_rgb_t;

/* Function prototypes */
color_rgb_t colors_convert_hsl_rgb (color_hsl_t hsl);

#endif //SW_SYSTEM_COLORS_H
