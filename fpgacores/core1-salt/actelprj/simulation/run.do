quietly set ACTELLIBNAME proasic3
quietly set PROJECT_DIR "Y:/Documents/work/xpress/fpgacores/core1-salt/actelprj"

if {[file exists presynth/_info]} {
   echo "INFO: Simulation library presynth already exists"
} else {
   vlib presynth
}
vmap presynth presynth
vmap proasic3 "C:/Actel/Libero_v9.1/Designer/lib/modelsim/precompiled/vhdl/proasic3"

vcom -93 -explicit -work presynth "${PROJECT_DIR}/hdl/xpress_uart.vhd"
vcom -93 -explicit -work presynth "${PROJECT_DIR}/hdl/txt_util.vhd"
vcom -93 -explicit -work presynth "${PROJECT_DIR}/hdl/test_uart.vhd"
vcom -93 -explicit -work presynth "${PROJECT_DIR}/hdl/xpress.vhd"

vsim -L proasic3 -L presynth  -t 1ps presynth.test_uart
# The following lines are commented because no testbench is associated with the project
# add wave /testbench/*
# run 1000ns
