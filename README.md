# 7A35T_Arty_RemoteLedControl
## Software Requirements
- Ubuntu (16.04 LTS)
- Xilinx Vivado 2015.2 and SDK 2015.2
- Valid Xilinxlicense
- All other required software (cmake, automake and so on)
- Arty Board

## Generation Instructions
The following script indicates the steps of the complete flow for generating, compile all the FPGA hardware and software.
```
#!/bin/sh
# 1. Change directory to the hardware system creation:
git clone https://github.com/xarteaga/7A35T_Arty_RemoteLedControl.git
cd fpga/hw_system/
# 2. Create hardware system, synthesize, implement and export
make
# 3. Create SDK workspace (BSP, HW and Hello world)
make create_workspace
# 4. Change directory to sowftare
cd ../sw_system
# 5. Create build folder and change directory
mkdir build
cd build
# 6. Generate compilation scripts
cmake ..
# 7. Compile sowftware
make
# 7. Download FPGA
make download
# 8. Run Software
make run
```

## Useful Links
- [How To Store Your SDK Project in SPI Flash](https://reference.digilentinc.com/learn/programmable-logic/tutorials/htsspisf/start)
- [Vivado 2015.2 TCL Commands](http://www.xilinx.com/support/documentation/sw_manuals/xilinx2015_2/ug835-vivado-tcl-commands.pdf)
