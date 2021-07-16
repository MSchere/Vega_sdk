################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
C:/Vega/rv32m1_sdk_riscv/rtos/freertos_9.0.0/Source/portable/GCC/RISCY/portASM.S 

OBJS += \
./osswpackages/freertos/src/portable/port.o \
./osswpackages/freertos/src/portable/portASM.o 

S_UPPER_DEPS += \
./osswpackages/freertos/src/portable/portASM.d 

C_DEPS += \
./osswpackages/freertos/src/portable/port.d 


# Each subdirectory must supply rules for building sources it contributes
osswpackages/freertos/src/portable/port.o: C:/Vega/rv32m1_sdk_riscv/rtos/freertos_9.0.0/Source/portable/GCC/RISCY/port.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-unknown-elf-gcc -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -ffreestanding -fno-builtin -Wall  -g -DDEBUG -DCPU_RV32M1_ri5cy -DFSL_RTOS_FREE_RTOS -I"C:\Vega\rv32m1_sdk_riscv\boards\rv32m1_vega\rtos_examples\freertos_tfg\ri5cy\riscveclipse\pswpackages\freertosapi_freertos_x86_v1\include" -I"C:\Vega\rv32m1_sdk_riscv\boards\rv32m1_vega\rtos_examples\freertos_tfg\ri5cy\riscveclipse\swinterfaces\exit_iface_c99\include" -I"C:\Vega\rv32m1_sdk_riscv\boards\rv32m1_vega\rtos_examples\freertos_tfg\ri5cy\riscveclipse\swpackages\edroombp_slib_head\include" -I"C:\Vega\rv32m1_sdk_riscv\boards\rv32m1_vega\rtos_examples\freertos_tfg\ri5cy\riscveclipse\pswpackages\freertosapi_freertos_x86_v1\include\platform" -I"C:\Vega\rv32m1_sdk_riscv\boards\rv32m1_vega\rtos_examples\freertos_tfg\ri5cy\riscveclipse\osswpackages\freertos\src\portable\GCC\Posix" -I"C:\Vega\rv32m1_sdk_riscv\boards\rv32m1_vega\rtos_examples\freertos_tfg\ri5cy\riscveclipse\osswinterfaces\freertosapi\include\public" -I"C:\Vega\rv32m1_sdk_riscv\boards\rv32m1_vega\rtos_examples\freertos_tfg\ri5cy\riscveclipse\swinterfaces\stdarg_iface_c99\include" -I"C:\Vega\rv32m1_sdk_riscv\boards\rv32m1_vega\rtos_examples\freertos_tfg\ri5cy\riscveclipse\swinterfaces\xprintf_iface_v1\include" -I"C:\Vega\rv32m1_sdk_riscv\boards\rv32m1_vega\rtos_examples\freertos_tfg\ri5cy\riscveclipse\swpackages\xprintf_slib_head\include" -I"C:\Vega\rv32m1_sdk_riscv\boards\rv32m1_vega\rtos_examples\freertos_tfg\ri5cy\riscveclipse\config\include" -I../../../../../../../rtos/freertos_9.0.0/Source/portable/GCC/RISCY -I../../../../../../../rtos/freertos_9.0.0/Source/include -I../../../../../../../RISCV -I../../../../../../../devices -I../../.. -I../../../../.. -I../../../../../../../rtos/freertos_9.0.0/Source -I../../../../../../../devices/RV32M1/drivers -I../../../../../../../devices/RV32M1/utilities -I../../../../../../../devices/RV32M1/utilities/io -I../../../../../../../devices/RV32M1/utilities/str -I../../../../../../../devices/RV32M1/utilities/log -I../../../../../../../devices/RV32M1 -I../.. -I../../../../../freertos_config_board/ri5cy -I"C:\Vega\rv32m1_sdk_riscv\boards\rv32m1_vega\rtos_examples\freertos_tfg\ri5cy\riscveclipse\osswpackages\freertos\src\portable\GCC\Posix" -std=gnu99 -march=rv32imcxpulpv2 -Wa,-march=rv32imcxpulpv2 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

osswpackages/freertos/src/portable/portASM.o: C:/Vega/rv32m1_sdk_riscv/rtos/freertos_9.0.0/Source/portable/GCC/RISCY/portASM.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross Assembler'
	riscv32-unknown-elf-gcc -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -ffreestanding -fno-builtin -Wall  -g -x assembler-with-cpp -DDEBUG -I../../.. -I../../../../.. -I../../../../../freertos_config_board/ri5cy -I../.. -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


