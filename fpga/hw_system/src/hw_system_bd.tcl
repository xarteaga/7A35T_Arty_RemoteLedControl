
################################################################
# This is a generated script based on design: design_1
#
# Though there are limitations about the generated script,
# the main purpose of this utility is to make learning
# IP Integrator Tcl commands easier.
################################################################

################################################################
# Check if script is running in correct Vivado version.
################################################################
set scripts_vivado_version 2015.2
set current_vivado_version [version -short]

if { [string first $scripts_vivado_version $current_vivado_version] == -1 } {
	 puts ""
	 puts "ERROR: This script was generated using Vivado <$scripts_vivado_version> and is being run in <$current_vivado_version> of Vivado. Please run the script in Vivado <$scripts_vivado_version> then open the design in Vivado <$current_vivado_version>. Upgrade the design by running \"Tools => Report => Report IP Status...\", then run write_bd_tcl to create an updated script."

	 return 1
}

################################################################
# START
################################################################

# To test this script, run the following commands from Vivado Tcl console:
# source design_1_script.tcl

# If you do not already have a project created,
# you can create a project using the following command:
#		create_project project_1 myproj -part xc7a35ticsg324-1L
#		set_property BOARD_PART digilentinc.com:arty:part0:1.1 [current_project]

# CHECKING IF PROJECT EXISTS
if { [get_projects -quiet] eq "" } {
	 puts "ERROR: Please open or create a project!"
	 return 1
}

	

# CHANGE DESIGN NAME HERE
set design_name system

# If you do not already have an existing IP Integrator design open,
# you can create a design using the following command:
#		create_bd_design $design_name

# Creating design if needed
set errMsg ""
set nRet 0

set cur_design [current_bd_design -quiet]
set list_cells [get_bd_cells -quiet]

if { ${design_name} eq "" } {
	 # USE CASES:
	 #		1) Design_name not set

	 set errMsg "ERROR: Please set the variable <design_name> to a non-empty value."
	 set nRet 1

} elseif { ${cur_design} ne "" && ${list_cells} eq "" } {
	 # USE CASES:
	 #		2): Current design opened AND is empty AND names same.
	 #		3): Current design opened AND is empty AND names diff; design_name NOT in project.
	 #		4): Current design opened AND is empty AND names diff; design_name exists in project.

	 if { $cur_design ne $design_name } {
			puts "INFO: Changing value of <design_name> from <$design_name> to <$cur_design> since current design is empty."
			set design_name [get_property NAME $cur_design]
	 }
	 puts "INFO: Constructing design in IPI design <$cur_design>..."

} elseif { ${cur_design} ne "" && $list_cells ne "" && $cur_design eq $design_name } {
	 # USE CASES:
	 #		5) Current design opened AND has components AND same names.

	 set errMsg "ERROR: Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
	 set nRet 1
} elseif { [get_files -quiet ${design_name}.bd] ne "" } {
	 # USE CASES: 
	 #		6) Current opened design, has components, but diff names, design_name exists in project.
	 #		7) No opened design, design_name exists in project.

	 set errMsg "ERROR: Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
	 set nRet 2

} else {
	 # USE CASES:
	 #		8) No opened design, design_name not in project.
	 #		9) Current opened design, has components, but diff names, design_name not in project.

	 puts "INFO: Currently there is no design <$design_name> in project, so creating one..."

	 create_bd_design $design_name

	 puts "INFO: Making design <$design_name> as current_bd_design."
	 current_bd_design $design_name

}

puts "INFO: Currently the variable <design_name> is equal to \"$design_name\"."

if { $nRet != 0 } {
	 puts $errMsg
	 return $nRet
}

##################################################################
# DESIGN PROCs
##################################################################


# Hierarchical cell: microblaze_0_local_memory
proc create_hier_cell_microblaze_0_local_memory { parentCell nameHier } {

	if { $parentCell eq "" || $nameHier eq "" } {
		 puts "ERROR: create_hier_cell_microblaze_0_local_memory() - Empty argument(s)!"
		 return
	}

	# Get object for parentCell
	set parentObj [get_bd_cells $parentCell]
	if { $parentObj == "" } {
		 puts "ERROR: Unable to find parent cell <$parentCell>!"
		 return
	}

	# Make sure parentObj is hier blk
	set parentType [get_property TYPE $parentObj]
	if { $parentType ne "hier" } {
		 puts "ERROR: Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."
		 return
	}

	# Save current instance; Restore later
	set oldCurInst [current_bd_instance .]

	# Set parent object as current
	current_bd_instance $parentObj

	# Create cell and set as current instance
	set hier_obj [create_bd_cell -type hier $nameHier]
	current_bd_instance $hier_obj

	# Create interface pins
	create_bd_intf_pin -mode MirroredMaster -vlnv xilinx.com:interface:lmb_rtl:1.0 DLMB
	create_bd_intf_pin -mode MirroredMaster -vlnv xilinx.com:interface:lmb_rtl:1.0 ILMB

	# Create pins
	create_bd_pin -dir I -type clk LMB_Clk
	create_bd_pin -dir I -from 0 -to 0 -type rst LMB_Rst

	# Create instance: dlmb_bram_if_cntlr, and set properties
	set dlmb_bram_if_cntlr [ create_bd_cell -type ip -vlnv xilinx.com:ip:lmb_bram_if_cntlr:4.0 dlmb_bram_if_cntlr ]
	set_property -dict [ list CONFIG.C_ECC {0}	] $dlmb_bram_if_cntlr

	# Create instance: dlmb_v10, and set properties
	set dlmb_v10 [ create_bd_cell -type ip -vlnv xilinx.com:ip:lmb_v10:3.0 dlmb_v10 ]

	# Create instance: ilmb_bram_if_cntlr, and set properties
	set ilmb_bram_if_cntlr [ create_bd_cell -type ip -vlnv xilinx.com:ip:lmb_bram_if_cntlr:4.0 ilmb_bram_if_cntlr ]
	set_property -dict [ list CONFIG.C_ECC {0}	] $ilmb_bram_if_cntlr

	# Create instance: ilmb_v10, and set properties
	set ilmb_v10 [ create_bd_cell -type ip -vlnv xilinx.com:ip:lmb_v10:3.0 ilmb_v10 ]

	# Create instance: lmb_bram, and set properties
	set lmb_bram [ create_bd_cell -type ip -vlnv xilinx.com:ip:blk_mem_gen:8.2 lmb_bram ]
	set_property -dict [ list CONFIG.Memory_Type {True_Dual_Port_RAM} CONFIG.use_bram_block {BRAM_Controller}	] $lmb_bram

	# Create interface connections
	connect_bd_intf_net -intf_net microblaze_0_dlmb [get_bd_intf_pins DLMB] [get_bd_intf_pins dlmb_v10/LMB_M]
	connect_bd_intf_net -intf_net microblaze_0_dlmb_bus [get_bd_intf_pins dlmb_bram_if_cntlr/SLMB] [get_bd_intf_pins dlmb_v10/LMB_Sl_0]
	connect_bd_intf_net -intf_net microblaze_0_dlmb_cntlr [get_bd_intf_pins dlmb_bram_if_cntlr/BRAM_PORT] [get_bd_intf_pins lmb_bram/BRAM_PORTA]
	connect_bd_intf_net -intf_net microblaze_0_ilmb [get_bd_intf_pins ILMB] [get_bd_intf_pins ilmb_v10/LMB_M]
	connect_bd_intf_net -intf_net microblaze_0_ilmb_bus [get_bd_intf_pins ilmb_bram_if_cntlr/SLMB] [get_bd_intf_pins ilmb_v10/LMB_Sl_0]
	connect_bd_intf_net -intf_net microblaze_0_ilmb_cntlr [get_bd_intf_pins ilmb_bram_if_cntlr/BRAM_PORT] [get_bd_intf_pins lmb_bram/BRAM_PORTB]

	# Create port connections
	connect_bd_net -net microblaze_0_Clk [get_bd_pins LMB_Clk] [get_bd_pins dlmb_bram_if_cntlr/LMB_Clk] [get_bd_pins dlmb_v10/LMB_Clk] [get_bd_pins ilmb_bram_if_cntlr/LMB_Clk] [get_bd_pins ilmb_v10/LMB_Clk]
	connect_bd_net -net microblaze_0_LMB_Rst [get_bd_pins LMB_Rst] [get_bd_pins dlmb_bram_if_cntlr/LMB_Rst] [get_bd_pins dlmb_v10/SYS_Rst] [get_bd_pins ilmb_bram_if_cntlr/LMB_Rst] [get_bd_pins ilmb_v10/SYS_Rst]
	
	# Restore current instance
	current_bd_instance $oldCurInst
}


# Procedure to create entire design; Provide argument to make
# procedure reusable. If parentCell is "", will use root.
proc create_root_design { parentCell } {

	if { $parentCell eq "" } {
		 set parentCell [get_bd_cells /]
	}

	# Get object for parentCell
	set parentObj [get_bd_cells $parentCell]
	if { $parentObj == "" } {
		 puts "ERROR: Unable to find parent cell <$parentCell>!"
		 return
	}

	# Make sure parentObj is hier blk
	set parentType [get_property TYPE $parentObj]
	if { $parentType ne "hier" } {
		 puts "ERROR: Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."
		 return
	}

	# Save current instance; Restore later
	set oldCurInst [current_bd_instance .]

	# Set parent object as current
	current_bd_instance $parentObj


	# Create interface ports
	set eth_mii [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:mii_rtl:1.0 eth_mii ]
	set eth_mdio_mdc [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:mdio_rtl:1.0 eth_mdio_mdc ]
	set rgb_extern_leds [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:gpio_rtl:1.0 rgb_extern_leds ]
	set rgb_board_leds [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:gpio_rtl:1.0 rgb_board_leds ]
	set uart_lcd [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:uart_rtl:1.0 uart_lcd ]
	set qspi_flash [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:spi_rtl:1.0 qspi_flash ]
	set usb_uart [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:uart_rtl:1.0 usb_uart ]
	set uart_wifi [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:uart_rtl:1.0 uart_wifi ]
	set ddr3_sdram [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:ddrx_rtl:1.0 ddr3_sdram ]

	# Create ports
	set reset [ create_bd_port -dir I -type rst reset ]
	set_property -dict [ list CONFIG.POLARITY {ACTIVE_LOW}	] $reset
	set sys_clock [ create_bd_port -dir I -type clk sys_clock ]
	set_property -dict [ list CONFIG.FREQ_HZ {100000000.0} CONFIG.PHASE {0.000}	] $sys_clock
	set eth_ref_clk [ create_bd_port -dir O -type clk eth_ref_clk ]
	set_property -dict [ list \
		CONFIG.FREQ_HZ {25000000} \
		] $eth_ref_clk

	# Create instance: axi_ethernetlite, and set properties
	set axi_ethernetlite_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_ethernetlite:3.0 axi_ethernetlite_0 ]
	set_property -dict [ list \
		CONFIG.MII_BOARD_INTERFACE {eth mii} \
		CONFIG.MDIO_BOARD_INTERFACE {eth mdio mdc} \
	] $axi_ethernetlite_0

	# Create instance: massive_pwm_0, and set properties
	set massive_pwm_0 [ create_bd_cell -type ip -vlnv xilinx.com:user:massive_pwm:1.0 massive_pwm_0 ]
	set_property -dict [ list CONFIG.NUM_LEDS {4}	] $massive_pwm_0

	# Create instance: massive_pwm_0, and set properties
	set massive_pwm_1 [ create_bd_cell -type ip -vlnv xilinx.com:user:massive_pwm:1.0 massive_pwm_1 ]
	set_property -dict [ list CONFIG.NUM_LEDS {10}	] $massive_pwm_1
	
	# Create instance: axi_quad_spi_0, and set properties
	set axi_quad_spi_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_quad_spi:3.2 axi_quad_spi_0 ]
	set_property -dict [ list \
		CONFIG.C_SCK_RATIO {2} \
		CONFIG.C_SPI_MEMORY {2} \
		CONFIG.C_SPI_MODE {2} \
		CONFIG.C_USE_STARTUP {0} \
		CONFIG.QSPI_BOARD_INTERFACE {qspi_flash} \
		CONFIG.USE_BOARD_FLOW {true}\
	] $axi_quad_spi_0

	# Create instance: uart_wifi, and set properties
	set uart_wifi [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_uartlite:2.0 uart_wifi ]
	set_property -dict [ list \
		CONFIG.C_BAUDRATE {115200} \
		CONFIG.UARTLITE_BOARD_INTERFACE {Custom} \
		CONFIG.USE_BOARD_FLOW {true}\
	] $uart_wifi
	
	# Create instance: uart_lcd, and set properties
	set uart_lcd [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_uartlite:2.0 uart_lcd ]
	set_property -dict [ list \
		CONFIG.C_BAUDRATE {9600} \
		CONFIG.UARTLITE_BOARD_INTERFACE {Custom} \
		CONFIG.USE_BOARD_FLOW {true}\
	] $uart_lcd

	# Create instance: axi_uartlite_0, and set properties
	set axi_uartlite_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_uartlite:2.0 axi_uartlite_0 ]
	set_property -dict [ list \
		CONFIG.C_BAUDRATE {115200} \
		CONFIG.UARTLITE_BOARD_INTERFACE {usb_uart} \
		CONFIG.USE_BOARD_FLOW {true}\
	] $axi_uartlite_0
	
	# Create instance: mig_7series_0, and set properties
	set mig_7series_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:mig_7series:2.3 mig_7series_0 ]
	set folder [pwd]
	set mig_file [glob $folder/src/mig.prj]
	set str_mig_folder [get_property IP_DIR [ get_ips [ get_property CONFIG.Component_Name $mig_7series_0 ] ] ]
	file copy $mig_file "$str_mig_folder/mig.prj"
	set_property -dict [ list \
		CONFIG.XML_INPUT_FILE {${proj_dir}/../mig.prj} \
	] $mig_7series_0

	# Create instance: clk_wiz_0, and set properties
	set clk_wiz_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:clk_wiz:5.1 clk_wiz_0 ]
	set_property -dict [ list \
		CONFIG.CLKOUT2_USED {true} \
		CONFIG.CLKOUT3_USED {true} \
		CONFIG.CLKOUT4_USED {true} \
		CONFIG.NUM_OUT_CLKS {4}\
		CONFIG.CLKOUT1_REQUESTED_OUT_FREQ {166.67}\
		CONFIG.CLKOUT2_REQUESTED_OUT_FREQ {200}\
		CONFIG.CLKOUT3_REQUESTED_OUT_FREQ {25}\
		CONFIG.CLKOUT4_REQUESTED_OUT_FREQ {100.0}\
		CONFIG.RESET_PORT {resetn}\
		CONFIG.MMCM_DIVCLK_DIVIDE {1}\
		CONFIG.MMCM_CLKOUT0_DIVIDE_F {6.000}\
		CONFIG.MMCM_CLKOUT1_DIVIDE {5}\
		CONFIG.MMCM_CLKOUT2_DIVIDE {40}\
		CONFIG.MMCM_CLKOUT3_DIVIDE {10}\
		CONFIG.RESET_TYPE {ACTIVE_LOW}\
		CONFIG.USE_BOARD_FLOW {true}\
		CONFIG.CLK_IN1_BOARD_INTERFACE {sys_clock}\
		CONFIG.CLKOUT1_JITTER {118.758}\
		CONFIG.CLKOUT2_JITTER {114.829}\
		CONFIG.CLKOUT2_PHASE_ERROR {98.575}\
		CONFIG.CLKOUT3_JITTER {175.402}\
		CONFIG.CLKOUT3_PHASE_ERROR {98.575}\
		CONFIG.CLKOUT4_JITTER {130.958}\
	] $clk_wiz_0

	# Create instance: mdm_1, and set properties
	set mdm_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:mdm:3.2 mdm_1 ]

	# Create instance: microblaze_0_axi_intc, and set properties
	set microblaze_0_axi_intc [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_intc:4.1 microblaze_0_axi_intc ]
	set_property -dict [ list \
		CONFIG.C_HAS_FAST {1} \
	] $microblaze_0_axi_intc

	# Create instance: axi_timer_0, and set properties
	set axi_timer_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_timer:2.0 axi_timer_0 ]
	set_property -dict [ list \
		CONFIG.mode_64bit {0} \
		CONFIG.enable_timer2 {1} \
	] $axi_timer_0
	
	# Create instance: axi_mem_intercon, and set properties
	set axi_mem_intercon [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 axi_mem_intercon ]
	set_property -dict [ list \
		CONFIG.NUM_SI {5} \
		CONFIG.NUM_MI {1} \
	] $axi_mem_intercon

	# Create instance: microblaze_0_axi_periph, and set properties
	set microblaze_0_axi_periph [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 microblaze_0_axi_periph ]
	set_property -dict [ list \
		CONFIG.NUM_SI {1} \
		CONFIG.NUM_MI {9} \
	] $microblaze_0_axi_periph
	
	# Create instance: microblaze_0_local_memory
	create_hier_cell_microblaze_0_local_memory [current_bd_instance .] microblaze_0_local_memory

	# Create instance: microblaze_0, and set properties
	set microblaze_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:microblaze:9.5 microblaze_0 ]
	set_property -dict [ list \
		CONFIG.C_D_AXI {1} \
		CONFIG.C_D_LMB {1} \
		CONFIG.C_I_LMB {1} \
		CONFIG.C_DEBUG_ENABLED {1} \
		CONFIG.C_USE_ICACHE {1} \
		CONFIG.C_CACHE_BYTE_SIZE {16384} \
		CONFIG.C_USE_DCACHE {1} \
		CONFIG.C_DCACHE_BYTE_SIZE {16384} \
	] $microblaze_0
	
	# Create instance: microblaze_0, and set properties
	set microblaze_0_xlconcat [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 microblaze_0_xlconcat ]
	set_property -dict [ list \
		CONFIG.NUM_PORTS {6} \
	] $microblaze_0_xlconcat
	
	# Create instance: fit_timer_0, and set properties
	set fit_timer_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:fit_timer:2.0 fit_timer_0 ]
	set_property -dict [ list \
		CONFIG.C_NO_CLOCKS {83333} \
	] $fit_timer_0
	
	# Create instance: proc_sys_reset_0, and set properties
	set proc_sys_reset_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 proc_sys_reset_0 ]
	# set_property -dict [ list CONFIG.RESET_BOARD_INTERFACE {reset} CONFIG.USE_BOARD_FLOW {true}	] $proc_sys_reset_0

	# Create interface connections
	connect_bd_intf_net -intf_net axi_mem_intercon_S00_AXI [get_bd_intf_pins axi_mem_intercon/S00_AXI] [get_bd_intf_pins microblaze_0/M_AXI_DC]
	connect_bd_intf_net -intf_net axi_mem_intercon_S01_AXI [get_bd_intf_pins axi_mem_intercon/S01_AXI] [get_bd_intf_pins microblaze_0/M_AXI_IC]
	connect_bd_intf_net -intf_net axi_mem_intercon_M01_AXI [get_bd_intf_pins axi_mem_intercon/M00_AXI] [get_bd_intf_pins mig_7series_0/S_AXI]
	connect_bd_intf_net -intf_net microblaze_0_axi_periph_M00_AXI [get_bd_intf_pins microblaze_0_axi_periph/M00_AXI] [get_bd_intf_pins microblaze_0_axi_intc/s_axi]
	connect_bd_intf_net -intf_net microblaze_0_axi_periph_M01_AXI [get_bd_intf_pins microblaze_0_axi_periph/M01_AXI] [get_bd_intf_pins axi_uartlite_0/S_AXI]
	connect_bd_intf_net -intf_net microblaze_0_axi_periph_M02_AXI [get_bd_intf_pins microblaze_0_axi_periph/M02_AXI] [get_bd_intf_pins axi_ethernetlite_0/S_AXI]
	connect_bd_intf_net -intf_net microblaze_0_axi_periph_M03_AXI [get_bd_intf_pins microblaze_0_axi_periph/M03_AXI] [get_bd_intf_pins axi_timer_0/S_AXI]
	connect_bd_intf_net -intf_net microblaze_0_axi_periph_M04_AXI [get_bd_intf_pins microblaze_0_axi_periph/M04_AXI] [get_bd_intf_pins massive_pwm_0/S00_AXI]
	connect_bd_intf_net -intf_net microblaze_0_axi_periph_M05_AXI [get_bd_intf_pins microblaze_0_axi_periph/M05_AXI] [get_bd_intf_pins massive_pwm_1/S00_AXI]
	connect_bd_intf_net -intf_net microblaze_0_axi_periph_M06_AXI [get_bd_intf_pins microblaze_0_axi_periph/M06_AXI] [get_bd_intf_pins uart_wifi/S_AXI]
	connect_bd_intf_net -intf_net microblaze_0_axi_periph_M07_AXI [get_bd_intf_pins microblaze_0_axi_periph/M07_AXI] [get_bd_intf_pins uart_lcd/S_AXI]
	connect_bd_intf_net -intf_net microblaze_0_axi_periph_M08_AXI [get_bd_intf_pins microblaze_0_axi_periph/M08_AXI] [get_bd_intf_pins axi_quad_spi_0/AXI_LITE]
	connect_bd_intf_net -intf_net microblaze_0_debug [get_bd_intf_pins microblaze_0/DEBUG] [get_bd_intf_pins mdm_1/MBDEBUG_0]
	connect_bd_intf_net -intf_net microblaze_0_dlmb [get_bd_intf_pins microblaze_0/DLMB] [get_bd_intf_pins microblaze_0_local_memory/DLMB]	
	connect_bd_intf_net -intf_net microblaze_0_ilmb [get_bd_intf_pins microblaze_0/ILMB] [get_bd_intf_pins microblaze_0_local_memory/ILMB]
	connect_bd_intf_net -intf_net microblaze_0_m_axi_dp [get_bd_intf_pins microblaze_0/M_AXI_DP] [get_bd_intf_pins microblaze_0_axi_periph/S00_AXI]
	connect_bd_intf_net -intf_net microblaze_0_interrupt [get_bd_intf_pins microblaze_0/INTERRUPT] [get_bd_intf_pins microblaze_0_axi_intc/interrupt]
	
	# Create port connections
	connect_bd_net -net microblaze_0_xlconcat_0 [get_bd_pins microblaze_0_xlconcat/In0] [get_bd_pins axi_timer_0/interrupt]
	connect_bd_net -net microblaze_0_xlconcat_1 [get_bd_pins microblaze_0_xlconcat/In1] [get_bd_pins axi_ethernetlite_0/ip2intc_irpt]
	connect_bd_net -net microblaze_0_xlconcat_2 [get_bd_pins microblaze_0_xlconcat/In2] [get_bd_pins axi_uartlite_0/interrupt]
	connect_bd_net -net microblaze_0_xlconcat_3 [get_bd_pins microblaze_0_xlconcat/In3] [get_bd_pins uart_wifi/interrupt]
	connect_bd_net -net microblaze_0_xlconcat_4 [get_bd_pins microblaze_0_xlconcat/In4] [get_bd_pins fit_timer_0/interrupt]
	connect_bd_net -net microblaze_0_xlconcat_5 [get_bd_pins microblaze_0_xlconcat/In5] [get_bd_pins axi_quad_spi_0/ip2intc_irpt]
	connect_bd_net -net microblaze_0_xlconcat [get_bd_pins microblaze_0_xlconcat/dout] [get_bd_pins microblaze_0_axi_intc/intr]

	# Distribute Peripherals Clock
	connect_bd_net -net microblaze_0_clk [get_bd_pins mig_7series_0/ui_clk] \
		[get_bd_pins axi_ethernetlite_0/s_axi_aclk] \
		[get_bd_pins massive_pwm_0/s00_axi_aclk] \
		[get_bd_pins massive_pwm_0/clk] \
		[get_bd_pins massive_pwm_1/s00_axi_aclk] \
		[get_bd_pins massive_pwm_1/clk] \
		[get_bd_pins uart_lcd/s_axi_aclk] \
		[get_bd_pins axi_quad_spi_0/s_axi_aclk] \
		[get_bd_pins axi_quad_spi_0/ext_spi_clk] \
		[get_bd_pins axi_uartlite_0/s_axi_aclk] \
		[get_bd_pins uart_wifi/s_axi_aclk] \
		[get_bd_pins axi_mem_intercon/ACLK] \
		[get_bd_pins axi_mem_intercon/S00_ACLK] \
		[get_bd_pins axi_mem_intercon/S01_ACLK] \
		[get_bd_pins axi_mem_intercon/S02_ACLK] \
		[get_bd_pins axi_mem_intercon/S03_ACLK] \
		[get_bd_pins axi_mem_intercon/S04_ACLK] \
		[get_bd_pins axi_mem_intercon/M00_ACLK] \
		[get_bd_pins microblaze_0_local_memory/LMB_Clk] \
		[get_bd_pins microblaze_0/Clk] \
		[get_bd_pins microblaze_0_axi_intc/s_axi_aclk] \
		[get_bd_pins microblaze_0_axi_intc/processor_clk] \
		[get_bd_pins microblaze_0_axi_periph/ACLK] \
		[get_bd_pins microblaze_0_axi_periph/S00_ACLK] \
		[get_bd_pins microblaze_0_axi_periph/M00_ACLK] \
		[get_bd_pins microblaze_0_axi_periph/M01_ACLK] \
		[get_bd_pins microblaze_0_axi_periph/M02_ACLK] \
		[get_bd_pins microblaze_0_axi_periph/M03_ACLK] \
		[get_bd_pins microblaze_0_axi_periph/M04_ACLK] \
		[get_bd_pins microblaze_0_axi_periph/M05_ACLK] \
		[get_bd_pins microblaze_0_axi_periph/M06_ACLK] \
		[get_bd_pins microblaze_0_axi_periph/M07_ACLK] \
		[get_bd_pins microblaze_0_axi_periph/M08_ACLK] \
		[get_bd_pins axi_timer_0/s_axi_aclk] \
		[get_bd_pins proc_sys_reset_0/slowest_sync_clk] \
		[get_bd_pins fit_timer_0/Clk]

	# Distribute Peripherals Reset
	connect_bd_net -net proc_sys_reset_0_peripheral_aresetn [get_bd_pins proc_sys_reset_0/peripheral_aresetn] \
		[get_bd_pins axi_ethernetlite_0/s_axi_aresetn] \
		[get_bd_pins massive_pwm_0/s00_axi_aresetn] \
		[get_bd_pins massive_pwm_1/s00_axi_aresetn] \
		[get_bd_pins uart_lcd/s_axi_aresetn] \
		[get_bd_pins axi_quad_spi_0/s_axi_aresetn] \
		[get_bd_pins axi_uartlite_0/s_axi_aresetn] \
		[get_bd_pins uart_wifi/s_axi_aresetn] \
		[get_bd_pins axi_mem_intercon/S00_ARESETN] \
		[get_bd_pins axi_mem_intercon/S01_ARESETN] \
		[get_bd_pins axi_mem_intercon/S02_ARESETN] \
		[get_bd_pins axi_mem_intercon/S03_ARESETN] \
		[get_bd_pins axi_mem_intercon/S04_ARESETN] \
		[get_bd_pins axi_mem_intercon/M00_ARESETN] \
		[get_bd_pins microblaze_0_axi_intc/s_axi_aresetn] \
		[get_bd_pins microblaze_0_axi_periph/S00_ARESETN] \
		[get_bd_pins microblaze_0_axi_periph/M00_ARESETN] \
		[get_bd_pins microblaze_0_axi_periph/M01_ARESETN] \
		[get_bd_pins microblaze_0_axi_periph/M02_ARESETN] \
		[get_bd_pins microblaze_0_axi_periph/M03_ARESETN] \
		[get_bd_pins microblaze_0_axi_periph/M04_ARESETN] \
		[get_bd_pins microblaze_0_axi_periph/M05_ARESETN] \
		[get_bd_pins microblaze_0_axi_periph/M06_ARESETN] \
		[get_bd_pins microblaze_0_axi_periph/M07_ARESETN] \
		[get_bd_pins microblaze_0_axi_periph/M08_ARESETN] \
		[get_bd_pins microblaze_0_axi_periph/ARESETN] \
		[get_bd_pins axi_timer_0/s_axi_aresetn] \
		[get_bd_pins mig_7series_0/aresetn] 
		
	connect_bd_net -net microblaze_0_reset [get_bd_pins proc_sys_reset_0/mb_reset] \
		[get_bd_pins microblaze_0_axi_intc/processor_rst] \
		[get_bd_pins massive_pwm_0/rst] \
		[get_bd_pins massive_pwm_1/rst] \
		[get_bd_pins fit_timer_0/Rst] \
		[get_bd_pins microblaze_0/Reset]
	connect_bd_net -net proc_sys_reset_0_bus_struct_reset [get_bd_pins proc_sys_reset_0/bus_struct_reset] \
		[get_bd_pins microblaze_0_local_memory/LMB_Rst]	
	connect_bd_net -net proc_sys_reset_0_interconnect_aresetn [get_bd_pins proc_sys_reset_0/interconnect_aresetn] \
		[get_bd_pins axi_mem_intercon/ARESETN]		
	connect_bd_net -net mdm_1_debug_sys_rst [get_bd_pins proc_sys_reset_0/mb_debug_sys_rst] \
		[get_bd_pins mdm_1/Debug_sys_Rst]
	connect_bd_net -net clk_wiz_0_clk_out1 [get_bd_pins clk_wiz_0/clk_out1] \
		[get_bd_pins mig_7series_0/sys_clk_i]
	connect_bd_net -net clk_wiz_0_clk_out2 [get_bd_pins clk_wiz_0/clk_out2] \
		[get_bd_pins mig_7series_0/clk_ref_i]		
	connect_bd_net -net mig_7series_0_ui_clk_sync_rst [get_bd_pins proc_sys_reset_0/ext_reset_in] \
		[get_bd_pins mig_7series_0/ui_clk_sync_rst]	
	connect_bd_net -net mig_7series_0_mmcm_locked [get_bd_pins proc_sys_reset_0/dcm_locked] \
		[get_bd_pins mig_7series_0/mmcm_locked]			
		
		
	# Create port connections
	connect_bd_net -net reset_1 [get_bd_ports reset] \
		[get_bd_pins clk_wiz_0/resetn] \
		[get_bd_pins mig_7series_0/sys_rst]
	connect_bd_net -net sys_clock_1 [get_bd_ports sys_clock] \
		[get_bd_pins clk_wiz_0/clk_in1]
	connect_bd_net -net eth_ref_clk_1 [get_bd_ports eth_ref_clk] \
		[get_bd_pins clk_wiz_0/clk_out3]

	# Create port interface connections
	connect_bd_intf_net -intf_net eth_mii_1 [get_bd_intf_ports eth_mii] [get_bd_intf_pins axi_ethernetlite_0/MII]
	connect_bd_intf_net -intf_net eth_mdio_mdc_1 [get_bd_intf_ports eth_mdio_mdc] [get_bd_intf_pins axi_ethernetlite_0/MDIO]
	connect_bd_intf_net -intf_net rgb_extern_leds_1 [get_bd_intf_ports rgb_extern_leds] [get_bd_intf_pins massive_pwm_1/PWM_OUT]
	connect_bd_intf_net -intf_net rgb_board_leds_1 [get_bd_intf_ports rgb_board_leds] [get_bd_intf_pins massive_pwm_0/PWM_OUT]
	connect_bd_intf_net -intf_net uart_lcd_1 [get_bd_intf_ports uart_lcd] [get_bd_intf_pins uart_lcd/UART]
	connect_bd_intf_net -intf_net qspi_flash_1 [get_bd_intf_ports qspi_flash] [get_bd_intf_pins axi_quad_spi_0/SPI_0]
	connect_bd_intf_net -intf_net usb_uart_1 [get_bd_intf_ports usb_uart] [get_bd_intf_pins axi_uartlite_0/UART]
	connect_bd_intf_net -intf_net uart_wifi_1 [get_bd_intf_ports uart_wifi] [get_bd_intf_pins uart_wifi/UART]
	connect_bd_intf_net -intf_net ddr3_sdram_1 [get_bd_intf_ports ddr3_sdram] [get_bd_intf_pins mig_7series_0/DDR3]


	# Create Data address segments
	create_bd_addr_seg -range 0x10000 -offset 0x41200000 [get_bd_addr_spaces microblaze_0/Data] \
		[get_bd_addr_segs microblaze_0_axi_intc/s_axi/Reg] SEG_microblaze_0_axi_intc_Reg
	create_bd_addr_seg -range 0x10000 -offset 0x00000000 [get_bd_addr_spaces microblaze_0/Data] \
		[get_bd_addr_segs microblaze_0_local_memory/dlmb_bram_if_cntlr/SLMB/Mem] SEG_dlmb_bram_if_cntlr_Mem
	create_bd_addr_seg -range 0x10000 -offset 0x40460000 [get_bd_addr_spaces microblaze_0/Data] \
		[get_bd_addr_segs axi_uartlite_0/S_AXI/Reg] SEG_axi_uartlite_0_Reg
	create_bd_addr_seg -range 0x10000000 -offset 0x80000000 [get_bd_addr_spaces microblaze_0/Data] \
		[get_bd_addr_segs mig_7series_0/memmap/memaddr] SEG_mig_7series_0_memaddr
	create_bd_addr_seg -range 0x10000 -offset 0x41C00000 [get_bd_addr_spaces microblaze_0/Data] \
		[get_bd_addr_segs axi_timer_0/S_AXI/Reg] SEG_axi_timer_0_Reg
	create_bd_addr_seg -range 0x10000 -offset 0x40E00000 [get_bd_addr_spaces microblaze_0/Data] \
		[get_bd_addr_segs axi_ethernetlite_0/S_AXI/Reg] SEG_axi_ethernetlite_0_Reg
	create_bd_addr_seg -range 0x10000 -offset 0x44A10000 [get_bd_addr_spaces microblaze_0/Data] \
		[get_bd_addr_segs massive_pwm_1/S00_AXI/S00_AXI_reg] SEG_massive_pwm_1_S00_AXI_reg
	create_bd_addr_seg -range 0x10000 -offset 0x44A00000 [get_bd_addr_spaces microblaze_0/Data] \
		[get_bd_addr_segs massive_pwm_0/S00_AXI/S00_AXI_reg] SEG_massive_pwm_0_S00_AXI_reg
	create_bd_addr_seg -range 0x10000 -offset 0x40610000 [get_bd_addr_spaces microblaze_0/Data] \
		[get_bd_addr_segs /uart_wifi/S_AXI/Reg] SEG_axi_uartwifi_Reg
	create_bd_addr_seg -range 0x10000 -offset 0x40620000 [get_bd_addr_spaces microblaze_0/Data] \
		[get_bd_addr_segs /uart_lcd/S_AXI/Reg] SEG_uart_lcd_Reg
	create_bd_addr_seg -range 0x10000 -offset 0x44A20000 [get_bd_addr_spaces microblaze_0/Data] \
		[get_bd_addr_segs /axi_quad_spi_0/AXI_LITE/Reg] SEG_axi_quad_spi_0_Reg	

	# Create Instruction address segments
	create_bd_addr_seg -range 0x8000 -offset 0x00000000 [get_bd_addr_spaces microblaze_0/Instruction] \
		[get_bd_addr_segs microblaze_0_local_memory/ilmb_bram_if_cntlr/SLMB/Mem] SEG_ilmb_bram_if_cntlr_Mem
	create_bd_addr_seg -range 0x10000000 -offset 0x80000000 [get_bd_addr_spaces microblaze_0/Instruction] \
		[get_bd_addr_segs mig_7series_0/memmap/memaddr] SEG_mig_7series_0_memaddr
		
	# Restore current instance
	current_bd_instance $oldCurInst

	save_bd_design
}
# End of create_root_design()


##################################################################
# MAIN FLOW
##################################################################

create_root_design ""


