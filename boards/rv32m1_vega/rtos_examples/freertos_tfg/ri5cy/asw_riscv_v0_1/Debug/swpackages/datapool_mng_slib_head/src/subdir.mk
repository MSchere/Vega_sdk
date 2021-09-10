################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../swpackages/datapool_mng_slib_head/src/datapool_mng.cpp 

OBJS += \
./swpackages/datapool_mng_slib_head/src/datapool_mng.o 

CPP_DEPS += \
./swpackages/datapool_mng_slib_head/src/datapool_mng.d 


# Each subdirectory must supply rules for building sources it contributes
swpackages/datapool_mng_slib_head/src/%.o: ../swpackages/datapool_mng_slib_head/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


