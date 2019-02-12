################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/Applications/ti/ccsv8/ccs_base/arm/include" --include_path="/Applications/ti/ccsv8/ccs_base/arm/include/CMSIS" --include_path="/Users/kyleprice/Desktop/SeniorClinic/workspace/SandiaClinic/BlinkLED_432" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --advice:power=all --define=ccs --define=__MSP432E401Y__ -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_msp432e401y_ccs.obj: ../startup_msp432e401y_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/Applications/ti/ccsv8/ccs_base/arm/include" --include_path="/Applications/ti/ccsv8/ccs_base/arm/include/CMSIS" --include_path="/Users/kyleprice/Desktop/SeniorClinic/workspace/SandiaClinic/BlinkLED_432" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --advice:power=all --define=ccs --define=__MSP432E401Y__ -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="startup_msp432e401y_ccs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

system_msp432e401y.obj: ../system_msp432e401y.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/Applications/ti/ccsv8/ccs_base/arm/include" --include_path="/Applications/ti/ccsv8/ccs_base/arm/include/CMSIS" --include_path="/Users/kyleprice/Desktop/SeniorClinic/workspace/SandiaClinic/BlinkLED_432" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --advice:power=all --define=ccs --define=__MSP432E401Y__ -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="system_msp432e401y.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


