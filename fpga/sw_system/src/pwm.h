/*
 * pwm.h
 *
 *  Created on: 18/06/2016
 *      Author: xavier
 */

#ifndef PWM_H_
#define PWM_H_

#include <inttypes.h>

#include "xparameters.h"
#include "server.h"

#define PWM_NUM_CHANNELS 10

typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t offset;
} led_t;

typedef struct {
	uint32_t period;
	led_t channels[PWM_NUM_CHANNELS];
} massive_pwm_t;

void *pwm_callback(request_t *req, response_t *res);

#endif /* PWM_H_ */
