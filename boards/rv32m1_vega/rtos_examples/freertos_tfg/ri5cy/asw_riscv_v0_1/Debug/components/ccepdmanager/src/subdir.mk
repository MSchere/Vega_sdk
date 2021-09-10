################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../components/ccepdmanager/src/CCEPDManagerB.cpp \
../components/ccepdmanager/src/CCEPDManagerS.cpp 

OBJS += \
./components/ccepdmanager/src/CCEPDManagerB.o \
./components/ccepdmanager/src/CCEPDManagerS.o 

CPP_DEPS += \
./components/ccepdmanager/src/CCEPDManagerB.d \
./components/ccepdmanager/src/CCEPDManagerS.d 


# Each subdirectory must supply rules for building sources it contributes
components/ccepdmanager/src/%.o: ../components/ccepdmanager/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


