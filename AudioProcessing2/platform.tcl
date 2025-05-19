# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\vivado_audiosoc\eval-synthesiser\AudioProcessing2\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\vivado_audiosoc\eval-synthesiser\AudioProcessing2\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {AudioProcessing2}\
-hw {C:\vivado_audiosoc\AudioProcessing2.xsa}\
-out {C:/vivado_audiosoc/eval-synthesiser}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {hello_world}
platform generate -domains 
platform active {AudioProcessing2}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
platform generate
platform generate -domains standalone_ps7_cortexa9_0,zynq_fsbl 
platform generate
platform generate -domains standalone_ps7_cortexa9_0,zynq_fsbl 
platform active {AudioProcessing2}
platform config -updatehw {C:/Users/axelc/Downloads/audio_interrupt_user_btn.xsa}
platform generate -domains 
platform clean
platform generate
platform config -updatehw {C:/Users/axelc/Downloads/audioprocessing2.xsa}
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform config -updatehw {C:/Users/axelc/Downloads/AudioProcessing2.xsa}
platform clean
platform clean
platform clean
platform generate
