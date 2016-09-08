# Check version
cmake_minimum_required (VERSION 3.5.1)

# Create Project
project (rgb_leds C )

# Add sources
add_library(rgb_leds
		rgb_leds.c
		rgb_leds_resource.c
		rgb_leds_cmd.c
		rgb_leds.h
		rgb_leds_resource.h
		rgb_leds_cmd.h
		)

# Include Directories
include_directories(rgb_leds ../../sdk_workspace/bsp_0/microblaze_0/include)
include_directories(rgb_leds ../utils)
include_directories(rgb_leds ../scheduler)
include_directories(rgb_leds ../)

