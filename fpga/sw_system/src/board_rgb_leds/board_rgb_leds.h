
#ifndef SW_SYSTEM_BOARD_RGB_LEDS_H
#define SW_SYSTEM_BOARD_RGB_LEDS_H

#include "xil_types.h"
#include "xparameters.h"

#define BOARD_RGB_LEDS_BASE_ADDR XPAR_MASSIVE_PWM_0_S00_AXI_BASEADDR
#define BOARD_RGB_LEDS_N XPAR_MASSIVE_PWM_0_NUM_LEDS
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

/* Function prototypes */
void board_rgb_leds_init(u32 f);
int board_rgb_leds_set(u8 ch, float r, float g, float b);
void board_rgb_leds_cmd (int argc, char ** argv);

#endif //SW_SYSTEM_BOARD_RGB_LEDS_H