/*
 * vaxi_os.c
 *
 *  Created on: 04/08/2016
 *      Author: xavier
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "xil_types.h"

#include "wifi.h"
#include "tinysh.h"
#include "vaxi_os.h"
#include "remote.h"

#define VAXI_OS_MAX_CMD 128

vaxi_os_fsm_state_t vaxi_os_fsm_state = VAXI_OS_FSM_STATE_IDLE;

static tinysh_cmd_t tinysh_cmd_1  = {0, "wifi_lap", "WiFi List Access Point", "<No arguments required>", wifi_request_lap, 0, 0, 0};
static tinysh_cmd_t tinysh_cmd_2  = {0, "wifi_reset", "WiFi Controller Reset", "<No arguments required>", wifi_request_reset, 0, 0, 0};

void vaxi_os_fsm_idle ();
void vaxi_os_fsm_lap ();

void vaxi_os_init() {
	vaxi_os_fsm_state = VAXI_OS_FSM_STATE_IDLE;

	tinysh_add_command(&tinysh_cmd_1);
	tinysh_add_command(&tinysh_cmd_2);

	xil_printf("%s ... OK\r\n", __func__);
}

void vaxi_os_put_char(char c) {
	remote_send((char*)&c, 1);
}

void vaxi_os_task() {

	switch(vaxi_os_fsm_state){
	case VAXI_OS_FSM_STATE_IDLE:
		vaxi_os_fsm_idle();
		break;
	case VAXI_OS_FSM_STATE_WIFI_LAP:
		vaxi_os_fsm_lap();
		break;
	case VAXI_OS_FSM_STATE_WIFI_RESET:
		break;
	default:
		vaxi_os_fsm_state = VAXI_OS_FSM_STATE_IDLE;
	}
}

void vaxi_os_fsm_idle () {
	char c;

	if (wifi_get_fsm_state() == WIFI_FSM_CWLAP) {

		vaxi_os_fsm_state = VAXI_OS_FSM_STATE_WIFI_LAP;
	} else {
		while(remote_recv(&c, 1) != 0) {
			tinysh_char_in(c);
		}
		vaxi_os_fsm_state = VAXI_OS_FSM_STATE_IDLE;
	}
}

void vaxi_os_fsm_lap () {
	u32 n, size;
	char buf [128];
	wifi_ap_t *wifi_ap_list;

	if (wifi_get_fsm_state() == WIFI_FSM_IDLE) {
		wifi_ap_list = wifi_get_ap_list();

		size = sprintf(buf, "           --- WiFi Access Points List --- \r\n");
		remote_send(buf, size);

		size = sprintf(buf, " ----------- SSID ------------- |--- RSSI ---\r\n");
		remote_send(buf, size);

		for(n = 0; (wifi_ap_list[n].ecn != WIFI_AP_ECN_EMPTY) && n < WIFI_AP_MAX_LIST; n ++) {
			size = sprintf(buf, "%32s    %d dBm\r\n", wifi_ap_list[n].ssid, wifi_ap_list[n].rssi);
			remote_send(buf, size);
		}
		tinysh_char_in('\r');
		tinysh_char_in('\n');

		vaxi_os_fsm_state = VAXI_OS_FSM_STATE_IDLE;
	} else {
		vaxi_os_fsm_state = WIFI_FSM_CWLAP;
	}
}

void vaxi_os_fsm_reset () {
	u32 size;
	char buf [128];

	if (wifi_get_fsm_state() == WIFI_FSM_IDLE) {
		size = sprintf(buf, "Reset OK!\r\n");
		remote_send(buf, size);
		tinysh_char_in('\n');

		vaxi_os_fsm_state = VAXI_OS_FSM_STATE_IDLE;
	} else {
		vaxi_os_fsm_state = VAXI_OS_FSM_STATE_WIFI_RESET;
	}
}
