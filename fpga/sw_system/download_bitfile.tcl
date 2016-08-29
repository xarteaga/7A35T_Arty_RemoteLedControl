# 1) Connect to Hardware server
xsdb connect

# 2) Select target
xsdb target 1

# 3) Download FPGA
xsdb fpga ../hw_system/output/hw_system.bit

# 4) Disconnect HW
xsdb disconnect
