################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include freertos_9.0.0/Source/portable/low_power_tickless/subdir.mk
-include freertos_9.0.0/Source/portable/MemMang/subdir.mk
-include freertos_9.0.0/Source/portable/GCC/RISCY/subdir.mk
-include freertos_9.0.0/Source/subdir.mk
-include board/subdir.mk
-include RV32M1_src/utilities/subdir.mk
-include RV32M1_src/gcc/subdir.mk
-include RV32M1_src/drivers/subdir.mk
-include RV32M1_src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
HelloWorldRISC-V.hex \

SECONDARY_SIZE += \
HelloWorldRISC-V.siz \


# All Target
all: HelloWorldRISC-V.elf secondary-outputs

# Tool invocations
HelloWorldRISC-V.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU RISC-V Cross C++ Linker'
	riscv-none-embed-g++ -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "/home/opolo70/RISCV_workspace/HelloWorldRISC-V/settings/RV32M1_ri5cy_flash.ld" -Xlinker --gc-sections -Wl,-Map,"HelloWorldRISC-V.map" --specs=nosys.specs -o "HelloWorldRISC-V.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

HelloWorldRISC-V.hex: HelloWorldRISC-V.elf
	@echo 'Invoking: GNU RISC-V Cross Create Flash Image'
	riscv-none-embed-objcopy -O ihex "HelloWorldRISC-V.elf"  "HelloWorldRISC-V.hex"
	@echo 'Finished building: $@'
	@echo ' '

HelloWorldRISC-V.siz: HelloWorldRISC-V.elf
	@echo 'Invoking: GNU RISC-V Cross Print Size'
	riscv-none-embed-size --format=berkeley "HelloWorldRISC-V.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS)$(CPP_DEPS) HelloWorldRISC-V.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
