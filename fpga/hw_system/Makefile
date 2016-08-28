# Vivado TCL scripts
CREATE_HW_SYSTEM = create_hw_system.tcl
IMPLEMENT_HW_SYSTEM = implement_hw_system.tcl

# HW_PROJECT
HW_PROJECT = hw_system/hw_system.xpr
HW_BITSTREAM = ouput/hw_system.bit

# Vivado call
VIVADO = vivado -mode batch

# Paths
LOG_PATH = output/logs

all: $(HW_PROJECT) $(HW_BITSTREAM)
	
$(HW_BITSTREAM): $(HW_PROJECT) $(IMPLEMENT_HW_SYSTEM)
	@$(VIVADO) -source $(IMPLEMENT_HW_SYSTEM) -log $(LOG_PATH)/$(basename $(IMPLEMENT_HW_SYSTEM)).log
	@echo "System implemented succeesfully!"

$(HW_PROJECT): $(CREATE_HW_SYSTEM) src/hw_system_bd.tcl src/mig.prj src/system.xdc
	@echo "Cleaning vivado project..."
	@rm -f *.jou *.log
	@rm -f -r hw_system
	@echo "Creating Vivado Project and block diagram"
	@$(VIVADO) -source $(CREATE_HW_SYSTEM) -log $(LOG_PATH)/$(basename $(CREATE_HW_SYSTEM)).log

$(LOG_PATH): Makefile
	@mkdir -p $(LOG_PATH)

create_folders: $(LOG_PATH)
	@echo "HW Project folders created"

create_system: $(HW_PROJECT)
	@echo "System Creation Done! It is ready to be Synthesized and Implemented!"

implement_system: create_folders create_system $(HW_BITSREAM)

clean:
	@rm -f -r hw_system $(LOG_PATH)
	@rm -f *.jou *.log
	@echo "Project Cleaned"
