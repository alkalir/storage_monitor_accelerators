# open_project ./$$1$$/sniffer_generic/sniffer_generic.xpr
# update_compile_order -fileset sources_1
# add_files -norecurse ./$$1$$/sniffer_generic/sniffer_generic.srcs/sources_1/imports/sniffer_generic_1.0/hdl/config.vhd
# update_compile_order -fileset sources_1
# ipx::package_project -root_dir ./$$1$$/sniffer_generic/sniffer_generic.srcs/sources_1/imports/sniffer_generic_1.0 -vendor user.org -library user -taxonomy /UserIP -force
# close_project

# create the pack for the sniffer


create_project sniffer_generic_1.0 ./$$1$$/sniffer_generic_1.0 -part $$2$$
set_property board_part $$3$$ [current_project] 
set_property target_language VHDL [current_project]
add_files {./$$1$$/sniffer_generic_1.0/hdl/GMI.vhd ./$$1$$/sniffer_generic_1.0/hdl/adapter_FEBE.vhd ./$$1$$/sniffer_generic_1.0/hdl/sniffer_generic.vhd ./$$1$$/sniffer_generic_1.0/hdl/adapter_CAPH.vhd ./$$1$$/sniffer_generic_1.0/hdl/adapter_axi4full.vhd ./$$1$$/sniffer_generic_1.0/hdl/smart_counter.vhd ./$$1$$/sniffer_generic_1.0/hdl/time_monitor.vhd ./$$1$$/sniffer_generic_1.0/hdl/nucleus.vhd ./$$1$$/sniffer_generic_1.0/hdl/event_monitor.vhd ./$$1$$/sniffer_generic_1.0/hdl/comp_prog.vhd ./$$1$$/sniffer_generic_1.0/hdl/config.vhd}
update_compile_order -fileset sources_1
update_compile_order -fileset sources_1
ipx::package_project -root_dir ./$$1$$/sniffer_generic_1.0 -vendor user.org -library user -taxonomy /UserIP
set_property core_revision 2 [ipx::current_core]
ipx::create_xgui_files [ipx::current_core]
ipx::update_checksums [ipx::current_core]
ipx::save_core [ipx::current_core]
set_property  ip_repo_paths  ./$$1$$/sniffer_generic_1.0 [current_project]
update_ip_catalog
close_project


open_project ./$$1$$/project_top/system.xpr
set_property  ip_repo_paths  {./$$1$$/mm_accelerator ./$$1$$/sniffer_generic_1.0} [current_project]
update_ip_catalog
open_bd_design {./$$1$$/project_top/system.srcs/sources_1/bd/design_1/design_1.bd}
upgrade_ip [get_ips  {design_1_rst_ps7_0_100M_0 design_1_axi_mem_intercon_0 design_1_ps7_0_axi_periph_0 design_1_axi_cdma_0_0}] -log ip_upgrade.log
export_ip_user_files -of_objects [get_ips {design_1_rst_ps7_0_100M_0 design_1_axi_mem_intercon_0 design_1_ps7_0_axi_periph_0 design_1_axi_cdma_0_0}] -no_script -sync -force -quiet
generate_target all [get_files  ./$$1$$/project_top/system.srcs/sources_1/bd/design_1/design_1.bd]
export_ip_user_files -of_objects [get_files ./$$1$$/project_top/system.srcs/sources_1/bd/design_1/design_1.bd] -no_script -sync -force -quiet
create_ip_run [get_files -of_objects [get_fileset sources_1] ./$$1$$/project_top/system.srcs/sources_1/bd/design_1/design_1.bd]
launch_runs -jobs 8 {design_1_processing_system7_0_0_synth_1 design_1_mm_accelerator_0_0_synth_1 design_1_rst_ps7_0_100M_0_synth_1 design_1_axi_cdma_0_0_synth_1 design_1_xbar_1_synth_1 design_1_xbar_2_synth_1 design_1_auto_us_0_synth_1 design_1_auto_ds_0_synth_1 design_1_auto_pc_0_synth_1 design_1_auto_pc_1_synth_1}
export_simulation -of_objects [get_files ./$$1$$/project_top/system.srcs/sources_1/bd/design_1/design_1.bd] -directory ./$$1$$/project_top/system.ip_user_files/sim_scripts -ip_user_files_dir ./$$1$$/project_top/system.ip_user_files -ipstatic_source_dir ./$$1$$/project_top/system.ip_user_files/ipstatic -lib_map_path [list {modelsim=./$$1$$/project_top/system.cache/compile_simlib/modelsim} {questa=./$$1$$/project_top/system.cache/compile_simlib/questa} {riviera=./$$1$$/project_top/system.cache/compile_simlib/riviera} {activehdl=./$$1$$/project_top/system.cache/compile_simlib/activehdl}] -use_ip_compiled_libs -force -quiet
create_bd_cell -type ip -vlnv user.org:user:sniffer_generic:1.0 sniffer_generic_0

set_property -dict [list CONFIG.NUM_MI {3}] [get_bd_cells ps7_0_axi_periph]
connect_bd_intf_net -intf_net ps7_0_axi_periph_M02_AXI [get_bd_intf_pins ps7_0_axi_periph/M02_AXI] [get_bd_intf_pins sniffer_generic_0/s00_axi]

  connect_bd_net -net Net [get_bd_pins axi_cdma_0/m_axi_awready] [get_bd_pins axi_mem_intercon/S00_AXI_awready] [get_bd_pins sniffer_generic_0/awrite_ready]
  connect_bd_net -net Net1 [get_bd_pins axi_cdma_0/m_axi_bresp] [get_bd_pins axi_mem_intercon/S00_AXI_bresp] [get_bd_pins sniffer_generic_0/bwrite_resp]
  connect_bd_net -net Net2 [get_bd_pins axi_cdma_0/m_axi_bvalid] [get_bd_pins axi_mem_intercon/S00_AXI_bvalid] [get_bd_pins sniffer_generic_0/bwrite_valid]
  connect_bd_net -net axi_cdma_0_m_axi_awaddr [get_bd_pins axi_cdma_0/m_axi_awaddr] [get_bd_pins axi_mem_intercon/S00_AXI_awaddr] [get_bd_pins sniffer_generic_0/awrite_addr]
  connect_bd_net -net axi_cdma_0_m_axi_awburst [get_bd_pins axi_cdma_0/m_axi_awburst] [get_bd_pins axi_mem_intercon/S00_AXI_awburst] [get_bd_pins sniffer_generic_0/awrite_burst]
  connect_bd_net -net axi_cdma_0_m_axi_awlen [get_bd_pins axi_cdma_0/m_axi_awlen] [get_bd_pins axi_mem_intercon/S00_AXI_awlen] [get_bd_pins sniffer_generic_0/awrite_len]
  connect_bd_net -net axi_cdma_0_m_axi_awvalid [get_bd_pins axi_cdma_0/m_axi_awvalid] [get_bd_pins axi_mem_intercon/S00_AXI_awvalid] [get_bd_pins sniffer_generic_0/awrite_valid]
  connect_bd_net -net axi_cdma_0_m_axi_bready [get_bd_pins axi_cdma_0/m_axi_bready] [get_bd_pins axi_mem_intercon/S00_AXI_bready] [get_bd_pins sniffer_generic_0/bwrite_ready]
  connect_bd_net -net axi_cdma_0_m_axi_wlast [get_bd_pins axi_cdma_0/m_axi_wlast] [get_bd_pins axi_mem_intercon/S00_AXI_wlast] [get_bd_pins sniffer_generic_0/write_last]
  connect_bd_net -net axi_cdma_0_m_axi_wstrb [get_bd_pins axi_cdma_0/m_axi_wstrb] [get_bd_pins axi_mem_intercon/S00_AXI_wstrb] [get_bd_pins sniffer_generic_0/write_strb]
  connect_bd_net -net axi_cdma_0_m_axi_wvalid [get_bd_pins axi_cdma_0/m_axi_wvalid] [get_bd_pins axi_mem_intercon/S00_AXI_wvalid] [get_bd_pins sniffer_generic_0/write_valid]
  connect_bd_net -net axi_interconnect_0_S00_AXI_wready [get_bd_pins axi_cdma_0/m_axi_wready] [get_bd_pins axi_mem_intercon/S00_AXI_wready] [get_bd_pins sniffer_generic_0/write_ready]
  connect_bd_net -net mm_accelerator_0_tr_done [get_bd_pins mm_accelerator_0/tr_done] [get_bd_pins sniffer_generic_0/acc_done]
  connect_bd_net -net mm_accelerator_0_tr_start [get_bd_pins mm_accelerator_0/tr_start] [get_bd_pins sniffer_generic_0/acc_start]

  connect_bd_net [get_bd_pins mm_accelerator_0/tr_line_buffer_0_in_pel_rd] [get_bd_pins sniffer_generic_0/acc_line_buffer_0_in_pel_rd]
  connect_bd_net [get_bd_pins sniffer_generic_0/acc_fifo_big_line_buffer_0_in_pel_wr] [get_bd_pins mm_accelerator_0/tr_fifo_big_line_buffer_0_in_pel_wr]
  connect_bd_net [get_bd_pins mm_accelerator_0/tr_fifo_big_line_buffer_0_real_size_wr] [get_bd_pins sniffer_generic_0/acc_fifo_big_line_buffer_0_real_size_wr]
  connect_bd_net [get_bd_pins sniffer_generic_0/acc_line_buffer_0_real_size_rd] [get_bd_pins mm_accelerator_0/tr_line_buffer_0_real_size_rd]

connect_bd_net [get_bd_pins sniffer_generic_0/timing] [get_bd_pins processing_system7_0/FCLK_CLK0]
connect_bd_net [get_bd_pins sniffer_generic_0/arstn] [get_bd_pins rst_ps7_0_100M/peripheral_aresetn]
connect_bd_net [get_bd_pins sniffer_generic_0/s00_axi_aresetn] [get_bd_pins rst_ps7_0_100M/peripheral_aresetn]
connect_bd_net [get_bd_pins sniffer_generic_0/s00_axi_aclk] [get_bd_pins processing_system7_0/FCLK_CLK0]
connect_bd_net [get_bd_pins ps7_0_axi_periph/M02_ACLK] [get_bd_pins processing_system7_0/FCLK_CLK0]
connect_bd_net [get_bd_pins ps7_0_axi_periph/M02_ARESETN] [get_bd_pins rst_ps7_0_100M/peripheral_aresetn]
assign_bd_address
save_bd_design
start_gui
