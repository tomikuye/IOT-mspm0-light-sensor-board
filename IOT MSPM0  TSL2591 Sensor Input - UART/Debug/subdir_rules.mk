################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs1281/ccs/tools/compiler/ti-cgt-armllvm_3.2.1.LTS/bin/tiarmclang" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"/Users/tomikuye/workspace_v12/IOT MSPM0  TSL2591 Sensor Input - UART" -I"/Users/tomikuye/workspace_v12/IOT MSPM0  TSL2591 Sensor Input - UART/Debug" -I"/Users/tomikuye/ti/mspm0_sdk_2_04_00_06/source/third_party/CMSIS/Core/Include" -I"/Users/tomikuye/ti/mspm0_sdk_2_04_00_06/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1152682367: ../i2c_controller_rw_multibyte_fifo_poll.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"/Users/tomikuye/ti/sysconfig_1.22.0/sysconfig_cli.sh" --script "/Users/tomikuye/workspace_v12/IOT MSPM0  TSL2591 Sensor Input - UART/i2c_controller_rw_multibyte_fifo_poll.syscfg" -o "." -s "/Users/tomikuye/ti/mspm0_sdk_2_04_00_06/.metadata/product.json" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-1152682367 ../i2c_controller_rw_multibyte_fifo_poll.syscfg
device.opt: build-1152682367
device.cmd.genlibs: build-1152682367
ti_msp_dl_config.c: build-1152682367
ti_msp_dl_config.h: build-1152682367
Event.dot: build-1152682367

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs1281/ccs/tools/compiler/ti-cgt-armllvm_3.2.1.LTS/bin/tiarmclang" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"/Users/tomikuye/workspace_v12/IOT MSPM0  TSL2591 Sensor Input - UART" -I"/Users/tomikuye/workspace_v12/IOT MSPM0  TSL2591 Sensor Input - UART/Debug" -I"/Users/tomikuye/ti/mspm0_sdk_2_04_00_06/source/third_party/CMSIS/Core/Include" -I"/Users/tomikuye/ti/mspm0_sdk_2_04_00_06/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: /Users/tomikuye/ti/mspm0_sdk_2_04_00_06/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/Applications/ti/ccs1281/ccs/tools/compiler/ti-cgt-armllvm_3.2.1.LTS/bin/tiarmclang" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"/Users/tomikuye/workspace_v12/IOT MSPM0  TSL2591 Sensor Input - UART" -I"/Users/tomikuye/workspace_v12/IOT MSPM0  TSL2591 Sensor Input - UART/Debug" -I"/Users/tomikuye/ti/mspm0_sdk_2_04_00_06/source/third_party/CMSIS/Core/Include" -I"/Users/tomikuye/ti/mspm0_sdk_2_04_00_06/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


