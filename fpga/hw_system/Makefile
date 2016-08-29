# Vivado TCL scripts
CREATE_HW_SYSTEM = create_hw_system.tcl
IMPLEMENT_HW_SYSTEM = implement_hw_system.tcl
EXPORT_HW_SYSTEM = export_hw_system.tcl
CREATE_WORKSPACE = create_workspace.tcl

# HW_PROJECT
HW_PROJECT = hw_system/hw_system.xpr
HW_BITSTREAM = output/hw_system.bit
HW_DEF_SDK = output/hw_system.hdf

# Xilinx Binaries
VIVADO = vivado -mode batch
XSDK = xsdk -mode batch

# Paths
LOG_PATH = output/logs

all: $(HW_DEF_SDK)
	

$(HW_BITSTREAM): $(HW_PROJECT) $(IMPLEMENT_HW_SYSTEM)
	@rm -f *.jou *.log *.str
	@$(VIVADO) -source $(IMPLEMENT_HW_SYSTEM) -log $(LOG_PATH)/$(basename $(IMPLEMENT_HW_SYSTEM)).log

$(HW_DEF_SDK): $(HW_BITSTREAM) $(EXPORT_HW_SYSTEM)
	@rm -f *.jou *.log *.str
	@$(VIVADO) -source $(EXPORT_HW_SYSTEM) -log $(LOG_PATH)/$(basename $(EXPORT_HW_SYSTEM)).log

$(HW_PROJECT): $(CREATE_HW_SYSTEM) src/hw_system_bd.tcl src/mig.prj src/system.xdc
	@rm -f *.jou *.log *.str
	@rm -f -r hw_system
	@$(VIVADO) -source $(CREATE_HW_SYSTEM) -log $(LOG_PATH)/$(basename $(CREATE_HW_SYSTEM)).log

create_workspace: $(HW_DEF_SDK) $(CREATE_WORKSPACE)
	@rm -f *.jou *.log *.str
	@$(XSDK) -source $(CREATE_WORKSPACE) -log $(LOG_PATH)/$(basename $(CREATE_WORKSPACE)).log

create_folders: $(LOG_PATH)

create_system: $(HW_PROJECT)

implement_system: create_folders create_system $(HW_BITSREAM)

export_system: $(HW_DEF_SDK)


# Clean all the project
clean:
	@rm -f -r hw_system $(LOG_PATH)
	@rm -f *.jou *.log
	@echo "Project Cleaned"
