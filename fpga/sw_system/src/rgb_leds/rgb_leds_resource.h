#ifndef SW_SYSTEM_RGB_LEDS_RESOURCE_H
#define SW_SYSTEM_RGB_LEDS_RESOURCE_H

#include "server/server.h"

callback_t *rgb_leds_resource_set_color(request_t *req, response_t *res);
callback_t *rgb_leds_resource_set_frequency (request_t *req, response_t *res);
callback_t *rgb_leds_resource_set_offset(request_t *req, response_t *res);
callback_t *rgb_leds_resource_set_mode(request_t *req, response_t *res);
callback_t *rgb_leds_resource_auto_configure(request_t *req, response_t *res);

#endif //SW_SYSTEM_RGB_LEDS_RESOURCE_H
