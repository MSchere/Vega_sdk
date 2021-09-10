################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_channel_drv.cpp \
../swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_pus_service12.cpp \
../swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_pus_service128.cpp \
../swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_pus_service17.cpp \
../swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_pus_service19.cpp \
../swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_pus_service3.cpp \
../swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_pus_service6.cpp \
../swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_pus_service9.cpp 

OBJS += \
./swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_channel_drv.o \
./swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_pus_service12.o \
./swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_pus_service128.o \
./swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_pus_service17.o \
./swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_pus_service19.o \
./swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_pus_service3.o \
./swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_pus_service6.o \
./swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_pus_service9.o 

CPP_DEPS += \
./swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_channel_drv.d \
./swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_pus_service12.d \
./swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_pus_service128.d \
./swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_pus_service17.d \
./swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_pus_service19.d \
./swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_pus_service3.d \
./swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_pus_service6.d \
./swpackages/emu_sc_channel_drv_slib_head/src/emu_sc_pus_service9.d 


# Each subdirectory must supply rules for building sources it contributes
swpackages/emu_sc_channel_drv_slib_head/src/%.o: ../swpackages/emu_sc_channel_drv_slib_head/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


