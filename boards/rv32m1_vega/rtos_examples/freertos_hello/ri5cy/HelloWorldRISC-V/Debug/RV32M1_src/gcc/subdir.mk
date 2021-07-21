################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../RV32M1_src/gcc/startup_RV32M1_ri5cy.S 

OBJS += \
./RV32M1_src/gcc/startup_RV32M1_ri5cy.o 

S_UPPER_DEPS += \
./RV32M1_src/gcc/startup_RV32M1_ri5cy.d 


# Each subdirectory must supply rules for building sources it contributes
RV32M1_src/gcc/%.o: ../RV32M1_src/gcc/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross Assembler'
	riscv-none-embed-gcc -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -x assembler-with-cpp -I"/home/opolo70/RISCV_workspace/HelloWorldRISC-V/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


