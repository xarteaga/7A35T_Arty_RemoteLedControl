/*
 * usb_uart.c
 *
 *  Created on: 03/08/2016
 *      Author: xavier
 */

#include <string.h>

#include "xparameters.h"
#include "xuartlite.h"
#include "../remote.h"
#include "scheduler.h"

#define USB_UART_BUFF_SIZE_POW (11)
#define USB_UART_BUFF_SIZE (1<<USB_UART_BUFF_SIZE_POW)
#define USB_UART_BUFF_MOD(X) (((u32) X ) & (USB_UART_BUFF_SIZE - 1))

u8 usb_uart_rx_buff[USB_UART_BUFF_SIZE];
u8 usb_uart_tx_buff[USB_UART_BUFF_SIZE];
u32 usb_uart_buff_write_ptr = 0, usb_uart_buff_read_ptr = 0;

XUartLite usb_uart;

/* Function prototypes */
void usb_uart_task();

static scheduler_entry_t usb_uart_scheduler_entry = {0, 1, usb_uart_task};

void usb_uart_rx_handler(void *CallBackRef, unsigned int EventData) {
    XUartLite_Recv(&usb_uart, usb_uart_rx_buff, USB_UART_BUFF_SIZE);
    return;
}

void usb_uart_tx_handler(void *CallBackRef, unsigned int EventData){
    return;
}

void usb_uart_init () {
    XUartLite_Initialize(&usb_uart, XPAR_AXI_UARTLITE_0_DEVICE_ID);
    XUartLite_SetRecvHandler(&usb_uart, usb_uart_rx_handler ,&usb_uart);
    XUartLite_SetSendHandler(&usb_uart, usb_uart_tx_handler ,&usb_uart);
    XUartLite_EnableInterrupt(&usb_uart);

    XUartLite_Recv(&usb_uart, usb_uart_rx_buff, USB_UART_BUFF_SIZE);

    usb_uart_buff_write_ptr = 0;
    usb_uart_buff_read_ptr = 0;
    remote_print("%s ... OK\r\n", __func__);

    /* Add entry */
    scheduler_add_entry(&usb_uart_scheduler_entry);
}

u32 usb_uart_available() {
    u32 diff;
    usb_uart_buff_write_ptr = usb_uart.ReceiveBuffer.NextBytePtr - usb_uart_rx_buff;
    if (usb_uart_buff_write_ptr >= usb_uart_buff_read_ptr)
        diff = usb_uart_buff_write_ptr - usb_uart_buff_read_ptr;
    else
        diff = (usb_uart_buff_write_ptr + USB_UART_BUFF_SIZE) - usb_uart_buff_read_ptr;

    return diff;
}

void usb_uart_write(u8 *buf, u32 size) {
    memcpy(usb_uart_tx_buff, buf, size);
    usb_uart_tx_buff[size] = '\0';
    XUartLite_Send(&usb_uart, buf, size);
    //xil_printf(usb_uart_tx_buff);
}

u32 usb_uart_read(u8 *buf, u32 maxsize) {
    u32 n = usb_uart_available();
    u32 count = 0;

    if (maxsize < n)
        n = maxsize;

    for (count = 0; count < n; count ++){
        buf[count] = usb_uart_rx_buff[usb_uart_buff_read_ptr];
        usb_uart_buff_read_ptr = USB_UART_BUFF_MOD(usb_uart_buff_read_ptr + 1);
    }

    return n;
}

void usb_uart_task() {
    XUartLite_ReceiveBuffer(&usb_uart);
    XUartLite_SendBuffer(&usb_uart);
}
