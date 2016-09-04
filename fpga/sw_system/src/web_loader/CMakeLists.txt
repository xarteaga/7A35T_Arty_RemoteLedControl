# Check version
cmake_minimum_required (VERSION 3.5.1)

# Create Project
project (web_loader C )

# Add sources
add_library(web_loader
			web_loader.h
			web_loader.c
			web_loader_data.h
		)

# Include Directories
include_directories(web_loader ../../sdk_workspace/bsp_0/microblaze_0/include)
