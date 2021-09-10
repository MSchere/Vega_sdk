################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include swpackages/xprintf_slib_head/src/posix_v13/linux_2_6/subdir.mk
-include swpackages/icuasw_pus_services_slib_head/src/subdir.mk
-include swpackages/exit_slib_c99/src/posix_v13/subdir.mk
-include swpackages/emu_tc_programming/src/subdir.mk
-include swpackages/emu_sc_channel_drv_slib_head/src/subdir.mk
-include swpackages/edroomtc_slib_head/src/subdir.mk
-include swpackages/edroomsl_slib_head/src/freertosapi/subdir.mk
-include swpackages/edroombp_slib_head/src/freertossapi/freertos_posix/subdir.mk
-include swpackages/edroombp_slib_head/src/freertossapi/subdir.mk
-include swpackages/datapool_mng_slib_head/src/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include pswpackages/freertosapi_freertos_x86_v1/src/subdir.mk
-include freertos/portable/subdir.mk
-include freertos/subdir.mk
-include edroom_glue/src/subdir.mk
-include drivers/freertos/subdir.mk
-include drivers/subdir.mk
-include dataclasses/CDSensorTMBufferStatus/src/subdir.mk
-include components/icuasw/src/subdir.mk
-include components/cctm_channelctrl/src/subdir.mk
-include components/cchk_fdirmng/src/subdir.mk
-include components/ccepdmanager/src/subdir.mk
-include components/ccbkgtcexec/src/subdir.mk
-include board/subdir.mk
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
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: asw_riscv_v0_1

# Tool invocations
asw_riscv_v0_1: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++  -o "asw_riscv_v0_1" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(C_DEPS)$(CPP_DEPS) asw_riscv_v0_1
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
