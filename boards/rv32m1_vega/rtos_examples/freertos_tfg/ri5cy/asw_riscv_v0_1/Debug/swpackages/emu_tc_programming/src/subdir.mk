################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../swpackages/emu_tc_programming/src/emu_tc_programming.cpp 

OBJS += \
./swpackages/emu_tc_programming/src/emu_tc_programming.o 

CPP_DEPS += \
./swpackages/emu_tc_programming/src/emu_tc_programming.d 


# Each subdirectory must supply rules for building sources it contributes
swpackages/emu_tc_programming/src/%.o: ../swpackages/emu_tc_programming/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


