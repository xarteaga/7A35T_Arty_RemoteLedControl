
#include <stdio.h>
#include <string.h>

#include "rgb_leds.h"

#include "server/server.h"
#include "utils.h"

char rgb_leds_json_buff[1024];
char rgb_leds_freq_str[32];

char *rgb_leds_json () {
    int n, i;
    rgb_led_t *rgb_chan = NULL;

    n = sprintf(rgb_leds_json_buff, "[");
    for(i = 0; i < RGB_LEDS_N; i++){
        /* Add colon if required */
        if (i!=0){
            rgb_leds_json_buff[n] = ',';
            n++;
        }

        /* Get RGB channel */
        rgb_chan = rgb_leds_get_channel((u32)i);

        /* Add RGB Channel */
        n += sprintf(rgb_leds_json_buff + n, "{\"offset\": %d, \"r\":%d, \"g\":%d, \"b\":%d}", \
				rgb_chan->offset, rgb_chan->red, rgb_chan->green, rgb_chan->blue);
    }

    (void) sprintf(rgb_leds_json_buff + n, "]");


    return rgb_leds_json_buff;
}

callback_t *rgb_leds_resource_set_frequency (request_t *req, response_t *res) {
    char *argv[10];
    int argn = path2args(req->url, argv);
    int err = 1;
    float f = 0.0;

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
            rgb_leds_set_freq((u32) f);
        }
    }

    if (err < 0) {
        res->code = RES_BAD_REQUEST;
        res->content = "Bad number of arguments. Usage: /rgb_leds/freq/$Freq. in Hz$\r\n";
    } else {
        sprintf(rgb_leds_freq_str, "%d Hz\r\n", (int)f);

        res->code = RES_OK;
        res->content = rgb_leds_freq_str;
    }

    return NULL;
}

callback_t *rgb_leds_resource_set_color(request_t *req, response_t *res){
    char *argv[10];
    int argn = path2args(req->url, argv);
    int err = 0;
    int hex = 0;
    int chan = 0;

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
        err = rgb_leds_set_hex_color((u32)chan, (u32)hex);
    }

    /* Check for errors */
    if (err < 0) {
        res->code = RES_BAD_REQUEST;
        res->content = "Bad number of arguments. Usage: /rgb_leds/color/$channel$/$hex. code$\r\n";
    } else {
        res->code = RES_OK;
        res->content = rgb_leds_json();
    }

    return NULL;
}

callback_t *rgb_leds_resource_set_offset(request_t *req, response_t *res){
    char *argv[10];
    int argn = path2args(req->url, argv);
    int err = 0;
    int offset = 0;
    int chan = 0;

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
        err = rgb_leds_set_offset((u32)chan, (u32)offset);
    }

    /* Check for errors */
    if (err < 0) {
        res->code = RES_BAD_REQUEST;
        res->content = "Bad number of arguments. Usage: /rgb_leds/offset/$channel$/$offset 0 - 255$\r\n";
    } else {
        res->code = RES_OK;
        res->content = rgb_leds_json();
    }

    return NULL;
}

callback_t *rgb_leds_resource_set_mode(request_t *req, response_t *res){
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
            rgb_leds_set_mode(RGB_LEDS_MODE_AUTO);
        } else {
            rgb_leds_set_mode(RGB_LEDS_MODE_MANUAL);
        }
    }

    /* Check for errors */
    if (err < 0) {
        res->code = RES_BAD_REQUEST;
        res->content = "Bad number of arguments. Usage: /rgb_leds/{auto|manual}\r\n";
    } else {
        res->code = RES_OK;
        res->content = rgb_leds_json();
    }

    return NULL;
}
callback_t *rgb_leds_resource_auto_configure(request_t *req, response_t *res){
    char *argv[10];
    int argn = path2args(req->url, argv);
    int err = 0;
    float temp;

    /* Check format */
    if (argn != 3 ) {
        err = -1;
    }

    /* Parse parameter */
    if (err >= 0) {
        err = sscanf(argv[2], "%f", &temp);
        if (err != 1) {
            err = -1;
        }
    }

    /* Check paramater */
    if (strcmp("saturation", argv[1]) == 0){
        if (temp > 0.0 && temp <= 1.0) {
            rgb_leds_set_saturation(temp);
        } else {
            err = -1;
        }
    } else if (strcmp("lightness", argv[1]) == 0){
        if (temp > 0.0 && temp <= 1.0) {
            rgb_leds_set_lightness(temp);
        } else {
            err = -1;
        }
    } else if (strcmp("period", argv[1]) == 0){
        if (temp > 0.0) {
            rgb_leds_auto_period((u32)(1000.0*temp));
        } else {
            err = -1;
        }
    } else {
        err = -1;
    }

    /* Check for errors */
    if (err < 0) {
        res->code = RES_BAD_REQUEST;
        res->content = "Bad number of arguments. Usage: /rgb_leds/period/{seconds}\r\n";
    } else {
        res->code = RES_OK;
        res->content = rgb_leds_json();
    }

    return NULL;
}
