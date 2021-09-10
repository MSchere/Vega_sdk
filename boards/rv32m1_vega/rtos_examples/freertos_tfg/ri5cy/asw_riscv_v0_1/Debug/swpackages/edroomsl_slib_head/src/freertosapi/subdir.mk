################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../swpackages/edroomsl_slib_head/src/freertosapi/edroomsl.cpp 

OBJS += \
./swpackages/edroomsl_slib_head/src/freertosapi/edroomsl.o 

CPP_DEPS += \
./swpackages/edroomsl_slib_head/src/freertosapi/edroomsl.d 


# Each subdirectory must supply rules for building sources it contributes
swpackages/edroomsl_slib_head/src/freertosapi/%.o: ../swpackages/edroomsl_slib_head/src/freertosapi/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


