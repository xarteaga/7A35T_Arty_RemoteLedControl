# Check version
cmake_minimum_required (VERSION 3.5.1)

# Create Project
project (server C )

# Add sources
add_library(server
		server.h
		server.c
		)

# Include Directories
include_directories(server ../../sdk_workspace/bsp_0/microblaze_0/include)
