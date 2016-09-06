
#include <stdio.h>
#include <string.h>

#include "board_rgb_leds.h"

#include "server.h"
#include "utils.h"

char board_rgb_leds_json_buff[1024];
char board_rgb_leds_freq_str[32];

char *board_rgb_leds_json () {
    uint32_t n, i;
    board_rgb_led_t *rgb_chan = NULL;

    n = sprintf(board_rgb_leds_json_buff, "[");
    for(i = 0; i < BOARD_RGB_LEDS_N; i++){
        /* Add colon if required */
        if (i!=0){
            board_rgb_leds_json_buff[n] = ',';
            n++;
        }

        /* Get RGB channel */
        rgb_chan = board_rgb_leds_get_channel(i);

        /* Add RGB Channel */
        n += sprintf(board_rgb_leds_json_buff + n, "{\"offset\": %d, \"r\":%d, \"g\":%d, \"b\":%d}", \
				rgb_chan->offset, rgb_chan->red, rgb_chan->green, rgb_chan->blue);
    }

    n += sprintf(board_rgb_leds_json_buff + n, "]");


    return board_rgb_leds_json_buff;
}

callback_t *board_rgb_leds_resource_set_frequency (request_t *req, response_t *res) {
    char *argv[10];
    int argn = path2args(req->url, argv);
    int err = 1;
    float f;

    /* Check format */
    if (argn < 3 ) {
        err = -1;
    }

    /* Parse frequency */
    if (err > 0) {
        /* Scan value */
        err = sscanf(argv[2], "%f", &f);

        /* Check for errors */
        if (err < 1) {
            err = -1;
        } else {
            /* Set frequency */
            board_rgb_leds_set_freq((u32) f);
        }
    }

    if (err < 0) {
        res->code = RES_BAD_REQUEST;
        res->content = "Bad number of arguments. Usage: /board_rgb_leds/freq/$Freq. in Hz$\r\n";
    } else {
        sprintf(board_rgb_leds_freq_str, "%d Hz\r\n", (u32)f);

        res->code = RES_OK;
        res->content = board_rgb_leds_freq_str;
    }

    return NULL;
}

callback_t *board_rgb_leds_resource_set_color(request_t *req, response_t *res){
    char *argv[10];
    int argn = path2args(req->url, argv);
    int err = 0;
    u32 hex;
    u32 chan;

    /* Check format */
    if (argn < 4 ) {
        err = -1;
    }

    /* Parse channel */
    if (err >= 0) {
        /* Scan value */
        err = sscanf(argv[2], "%d", &chan);

        /* Check for errors */
        if (err < 1) {
            err = -1;
        }
    }

    /* Parse hex value */
    if (err >= 0) {
        /* Scan value */
        err = sscanf(argv[3], "%X", &hex);

        /* Check for errors */
        if (err < 1 || hex > 0xFFFFFF) {
            err = -1;
        }
    }

    /* Set frequency */
    if (err >= 0) {
        err = board_rgb_leds_set_hex_color(chan, hex);
    }

    /* Check for errors */
    if (err < 0) {
        res->code = RES_BAD_REQUEST;
        res->content = "Bad number of arguments. Usage: /board_rgb_leds/color/$channel$/$hex. code$\r\n";
    } else {
        res->code = RES_OK;
        res->content = board_rgb_leds_json();
    }

    return NULL;
}

callback_t *board_rgb_leds_resource_set_offset(request_t *req, response_t *res){
    char *argv[10];
    int argn = path2args(req->url, argv);
    int err = 0;
    u32 offset;
    u32 chan;

    /* Check format */
    if (argn != 4 ) {
        err = -1;
    }

    /* Parse channel */
    if (err >= 0) {
        /* Scan value */
        err = sscanf(argv[2], "%d", &chan);

        /* Check for errors */
        if (err < 1) {
            err = -1;
        }
    }

    /* Parse hex value */
    if (err >= 0) {
        /* Scan value */
        err = sscanf(argv[3], "%d", &offset);

        /* Check for errors */
        if (err < 1 || offset > 0xFF) {
            err = -1;
        }
    }

    /* Set frequency */
    if (err >= 0) {
        err = board_rgb_leds_set_offset(chan, offset);
    }

    /* Check for errors */
    if (err < 0) {
        res->code = RES_BAD_REQUEST;
        res->content = "Bad number of arguments. Usage: /board_rgb_leds/offset/$channel$/$offset 0 - 255$\r\n";
    } else {
        res->code = RES_OK;
        res->content = board_rgb_leds_json();
    }

    return NULL;
}

callback_t *board_rgb_leds_resource_set_auto(request_t *req, response_t *res){
    char *argv[10];
    int argn = path2args(req->url, argv);
    int err = 0;

    /* Check format */
    if (argn != 2 ) {
        err = -1;
    }

    /* Parse channel */
    if (err >= 0) {
        if (strcmp(argv[1], "auto") == 0) {
            board_rgb_leds_set_mode(BOARD_RGB_LEDS_MODE_AUTO);
        } else {
            board_rgb_leds_set_mode(BOARD_RGB_LEDS_MODE_MANUAL);
        }
    }

    /* Check for errors */
    if (err < 0) {
        res->code = RES_BAD_REQUEST;
        res->content = "Bad number of arguments. Usage: /board_rgb_leds/{auto|manual}\r\n";
    } else {
        res->code = RES_OK;
        res->content = board_rgb_leds_json();
    }

    return NULL;
}