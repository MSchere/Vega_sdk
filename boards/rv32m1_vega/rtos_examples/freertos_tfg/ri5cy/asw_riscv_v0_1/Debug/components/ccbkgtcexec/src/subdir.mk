################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../components/ccbkgtcexec/src/CCBKGTCExecB.cpp \
../components/ccbkgtcexec/src/CCBKGTCExecS.cpp 

OBJS += \
./components/ccbkgtcexec/src/CCBKGTCExecB.o \
./components/ccbkgtcexec/src/CCBKGTCExecS.o 

CPP_DEPS += \
./components/ccbkgtcexec/src/CCBKGTCExecB.d \
./components/ccbkgtcexec/src/CCBKGTCExecS.d 


# Each subdirectory must supply rules for building sources it contributes
components/ccbkgtcexec/src/%.o: ../components/ccbkgtcexec/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


