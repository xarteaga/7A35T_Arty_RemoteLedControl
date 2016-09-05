#ifndef SW_SYSTEM_BOARD_RGB_LEDS_RESOURCE_H
#define SW_SYSTEM_BOARD_RGB_LEDS_RESOURCE_H

#include "../server.h"

void *board_rgb_leds_resource_set_color(request_t *req, response_t *res);
void *board_rgb_leds_resource_set_frequency (request_t *req, response_t *res);
void *board_rgb_leds_resource_set_offset(request_t *req, response_t *res);

#endif //SW_SYSTEM_BOARD_RGB_LEDS_RESOURCE_H
