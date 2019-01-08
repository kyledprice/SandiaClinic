################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
ccs/startup_msp432e401y_ccs.obj: ../ccs/startup_msp432e401y_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/Users/kyleprice/Desktop/SeniorClinic/workspace/SandiaClinic/fw/fw5v0" --include_path="/Applications/ti/simplelink_msp432e4_sdk_2_20_00_20/source/third_party/CMSIS/Include" --include_path="/Applications/ti/simplelink_msp432e4_sdk_2_20_00_20/source" --include_path="/Applications/ti/simplelink_msp432e4_sdk_2_20_00_20/source/ti/net/bsd" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" --advice:power=none --define=DeviceFamily_MSP432E4 --define=__MSP432E401Y__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="ccs/startup_msp432e401y_ccs.d_raw" --obj_directory="ccs" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


