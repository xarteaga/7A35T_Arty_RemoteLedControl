#ifndef SW_SYSTEM_USB_UART_H
#define SW_SYSTEM_USB_UART_H

#include "xil_types.h"

/* Function prototypes */
void usb_uart_init ();
u32 usb_uart_read(u8 *buf, u32 maxsize);
void usb_uart_write(u8 *buf, u32 size);

#endif //SW_SYSTEM_USB_UART_H
