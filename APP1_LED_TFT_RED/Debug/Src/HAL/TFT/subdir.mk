################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/TFT/TFT_program.c \
../Src/HAL/TFT/fonts.c 

OBJS += \
./Src/HAL/TFT/TFT_program.o \
./Src/HAL/TFT/fonts.o 

C_DEPS += \
./Src/HAL/TFT/TFT_program.d \
./Src/HAL/TFT/fonts.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/TFT/%.o Src/HAL/TFT/%.su Src/HAL/TFT/%.cyclo: ../Src/HAL/TFT/%.c Src/HAL/TFT/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"H:/test/ARM_prgect/Bootloader-UART-Based-with-Interactive-TFT-Screen/Bootloader_APP_updater/SERVICES" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-TFT

clean-Src-2f-HAL-2f-TFT:
	-$(RM) ./Src/HAL/TFT/TFT_program.cyclo ./Src/HAL/TFT/TFT_program.d ./Src/HAL/TFT/TFT_program.o ./Src/HAL/TFT/TFT_program.su ./Src/HAL/TFT/fonts.cyclo ./Src/HAL/TFT/fonts.d ./Src/HAL/TFT/fonts.o ./Src/HAL/TFT/fonts.su

.PHONY: clean-Src-2f-HAL-2f-TFT

