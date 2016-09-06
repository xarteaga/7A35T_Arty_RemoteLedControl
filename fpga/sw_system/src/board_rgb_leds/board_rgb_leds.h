
#ifndef SW_SYSTEM_BOARD_RGB_LEDS_H
#define SW_SYSTEM_BOARD_RGB_LEDS_H

#include "xil_types.h"
#include "xparameters.h"

#define BOARD_RGB_LEDS_BASE_ADDR ((board_rgb_leds_t*) XPAR_MASSIVE_PWM_0_S00_AXI_BASEADDR)
#define BOARD_RGB_LEDS_N ((u32) XPAR_MASSIVE_PWM_0_NUM_LEDS)
#define BOARD_RGB_LEDS_CLK_BASE ((u32)XPAR_CPU_CORE_CLOCK_FREQ_HZ)

typedef struct {
    u8 red;
    u8 green;
    u8 blue;
    u8 offset;
} board_rgb_led_t;

typedef struct {
    u32 divider;
    board_rgb_led_t channels[BOARD_RGB_LEDS_N];
} board_rgb_leds_t;

typedef enum {
    BOARD_RGB_LEDS_MODE_UNDEFINED,
    BOARD_RGB_LEDS_MODE_MANUAL,
    BOARD_RGB_LEDS_MODE_AUTO
} board_rgb_leds_mode_t;

/* Function prototypes */
void board_rgb_leds_init(u32 f);
board_rgb_led_t* board_rgb_leds_get_channel(u32 chan);
void board_rgb_leds_set_freq(u32 f);
int board_rgb_leds_set_hex_color (u32 ch, u32 hex);
int board_rgb_leds_set_offset(u32 ch, u32 offset);
int board_rgb_leds_set_float(u8 ch, float r, float g, float b);
void board_rgb_leds_set_mode (board_rgb_leds_mode_t m);
void board_rgb_leds_task();

#endif //SW_SYSTEM_BOARD_RGB_LEDS_H
