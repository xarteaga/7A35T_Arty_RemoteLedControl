/*
 * pwm.c
 *
 *  Created on: 18/06/2016
 *      Author: xavier
 */

#include <inttypes.h>
#include <string.h>
#include <stdio.h>

#include "pwm.h"
#include "server.h"
#include "utils.h"

#define VERBOSE

typedef enum {RED, GREEN, BLUE, RGB} colors_t;
massive_pwm_t *pwm = (massive_pwm_t *)XPAR_MASSIVE_PWM_1_S00_AXI_BASEADDR;

char json_buff[1024];

char* getJSON () {
	uint32_t n, i;
	n = sprintf(json_buff, "[");
	for(i = 0; i < PWM_NUM_CHANNELS; i++){
		if (i!=0){
			json_buff[n] = ',';
			n++;
		}
		n += sprintf(json_buff + n, "{\"offset\": %d, \"r\":%d, \"g\":%d, \"b\":%d}", \
				pwm->channels[i].offset, pwm->channels[i].red, pwm->channels[i].green, pwm->channels[i].blue);
	}

	n += sprintf(json_buff + n, "]");


	return json_buff;
}

callback_t *pwm_callback(request_t *req, response_t *res){
	char *path = req->url;
	char *argv[10];
	int argn = path2args(path, argv);
	int rgb_led, err, value;

	colors_t color;

	printf("Num of args: %d \r\n", argn);

	/* Check format */
	if (argn != 4) {
		res->code = RES_BAD_REQUEST;
		res->content = "Bad number of arguments. Usage: /pwm/$RGB index [1 -4]$/$color [red, green, blue, rgb]$/$value$\r\n";
		return 0;
	}

	/* Get channel number */
	err = sscanf(argv[1], "%d", &rgb_led);
	if (err < 1 || rgb_led > PWM_NUM_CHANNELS) {
		res->code = RES_BAD_REQUEST;
		res->content = "Bad RGB index. Usage: /pwm/$RGB index [1 to NUM_CHANNELS]$/$color [red, green, blue, rgb]$/$value$\r\n";

#ifdef VERBOSE
		printf("[ PWM CALLBACK ] ERROR. Bad RGB index (arg = '%s', err = %d, index = %d)\r\n", argv[1], err, rgb_led);
#endif

		return 0;
	}

	/* Get channel number */
	if (strcmp(argv[2], "red") == 0) {
		color = RED;
	} else if (strcmp(argv[2], "green") == 0) {
		color = GREEN;
	} else if (strcmp(argv[2], "blue") == 0) {
		color = BLUE;
	} else if (strcmp(argv[2], "rgb") == 0) {
		color = RGB;
	} else {
		res->code = RES_BAD_REQUEST;
		res->content = "Bad color selection. Usage: /pwm/$RGB index [1 to NUM_CHANNELS]$/$color [red, green, blue, rgb]$/$value$\r\n";
		return 0;
	}

	/* Get value */
	if (argv[3][0] == 'x' )
		err = sscanf(argv[3] + 1, "%x", &value);
	else
		err = sscanf(argv[3], "%d", &value);
	if (err < 1 || (color == RGB && value > 16777215) || (color != RGB && value > 255) || value < 0){
		res->code = RES_BAD_REQUEST;
		res->content = "Bad RGB value. Usage: /pwm/$RGB index [1 to NUM_CHANNELS]$/$color [red, green, blue, rgb]$/$value$\r\n";
		return 0;
	}

	switch (color) {
		case RED:
			pwm->channels[rgb_led].red = value;
			printf("[ PWM CALLBACK ] Setting RED as %02X\r\n", value);
			break;
		case GREEN:
			pwm->channels[rgb_led].green = value;
			printf("[ PWM CALLBACK ] Setting GREEN as %02X\r\n", value);
			break;
		case BLUE:
			pwm->channels[rgb_led].blue = value;
			printf("[ PWM CALLBACK ] Setting BLUE as %02X\r\n", value);
			break;
		default:
			pwm->channels[rgb_led].red = value>>16;
			pwm->channels[rgb_led].green = (value>>8) & 255;
			pwm->channels[rgb_led].blue = value & 255;
			printf("[ PWM CALLBACK ] Setting RGB as %06X\r\n", value);
			break;
	}

	strcpy(res->headers[0].name, "Access-Control-Allow-Origin");
	strcpy(res->headers[0].value, "*");

	strcpy(res->headers[1].name, "Content-Type");
	strcpy(res->headers[1].value, "application/json; charset=utf-8");

	res->content = getJSON ();


	return 0;
}

void pwm_set_period (uint32_t period) {
	pwm->period = period;
}

