#!/usr/bin/tclsh
# 0) Delete previous existance of workspace
file delete -force ../sw_system/sdk_workspace

# 1) Set Workspace
sdk set_workspace ../sw_system/sdk_workspace

# 2) Create HW project
sdk create_hw_project -name hw_0 -hwspec output/hw_system.hdf

# Create BSP
sdk create_bsp_project -name bsp_0 -hwproject hw_0 -mss src/system.mss

# Create Hello World Project
sdk create_app_project -name helloworld -hwproject hw_0 -proc microblaze_0 -os standalone -lang C -app {Hello World} -bsp bsp_0

sdk build_project bsp_0
sdk build_project helloworld
exit
