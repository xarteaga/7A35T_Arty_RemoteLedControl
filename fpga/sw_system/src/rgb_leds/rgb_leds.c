/* Standard C includes */
#include <stdio.h>
#include <string.h>
#include <math.h>

/* Xilinx Includes */

/* Project Includes */
#include "rgb_leds.h"
#include "rgb_leds_cmd.h"
#include "colors.h"
#include "tinysh.h"
#include "scheduler.h"
#include "server.h"
#include "rgb_leds_resource.h"

/* Variables */
static rgb_leds_t *rgb_leds = RGB_LEDS_BASE_ADDR;
static rgb_leds_mode_t rgb_leds_mode = RGB_LEDS_MODE_UNDEFINED;
static color_hsl_t rgb_leds_auto_colors [RGB_LEDS_N];

/* Function Prototypes */
void rgb_leds_auto();
void rgb_leds_task(u32 elapsed);

/* Command entries */
static tinysh_cmd_t  tinysh_rgb_leds = {0, "rgb_leds", "WiFi Controller Reset", "<chan 0-3> <red> <green> <blue>", rgb_leds_cmd, 0, 0, 0};

/* Scheduler entry */
static scheduler_entry_t leds_rgb_scheduler_entry = {0, 1000, rgb_leds_task};

/* Resource entries */
static resource_t rgb_leds_r1 = { "/rgb_leds/freq", (callback_t*) rgb_leds_resource_set_frequency};
static resource_t rgb_leds_r2 = { "/rgb_leds/color", (callback_t*) rgb_leds_resource_set_color};
static resource_t rgb_leds_r3 = { "/rgb_leds/offset", (callback_t*) rgb_leds_resource_set_offset};
static resource_t rgb_leds_r4 = { "/rgb_leds/auto", (callback_t*)rgb_leds_resource_set_mode};
static resource_t rgb_leds_r5 = { "/rgb_leds/manual", (callback_t*)rgb_leds_resource_set_mode};
static resource_t rgb_leds_r6 = { "/rgb_leds/period", (callback_t*)rgb_leds_resource_set_period};

void rgb_leds_init(u32 f) {
    /* Set all zeros */
    memset(rgb_leds, 0, sizeof(rgb_leds_t));

    /* Set PWM divider */
    rgb_leds_set_freq(f);

    /* initialize mode */
    rgb_leds_set_mode(RGB_LEDS_MODE_MANUAL);

    /* Add VaXi OS Commands */
    tinysh_add_command(&tinysh_rgb_leds);

    /* Add scheduler entry */
    scheduler_add_entry(&leds_rgb_scheduler_entry);

    /* Add server entries */
    server_add_resource(&rgb_leds_r1);
    server_add_resource(&rgb_leds_r2);
    server_add_resource(&rgb_leds_r3);
    server_add_resource(&rgb_leds_r4);
    server_add_resource(&rgb_leds_r5);
    server_add_resource(&rgb_leds_r6);
}

void rgb_leds_set_mode (rgb_leds_mode_t m){
    u32 i = 0;
    color_rgb_t rgb;

    /* If mode is AUTO, then set default values */
    if (m == RGB_LEDS_MODE_AUTO) {


        for (i = 0; i < RGB_LEDS_N; i++) {
            /* Temporal color */
            color_hsl_t *hsl = &(rgb_leds_auto_colors[i]);

            /* Set initial color */
            hsl->h = ((float) i/ (float)RGB_LEDS_N);
            hsl->s = 0.99;  /* Full saturation */
            hsl->l = 0.1;  /* Half Lightness */

            /* Convert to RGB */
            rgb = colors_convert_hsl_rgb(*hsl);

            /* Set PWM */
            rgb_leds->channels[i].red = rgb.r;
            rgb_leds->channels[i].green = rgb.g;
            rgb_leds->channels[i].blue = rgb.b;
        }
    }

    /* Set mode */
    rgb_leds_mode = m;
}

rgb_led_t* rgb_leds_get_channel(u32 chan) {
    /* Return null by default */
    rgb_led_t* ret = NULL;

    /* Check channel index to avoid Segmentation fault */
    if (chan < RGB_LEDS_N)
        ret = &(rgb_leds->channels[chan]);

    return ret;
}

void rgb_leds_set_freq(u32 f) {
    /* Set PWM divider */
    rgb_leds->divider = (u32)((RGB_LEDS_CLK_BASE>>8)/f);
}

int rgb_leds_set_float(u8 ch, float r, float g, float b) {
    int ret = 0;
    if (ch < RGB_LEDS_N) {
        rgb_leds->channels[ch].red = (u8) (256.0 * r);
        rgb_leds->channels[ch].green = (u8) (256.0 * g);
        rgb_leds->channels[ch].blue = (u8) (256.0 * b);
    } else {
        ret = (-1);
    }

    return ret;
}

int rgb_leds_set_hex_color (u32 ch, u32 hex) {
    int ret = 0;
    if (ch < RGB_LEDS_N) {
        rgb_leds->channels[ch].red = (u8) ((hex >> 16) & 0xFF);
        rgb_leds->channels[ch].green = (u8) ((hex >> 8) & 0xFF);
        rgb_leds->channels[ch].blue = (u8) ((hex & 0xFF));
    } else {
        ret = (-1);
    }

    return ret;
}

int rgb_leds_set_offset(u32 ch, u32 offset) {
    int ret = 0;
    if (ch < RGB_LEDS_N) {
        rgb_leds->channels[ch].offset = (u8) offset;
    } else {
        ret = (-1);
    }

    return ret;
}

void rgb_leds_auto_period(u32 period) {
    /* Check period boundary */
    if (period < 1000) {
        period = 1000; // Limit minimum period to 1 s
    }

    xil_printf("Setting period to %d", period);
    leds_rgb_scheduler_entry.period = period/100;
}

void rgb_leds_auto() {
    u32 i = 0;
    color_rgb_t rgb;

    for (i = 0; i < RGB_LEDS_N; i++) {
        /* Temporal color */
        color_hsl_t *hsl = &(rgb_leds_auto_colors[i]);

        /* Rotate color */
        hsl->h = (float)fmod(hsl->h + (float)0.01, (float)1);

        /* Convert to RGB */
        rgb = colors_convert_hsl_rgb(*hsl);

        /* Set PWM */
        rgb_leds->channels[i].red = rgb.r;
        rgb_leds->channels[i].green = rgb.g;
        rgb_leds->channels[i].blue = rgb.b;
    }
}

void rgb_leds_task(u32 elapsed) {
    switch(rgb_leds_mode){
        case RGB_LEDS_MODE_UNDEFINED:
            rgb_leds_mode = RGB_LEDS_MODE_MANUAL;
            break;
        case RGB_LEDS_MODE_MANUAL:
            /* Do Nothing */;
            break;
        case RGB_LEDS_MODE_AUTO:
            rgb_leds_auto();
            break;
        default:
            rgb_leds_mode = RGB_LEDS_MODE_MANUAL;
    }
}