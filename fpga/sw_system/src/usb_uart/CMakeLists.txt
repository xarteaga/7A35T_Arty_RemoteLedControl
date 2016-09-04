# Check version
cmake_minimum_required (VERSION 3.5.1)

# Create Project
project (usb_uart C )

# Add sources
add_library(usb_uart
			usb_uart.h
			usb_uart.c
		)

# Include Directories
include_directories(usb_uart ../../sdk_workspace/bsp_0/microblaze_0/include)
