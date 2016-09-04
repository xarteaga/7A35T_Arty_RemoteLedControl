# Check version
cmake_minimum_required (VERSION 3.5.1)

# Create Project
project (board_rgb_leds C )

# Add sources
add_library(board_rgb_leds
			board_rgb_leds.h
			board_rgb_leds.c
		)

# Include Directories
include_directories(board_rgb_leds ../../sdk_workspace/bsp_0/microblaze_0/include)
