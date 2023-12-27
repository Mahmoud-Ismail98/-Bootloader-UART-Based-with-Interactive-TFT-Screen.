################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/SYSTICK/STK_program.c 

OBJS += \
./Src/MCAL/SYSTICK/STK_program.o 

C_DEPS += \
./Src/MCAL/SYSTICK/STK_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/SYSTICK/%.o Src/MCAL/SYSTICK/%.su Src/MCAL/SYSTICK/%.cyclo: ../Src/MCAL/SYSTICK/%.c Src/MCAL/SYSTICK/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"H:/test/ARM_prgect/Bootloader-UART-Based-with-Interactive-TFT-Screen/Bootloader_Updater_APP/SERVICES" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-SYSTICK

clean-Src-2f-MCAL-2f-SYSTICK:
	-$(RM) ./Src/MCAL/SYSTICK/STK_program.cyclo ./Src/MCAL/SYSTICK/STK_program.d ./Src/MCAL/SYSTICK/STK_program.o ./Src/MCAL/SYSTICK/STK_program.su

.PHONY: clean-Src-2f-MCAL-2f-SYSTICK

