################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../dataclasses/CDSensorTMBufferStatus/src/cdsensortmbufferstatus.cpp 

OBJS += \
./dataclasses/CDSensorTMBufferStatus/src/cdsensortmbufferstatus.o 

CPP_DEPS += \
./dataclasses/CDSensorTMBufferStatus/src/cdsensortmbufferstatus.d 


# Each subdirectory must supply rules for building sources it contributes
dataclasses/CDSensorTMBufferStatus/src/%.o: ../dataclasses/CDSensorTMBufferStatus/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


