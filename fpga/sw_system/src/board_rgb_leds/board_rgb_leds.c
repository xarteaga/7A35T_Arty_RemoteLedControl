
#include <stdio.h>
#include <string.h>

#include "board_rgb_leds.h"
#include "../remote.h"

#include "../tinysh.h"

board_rgb_leds_t *board_rgb_leds = BOARD_RGB_LEDS_BASE_ADDR;
static tinysh_cmd_t  tinysh_board_rgb_leds = {0, "board_rgb_leds", "WiFi Controller Reset", "<chan 0-3> <red> <green> <blue>", board_rgb_leds_cmd, 0, 0, 0};

void board_rgb_leds_init(u32 f) {
    /* Set all zeros */
    memset(board_rgb_leds, 0, sizeof(board_rgb_leds_t));

    /* Set PWM divider */
    board_rgb_leds_set_freq(f);

    /* VaXi OS Commands */
    tinysh_add_command(&tinysh_board_rgb_leds);
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

void board_rgb_leds_cmd (int argc, char ** argv){
    int err = 1;
    int chan;
    float r, g, b;

    if (argc != 5) {
        remote_print("Wrong usage. board_rgb_leds <chan 0-3> <red> <green> <blue>\r\n");
        err = -1;
    }

    /* Get channel number */
    if (err > 0){
        err = sscanf(argv[1], "%d", &chan);
        if (err != 1){
            remote_print("Channel selector (%s) has the wrong format. It must be an integer lower than %d.\r\n",
                argv[1], BOARD_RGB_LEDS_N);
            err = -1;
        }
    }

    /* Get red */
    if (err > 0){
        err = sscanf(argv[2], "%f", &r);
        if (err != 1 || r > 1.0 || r < 0.0){
            remote_print("Color selector (%s) has the wrong format. It must be a float 0-1.\r\n",
                       argv[2]);
            err = -1;
        }
    }

    /* Get green */
    if (err > 0){
        err = sscanf(argv[3], "%f", &g);
        if (err != 1 || g > 1.0 || g < 0.0){
            remote_print("Color selector (%s) has the wrong format. It must be a float 0-1.\r\n",
                       argv[3]);
            err = -1;
        }
    }

    /* Get blue */
    if (err > 0){
        err = sscanf(argv[4], "%f", &b);
        if (err != 1 || b > 1.0 || b < 0.0){
            remote_print("Color selector (%s) has the wrong format. It must be a float 0-1.\r\n",
                       argv[4]);
            err = -1;
        }
    }

    /* Set color */
    if (err > 0) {
        remote_print("OK!\r\n");
        board_rgb_leds_set_float((u8) chan, r, g, b);
    }
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