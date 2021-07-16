################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../swpackages/exit_slib_c99/src/posix_v13/exit_iface.c 

OBJS += \
./swpackages/exit_slib_c99/src/posix_v13/exit_iface.o 

C_DEPS += \
./swpackages/exit_slib_c99/src/posix_v13/exit_iface.d 


# Each subdirectory must supply rules for building sources it contributes
swpackages/exit_slib_c99/src/posix_v13/%.o: ../swpackages/exit_slib_c99/src/posix_v13/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv32-unknown-elf-gcc -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -ffreestanding -fno-builtin -Wall  -g -DDEBUG -DCPU_RV32M1_ri5cy -DFSL_RTOS_FREE_RTOS -I"C:\Vega\rv32m1_sdk_riscv\boards\rv32m1_vega\rtos_examples\freertos_tfg\ri5cy\riscveclipse\pswpackages\freertosapi_freertos_x86_v1\include" -I"C:\Vega\rv32m1_sdk_riscv\boards\rv32m1_vega\rtos_examples\freertos_tfg\ri5cy\riscveclipse\swinterfaces\exit_iface_c99\include" -I"C:\Vega\rv32m1_sdk_riscv\boards\rv32m1_vega\rtos_examples\freertos_tfg\ri5cy\riscveclipse\swpackages\edroombp_slib_head\include" -I"C:\Vega\rv32m1_sdk_riscv\boards\rv32m1_vega\rtos_examples\freertos_tfg\ri5cy\riscveclipse\pswpackages\freertosapi_freertos_x86_v1\include\platform" -I"C:\Vega\rv32m1_sdk_riscv\boards\rv32m1_vega\rtos_examples\freertos_tfg\ri5cy\riscveclipse\osswpackages\freertos\src\portable\GCC\Posix" -I"C:\Vega\rv32m1_sdk_riscv\boards\rv32m1_vega\rtos_examples\freertos_tfg\ri5cy\riscveclipse\osswinterfaces\freertosapi\include\public" -I"C:\Vega\rv32m1_sdk_riscv\boards\rv32m1_vega\rtos_examples\freertos_tfg\ri5cy\riscveclipse\swinterfaces\stdarg_iface_c99\include" -I"C:\Vega\rv32m1_sdk_riscv\boards\rv32m1_vega\rtos_examples\freertos_tfg\ri5cy\riscveclipse\swinterfaces\xprintf_iface_v1\include" -I"C:\Vega\rv32m1_sdk_riscv\boards\rv32m1_vega\rtos_examples\freertos_tfg\ri5cy\riscveclipse\swpackages\xprintf_slib_head\include" -I"C:\Vega\rv32m1_sdk_riscv\boards\rv32m1_vega\rtos_examples\freertos_tfg\ri5cy\riscveclipse\config\include" -I../../../../../../../rtos/freertos_9.0.0/Source/portable/GCC/RISCY -I../../../../../../../rtos/freertos_9.0.0/Source/include -I../../../../../../../RISCV -I../../../../../../../devices -I../../.. -I../../../../.. -I../../../../../../../rtos/freertos_9.0.0/Source -I../../../../../../../devices/RV32M1/drivers -I../../../../../../../devices/RV32M1/utilities -I../../../../../../../devices/RV32M1/utilities/io -I../../../../../../../devices/RV32M1/utilities/str -I../../../../../../../devices/RV32M1/utilities/log -I../../../../../../../devices/RV32M1 -I../.. -I../../../../../freertos_config_board/ri5cy -I"C:\Vega\rv32m1_sdk_riscv\boards\rv32m1_vega\rtos_examples\freertos_tfg\ri5cy\riscveclipse\osswpackages\freertos\src\portable\GCC\Posix" -std=gnu99 -march=rv32imcxpulpv2 -Wa,-march=rv32imcxpulpv2 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


