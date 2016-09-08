
#ifndef SW_SYSTEM_RGB_LEDS_H
#define SW_SYSTEM_RGB_LEDS_H

#include "xil_types.h"
#include "xparameters.h"

/* Define the massive_pwm instance to use */
#ifndef RGB_LEDS_EXTERNAL
#define RGB_LEDS_BASE_ADDR ((rgb_leds_t*) XPAR_MASSIVE_PWM_0_S00_AXI_BASEADDR)
#define RGB_LEDS_N ((u32) XPAR_MASSIVE_PWM_0_NUM_LEDS)
#define RGB_LEDS_CLK_BASE ((u32)XPAR_CPU_CORE_CLOCK_FREQ_HZ)
#else
#define RGB_LEDS_BASE_ADDR ((rgb_leds_t*) XPAR_MASSIVE_PWM_1_S00_AXI_BASEADDR)
#define RGB_LEDS_N ((u32) XPAR_MASSIVE_PWM_1_NUM_LEDS)
#define RGB_LEDS_CLK_BASE ((u32)XPAR_CPU_CORE_CLOCK_FREQ_HZ)
#endif

typedef struct {
    u8 red;
    u8 green;
    u8 blue;
    u8 offset;
} rgb_led_t;

typedef struct {
    u32 divider;
    rgb_led_t channels[RGB_LEDS_N];
} rgb_leds_t;

typedef enum {
    RGB_LEDS_MODE_UNDEFINED,
    RGB_LEDS_MODE_MANUAL,
    RGB_LEDS_MODE_AUTO
} rgb_leds_mode_t;

/* Function prototypes */
void rgb_leds_init(u32 f);
rgb_led_t* rgb_leds_get_channel(u32 chan);
void rgb_leds_set_freq(u32 f);
int rgb_leds_set_hex_color (u32 ch, u32 hex);
int rgb_leds_set_offset(u32 ch, u32 offset);
int rgb_leds_set_float(u8 ch, float r, float g, float b);
void rgb_leds_set_mode (rgb_leds_mode_t m);
void rgb_leds_auto_period(u32 period);

#endif //SW_SYSTEM_RGB_LEDS_H
