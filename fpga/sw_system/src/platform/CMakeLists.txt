# Check version
cmake_minimum_required (VERSION 3.5.1)

# Create Project
project (sw_platform C )

# Add sources
add_library(sw_platform
			platform.c
			platform_mb.c
		)

# Include Directories
include_directories(sw_platform ../../sdk_workspace/bsp_0/microblaze_0/include)
include_directories(sw_platform ../scheduler)
include_directories(sw_platform ../usb_uart)
