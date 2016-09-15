#Clock constraints
create_clock -period 10.000 -name sys_clock [get_ports sys_clock]

#System clock
set_property -dict { PACKAGE_PIN E3 IOSTANDARD LVCMOS33 } [get_ports { sys_clock }]; 

#QSPI constraints
set_property -dict { PACKAGE_PIN L16 IOSTANDARD LVCMOS33 } [get_ports { qspi_flash_sck }]; 

# PWM LEDs 4bit
#set_property PACKAGE_PIN H5 [get_ports {PWM_LEDs_4bits[0]}]
#set_property PACKAGE_PIN J5 [get_ports {PWM_LEDs_4bits[1]}]
#set_property PACKAGE_PIN T9 [get_ports {PWM_LEDs_4bits[2]}]
#set_property PACKAGE_PIN T10 [get_ports {PWM_LEDs_4bits[3]}]

#set_property IOSTANDARD LVCMOS33 [get_ports {PWM_LEDs_4bits[0]}]
#set_property IOSTANDARD LVCMOS33 [get_ports {PWM_LEDs_4bits[1]}]
#set_property IOSTANDARD LVCMOS33 [get_ports {PWM_LEDs_4bits[2]}]
#set_property IOSTANDARD LVCMOS33 [get_ports {PWM_LEDs_4bits[3]}]

# RGB LEDs
set_property -dict { PACKAGE_PIN G6 IOSTANDARD LVCMOS33 } [get_ports { rgb_board_leds_tri_o[0] }]; 
set_property -dict { PACKAGE_PIN F6 IOSTANDARD LVCMOS33 } [get_ports { rgb_board_leds_tri_o[1] }];
set_property -dict { PACKAGE_PIN E1 IOSTANDARD LVCMOS33 } [get_ports { rgb_board_leds_tri_o[2] }];
set_property -dict { PACKAGE_PIN G3 IOSTANDARD LVCMOS33 } [get_ports { rgb_board_leds_tri_o[3] }];
set_property -dict { PACKAGE_PIN J4 IOSTANDARD LVCMOS33 } [get_ports { rgb_board_leds_tri_o[4] }];
set_property -dict { PACKAGE_PIN G4 IOSTANDARD LVCMOS33 } [get_ports { rgb_board_leds_tri_o[5] }];
set_property -dict { PACKAGE_PIN J3 IOSTANDARD LVCMOS33 } [get_ports { rgb_board_leds_tri_o[6] }];
set_property -dict { PACKAGE_PIN J2 IOSTANDARD LVCMOS33 } [get_ports { rgb_board_leds_tri_o[7] }];
set_property -dict { PACKAGE_PIN H4 IOSTANDARD LVCMOS33 } [get_ports { rgb_board_leds_tri_o[8] }];
set_property -dict { PACKAGE_PIN K1 IOSTANDARD LVCMOS33 } [get_ports { rgb_board_leds_tri_o[9] }];
set_property -dict { PACKAGE_PIN H6 IOSTANDARD LVCMOS33 } [get_ports { rgb_board_leds_tri_o[10] }];
set_property -dict { PACKAGE_PIN K2 IOSTANDARD LVCMOS33 } [get_ports { rgb_board_leds_tri_o[11] }];

# PMOD JA
set_property -dict { PACKAGE_PIN G13 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[0] }];
set_property -dict { PACKAGE_PIN B11 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[1] }];
set_property -dict { PACKAGE_PIN A11 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[2] }];
set_property -dict { PACKAGE_PIN D12 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[3] }];
set_property -dict { PACKAGE_PIN D13 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[4] }];
set_property -dict { PACKAGE_PIN B18 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[5] }];
set_property -dict { PACKAGE_PIN A18 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[6] }];
set_property -dict { PACKAGE_PIN K16 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[7] }];

# PMOD JB
set_property -dict { PACKAGE_PIN E15 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[8] }];
set_property -dict { PACKAGE_PIN E16 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[9] }];
set_property -dict { PACKAGE_PIN D15 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[10] }];
set_property -dict { PACKAGE_PIN C15 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[11] }];
set_property -dict { PACKAGE_PIN J17 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[12] }];
set_property -dict { PACKAGE_PIN J18 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[13] }];
set_property -dict { PACKAGE_PIN K15 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[14] }];
set_property -dict { PACKAGE_PIN J15 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[15] }];

# PMOD JC
set_property -dict { PACKAGE_PIN U12 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[16] }];
set_property -dict { PACKAGE_PIN V12 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[17] }];
set_property -dict { PACKAGE_PIN V10 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[18] }];
set_property -dict { PACKAGE_PIN V11 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[19] }];
set_property -dict { PACKAGE_PIN U14 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[20] }];
set_property -dict { PACKAGE_PIN V14 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[21] }];
set_property -dict { PACKAGE_PIN T13 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[22] }];
set_property -dict { PACKAGE_PIN U13 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[23] }];

# PMOD JD
set_property -dict { PACKAGE_PIN D4 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[24] }];
set_property -dict { PACKAGE_PIN D3 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[25] }];
set_property -dict { PACKAGE_PIN F4 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[26] }];
set_property -dict { PACKAGE_PIN F3 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[27] }];
set_property -dict { PACKAGE_PIN E2 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[28] }];
set_property -dict { PACKAGE_PIN D2 IOSTANDARD LVCMOS33 } [get_ports { rgb_extern_leds_tri_o[29] }];

# UART WiFi Tx
set_property PACKAGE_PIN G2 [get_ports {uart_wifi_txd}]
set_property IOSTANDARD LVCMOS33 [get_ports {uart_wifi_txd}]

# UART WiFi Rx
set_property PACKAGE_PIN H2 [get_ports {uart_wifi_rxd}]
set_property IOSTANDARD LVCMOS33 [get_ports {uart_wifi_rxd}]

# UART LCD Tx
set_property PACKAGE_PIN V17 [get_ports {uart_lcd_txd}]
set_property IOSTANDARD LVCMOS33 [get_ports {uart_lcd_txd}]

# UART LCD Rx
set_property PACKAGE_PIN U18 [get_ports {uart_lcd_rxd}]
set_property IOSTANDARD LVCMOS33 [get_ports {uart_lcd_rxd}]

# bitgen settings
set_property CONFIG_MODE SPIx4 [current_design]
set_property BITSTREAM.CONFIG.SPI_32BIT_ADDR NO [current_design]
set_property BITSTREAM.CONFIG.SPI_BUSWIDTH 4 [current_design]
set_property BITSTREAM.CONFIG.SPI_FALL_EDGE YES [current_design]
set_property BITSTREAM.CONFIG.UNUSEDPIN PULLNONE [current_design]
set_property BITSTREAM.CONFIG.CONFIGRATE 66 [current_design]
set_property CONFIG_VOLTAGE 3.3 [current_design]
set_property CFGBVS VCCO [current_design]
set_property BITSTREAM.CONFIG.M0PIN PULLUP [current_design]
set_property BITSTREAM.CONFIG.M1PIN PULLDOWN [current_design]
set_property BITSTREAM.CONFIG.M2PIN PULLDOWN [current_design]

set_property -dict { PACKAGE_PIN G18    IOSTANDARD LVCMOS33 } [get_ports { eth_ref_clk }]; #         Sch=eth_ref_clk 
set_property -dict { PACKAGE_PIN C2    IOSTANDARD LVCMOS33 } [get_ports { reset }]; #         Sch=reset 

# Set Compression
set_property BITSTREAM.GENERAL.COMPRESS TRUE [current_design]

