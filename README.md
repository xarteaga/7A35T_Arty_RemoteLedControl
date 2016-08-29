# 7A35T_Arty_RemoteLedControl

## Generation Instructions

1. Change directory to the hardware system creation:
```
cd fpga/hw_system/
```
2. Create hardware system, synthesize, implement and export
```
make
```
3. Create SDK workspace
```
make create_workspace
```
4. Change directory to sowftare
```
cd ../sw_system
```
5. Download FPGA
```
xsdk -batch download_bitfile.tcl
```
6. Run ELF
```
xsdk -batch run_elf.tcl
```
