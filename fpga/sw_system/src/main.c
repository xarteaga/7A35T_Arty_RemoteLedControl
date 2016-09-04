/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

#include <stdio.h>

#include "xparameters.h"

#include "netif/xadapter.h"

#include "platform/platform.h"
#include "platform/platform_config.h"

#include "lwip/tcp.h"
#include "lwip/tcp_impl.h"
#include "lwip/init.h"

#include "server.h"
#include "pwm.h"
#include "lcd.h"
#include "wifi_uart.h"
#include "wifi.h"
#include "vaxi_os.h"

extern massive_pwm_t *pwm;

resource_t resources[] = {
		{ "/pwm/", pwm_callback },
		{ "/lcd", lcd_callback },
		{ 0, 0}
};


#if LWIP_DHCP==1
#include "lwip/dhcp.h"
#endif

/* defined by each RAW mode application */
void print_app_header();
int transfer_data();

/* missing declaration in lwIP */
void lwip_init();

#if LWIP_DHCP==1
extern volatile int dhcp_timoutcntr;
err_t dhcp_start(struct netif *netif);
#endif

extern volatile int TcpFastTmrFlag;
extern volatile int TcpSlowTmrFlag;
static struct netif server_netif;
struct netif *echo_netif;

int transfer_data() {
	return 0;
}

void
print_ip(char *msg, struct ip_addr *ip) {
	print(msg);
	xil_printf("%d.%d.%d.%d\n\r", ip4_addr1(ip), ip4_addr2(ip),
			ip4_addr3(ip), ip4_addr4(ip));
}

void print_ip_settings(struct ip_addr *ip, struct ip_addr *mask, struct ip_addr *gw) {

	print_ip("Board IP: ", ip);
	print_ip("Netmask : ", mask);
	print_ip("Gateway : ", gw);
}

int main()
{
	struct ip_addr ipaddr, netmask, gw;

	/* the mac address of the board. this should be unique per board */
	unsigned char mac_ethernet_address[] =
	{ 0x00, 0x0a, 0x35, 0x00, 0x01, 0x02 };

	echo_netif = &server_netif;

	/* Init Platform */
	init_platform();

#if LWIP_DHCP==1
    ipaddr.addr = 0;
	gw.addr = 0;
	netmask.addr = 0;
#else
	/* initliaze IP addresses to be used */
	IP4_ADDR(&ipaddr,  192, 168,   1, 10);
	IP4_ADDR(&netmask, 255, 255, 255,  0);
	IP4_ADDR(&gw,      192, 168,   1,  1);
#endif
	print_app_header();

	xil_printf("Init LWIP core...\r\n");
	lwip_init();


  	/* Add network interface to the netif_list, and set it as default */
	xil_printf("Adding network interface...\r\n");
	if (!xemac_add(echo_netif, &ipaddr, &netmask,
						&gw, mac_ethernet_address,
						PLATFORM_EMAC_BASEADDR)) {
		xil_printf("Error adding N/W interface\n\r");
		return -1;
	}
	xil_printf("Setting default itf...\r\n");
	netif_set_default(echo_netif);

	/* now enable interrupts */
	xil_printf("Enabling interrupts...\r\n");
	platform_enable_interrupts();

	/* specify that the network if is up */
	netif_set_up(echo_netif);

#if (LWIP_DHCP==1)
	/* Create a new DHCP client for this interface.
	 * Note: you must call dhcp_fine_tmr() and dhcp_coarse_tmr() at
	 * the predefined regular intervals after starting the client.
	 */
	dhcp_start(echo_netif);
	dhcp_timoutcntr = 24;

	while(((echo_netif->ip_addr.addr) == 0) && (dhcp_timoutcntr > 0))
		xemacif_input(echo_netif);

	if (dhcp_timoutcntr <= 0) {
		if ((echo_netif->ip_addr.addr) == 0) {
			xil_printf("DHCP Timeout\r\n");
			xil_printf("Configuring default IP of 192.168.1.10\r\n");
			IP4_ADDR(&(echo_netif->ip_addr),  192, 168,   1, 10);
			IP4_ADDR(&(echo_netif->netmask), 255, 255, 255,  0);
			IP4_ADDR(&(echo_netif->gw),      192, 168,   1,  1);
		}
	}

	ipaddr.addr = echo_netif->ip_addr.addr;
	gw.addr = echo_netif->gw.addr;
	netmask.addr = echo_netif->netmask.addr;
#endif

	print_ip_settings(&ipaddr, &netmask, &gw);


	pwm->period = ((83333334)>>8)/100;
	pwm->channels[0].blue = 0;
	pwm->channels[0].green = 0;
	pwm->channels[0].red = 32;
	pwm->channels[0].offset = 0;
	pwm->channels[1].blue = 0;
	pwm->channels[1].green = 0;
	pwm->channels[1].red = 0;
	pwm->channels[1].offset = 64;
	pwm->channels[2].blue = 0;
	pwm->channels[2].green = 0;
	pwm->channels[2].red = 0;
	pwm->channels[2].offset = 128;
	pwm->channels[3].blue = 0;
	pwm->channels[3].green = 0;
	pwm->channels[3].red = 0;
	pwm->channels[3].offset = 192;

	/* start the application (web server, rxtest, txtest, etc..) */
	wifi_uart_init();
	http_server_start(80);
	remote_init ();
	lcd_init();
	wifi_init();
	vaxi_os_init();

	lcd_write("    [VaXiOS]", 1, 12);
	lcd_write("    Welcome!", 2, 12);

	/* receive and process packets */
	while (1) {
		if (TcpFastTmrFlag) {
			tcp_fasttmr();
			TcpFastTmrFlag = 0;
		}
		if (TcpSlowTmrFlag) {
			tcp_slowtmr();
			TcpSlowTmrFlag = 0;
		}
		xemacif_input(echo_netif);
		transfer_data();

		remote_task();

		wifi_uart_task();
		wifi_task();
		vaxi_os_task();

		/*if (lcd_is_writing() == FALSE){
			char rst_buf[2] = {124, 'r'};
			lcd_write(rst_buf, 2);
			xil_printf("Reseting LCD\r\n");
		}*/
	}

	/* never reached */
	cleanup_platform();

	return 0;
}
