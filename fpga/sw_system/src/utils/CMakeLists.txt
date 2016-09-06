# Check version
cmake_minimum_required (VERSION 3.5.1)

# Create Project
project (utils C )

# Add sources
add_library(utils
			wifi_utils.c
			wifi_utils.h
			colors.c
			colors.h
		)

# Include Directories
include_directories(web_loader ../../sdk_workspace/bsp_0/microblaze_0/include)
