# 1) Connect to Hardware server
xsdb connect

# 2) Select target
xsdb target 3

# 3) Stop processor
xsdb stop

# 4) Download FPGA
xsdb dow helloworld.elf

# 5) Run processor
xsdb con

# 6) Disconnect HW
xsdb disconnect
