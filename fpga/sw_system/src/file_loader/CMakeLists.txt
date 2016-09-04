# Check version
cmake_minimum_required (VERSION 3.5.1)

# Create Project
project (file_loader C )

# Add sources
add_library(file_loader
			file_loader.h
			file_loader.c
		)

# Include Directories
include_directories(file_loader ../../sdk_workspace/bsp_0/microblaze_0/include)
