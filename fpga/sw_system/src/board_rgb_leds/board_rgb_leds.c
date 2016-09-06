
#include <stdio.h>
#include <string.h>
#include <xbasic_types.h>

#include "board_rgb_leds.h"
#include "board_rgb_leds_cmd.h"
#include "colors.h"

#include "tinysh.h"

board_rgb_leds_t *board_rgb_leds = BOARD_RGB_LEDS_BASE_ADDR;

/* Command entries */
static tinysh_cmd_t  tinysh_board_rgb_leds = {0, "board_rgb_leds", "WiFi Controller Reset", "<chan 0-3> <red> <green> <blue>", board_rgb_leds_cmd, 0, 0, 0};

/* Driver mode */
board_rgb_leds_mode_t board_rgb_leds_mode = BOARD_RGB_LEDS_MODE_UNDEFINED;

color_hsl_t board_rgb_leds_auto_colors [BOARD_RGB_LEDS_N];

/* Function Prototypes */
void board_rgb_leds_auto(Xboolean reset);

void board_rgb_leds_init(u32 f) {
    /* Set all zeros */
    memset(board_rgb_leds, 0, sizeof(board_rgb_leds_t));

    /* Set PWM divider */
    board_rgb_leds_set_freq(f);

    /* initialize mode */
    board_rgb_leds_set_mode(BOARD_RGB_LEDS_MODE_MANUAL);

    /* Add VaXi OS Commands */
    tinysh_add_command(&tinysh_board_rgb_leds);
}

void board_rgb_leds_set_mode (board_rgb_leds_mode_t m){
    /* Set mode */
    board_rgb_leds_mode = m;

    /* If mode is AUTO, then set default values */
    if (m == BOARD_RGB_LEDS_MODE_AUTO) {
        board_rgb_leds_auto(TRUE);
    }
}

board_rgb_led_t* board_rgb_leds_get_channel(u32 chan) {
    /* Return null by default */
    board_rgb_led_t* ret = NULL;

    /* Check channel index to avoid Segmentation fault */
    if (chan < BOARD_RGB_LEDS_N)
        ret = &(board_rgb_leds->channels[chan]);

    return ret;
}

void board_rgb_leds_set_freq(u32 f) {
    /* Set PWM divider */
    board_rgb_leds->divider = (u32)((BOARD_RGB_LEDS_CLK_BASE>>8)/f);
}

int board_rgb_leds_set_float(u8 ch, float r, float g, float b) {
    int ret = 0;
    if (ch < BOARD_RGB_LEDS_N) {
        board_rgb_leds->channels[ch].red = (u8) (256.0 * r);
        board_rgb_leds->channels[ch].green = (u8) (256.0 * g);
        board_rgb_leds->channels[ch].blue = (u8) (256.0 * b);
    } else {
        ret = (-1);
    }

    return ret;
}

int board_rgb_leds_set_hex_color (u32 ch, u32 hex) {
    int ret = 0;
    if (ch < BOARD_RGB_LEDS_N) {
        board_rgb_leds->channels[ch].red = (u8) ((hex >> 16) & 0xFF);
        board_rgb_leds->channels[ch].green = (u8) ((hex >> 8) & 0xFF);
        board_rgb_leds->channels[ch].blue = (u8) ((hex & 0xFF));
    } else {
        ret = (-1);
    }

    return ret;
}

int board_rgb_leds_set_offset(u32 ch, u32 offset) {
    int ret = 0;
    if (ch < BOARD_RGB_LEDS_N) {
        board_rgb_leds->channels[ch].offset = offset;
    } else {
        ret = (-1);
    }

    return ret;
}

void board_rgb_leds_auto(Xboolean reset) {
    u32 i = 0;

    for (i = 0; i < BOARD_RGB_LEDS_N; i++) {
        /* Temporal color */
        color_hsl_t hsl = board_rgb_leds_auto_colors[i];
        color_rgb_t rgb;

        /* Rotate color */
        if (reset ==  TRUE) {
            printf("PROBE!\r\n");
            hsl.h = ((float) i/ (float)BOARD_RGB_LEDS_N);
            hsl.s = 0.9;  /* Full saturation */
            hsl.l = 0.1;  /* Half Lightness */

        } else {
            hsl.h += 0.001;
        }

        /* Check boundaries */
        if (hsl.h > 1.0){
            hsl.h -= 1.0;
        }

        /* Set Channel color */
        board_rgb_leds_auto_colors[i] = hsl;

        /* Convert to RGB */
        rgb = colors_convert_hsl_rgb(hsl);

        /* Set PWM */
        board_rgb_leds->channels[i].red = rgb.r;
        board_rgb_leds->channels[i].green = rgb.g;
        board_rgb_leds->channels[i].blue = rgb.b;

    }
}


void board_rgb_leds_task() {
    switch(board_rgb_leds_mode){
        case BOARD_RGB_LEDS_MODE_UNDEFINED:
            board_rgb_leds_mode = BOARD_RGB_LEDS_MODE_MANUAL;
            break;
        case BOARD_RGB_LEDS_MODE_MANUAL:
            /* Do Nothing */;
            break;
        case BOARD_RGB_LEDS_MODE_AUTO:
            board_rgb_leds_auto(FALSE);
            break;
        default:
            board_rgb_leds_mode = BOARD_RGB_LEDS_MODE_MANUAL;
    }
}