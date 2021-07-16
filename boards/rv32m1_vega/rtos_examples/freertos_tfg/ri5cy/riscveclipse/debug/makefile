################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include swpackages/xprintf_slib_head/src/posix_v13/linux_2_6/subdir.mk
-include swpackages/exit_slib_c99/src/posix_v13/subdir.mk
-include swpackages/edroombp_slib_head/src/freertossapi/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include pswpackages/freertosapi_freertos_x86_v1/src/subdir.mk
-include osswpackages/freertos/src/portable/MemMang/subdir.mk
-include osswpackages/freertos/src/portable/GCC/Posix/subdir.mk
-include osswpackages/freertos/src/portable/subdir.mk
-include osswpackages/freertos/src/subdir.mk
-include drivers/freertos/subdir.mk
-include drivers/subdir.mk
-include board/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: freertos_tfg_ri5cy_rv32m1_vega.elf secondary-outputs

# Tool invocations
freertos_tfg_ri5cy_rv32m1_vega.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU RISC-V Cross C Linker'
	riscv32-unknown-elf-gcc -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -ffreestanding -fno-builtin -Wall  -g -T ../settings/RV32M1_ri5cy_flash.ld -nostdlib -Xlinker --gc-sections -Wl,-Map,"freertos_tfg_ri5cy_rv32m1_vega.map" -march=rv32imcxpulpv2 -Xlinker -static -Xlinker -z -Xlinker muldefs -Xlinker -static  -Xlinker -z  -Xlinker muldefs -o "freertos_tfg_ri5cy_rv32m1_vega.elf" -Xlinker --start-group $(OBJS) $(USER_OBJS) $(LIBS) -Xlinker --end-group
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) freertos_tfg_ri5cy_rv32m1_vega.elf
	-@echo ' '

secondary-outputs:

.PHONY: all clean dependents

-include ../makefile.targets
