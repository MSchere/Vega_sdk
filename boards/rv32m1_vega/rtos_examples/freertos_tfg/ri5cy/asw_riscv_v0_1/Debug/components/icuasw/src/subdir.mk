################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../components/icuasw/src/ICUASWB.cpp \
../components/icuasw/src/ICUASWS.cpp 

OBJS += \
./components/icuasw/src/ICUASWB.o \
./components/icuasw/src/ICUASWS.o 

CPP_DEPS += \
./components/icuasw/src/ICUASWB.d \
./components/icuasw/src/ICUASWS.d 


# Each subdirectory must supply rules for building sources it contributes
components/icuasw/src/%.o: ../components/icuasw/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


