################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/FPEC/FPEC_program.c \
../Src/MCAL/FPEC/Parse.c 

OBJS += \
./Src/MCAL/FPEC/FPEC_program.o \
./Src/MCAL/FPEC/Parse.o 

C_DEPS += \
./Src/MCAL/FPEC/FPEC_program.d \
./Src/MCAL/FPEC/Parse.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/FPEC/%.o Src/MCAL/FPEC/%.su Src/MCAL/FPEC/%.cyclo: ../Src/MCAL/FPEC/%.c Src/MCAL/FPEC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"H:/test/ARM_prgect/Bootloader-UART-Based-with-Interactive-TFT-Screen/Bootloader_APP_updater/SERVICES" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-FPEC

clean-Src-2f-MCAL-2f-FPEC:
	-$(RM) ./Src/MCAL/FPEC/FPEC_program.cyclo ./Src/MCAL/FPEC/FPEC_program.d ./Src/MCAL/FPEC/FPEC_program.o ./Src/MCAL/FPEC/FPEC_program.su ./Src/MCAL/FPEC/Parse.cyclo ./Src/MCAL/FPEC/Parse.d ./Src/MCAL/FPEC/Parse.o ./Src/MCAL/FPEC/Parse.su

.PHONY: clean-Src-2f-MCAL-2f-FPEC

