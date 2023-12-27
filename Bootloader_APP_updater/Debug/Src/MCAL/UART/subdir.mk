################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/UART/USART_program.c 

OBJS += \
./Src/MCAL/UART/USART_program.o 

C_DEPS += \
./Src/MCAL/UART/USART_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/UART/%.o Src/MCAL/UART/%.su Src/MCAL/UART/%.cyclo: ../Src/MCAL/UART/%.c Src/MCAL/UART/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"H:/test/ARM_prgect/Bootloader-UART-Based-with-Interactive-TFT-Screen/Bootloader_Updater_APP/SERVICES" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-UART

clean-Src-2f-MCAL-2f-UART:
	-$(RM) ./Src/MCAL/UART/USART_program.cyclo ./Src/MCAL/UART/USART_program.d ./Src/MCAL/UART/USART_program.o ./Src/MCAL/UART/USART_program.su

.PHONY: clean-Src-2f-MCAL-2f-UART

