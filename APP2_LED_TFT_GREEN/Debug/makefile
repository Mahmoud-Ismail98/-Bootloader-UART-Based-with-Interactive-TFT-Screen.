################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/MCAL/SYSTICK/subdir.mk
-include Src/MCAL/SPI/subdir.mk
-include Src/MCAL/RCC/subdir.mk
-include Src/MCAL/GPIO/subdir.mk
-include Src/HAL/TFT/subdir.mk
-include Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := APP2_LED_TFT_GREEN
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
APP2_LED_TFT_GREEN.elf \

MAP_FILES += \
APP2_LED_TFT_GREEN.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
APP2_LED_TFT_GREEN.list \

OBJCOPY_HEX += \
APP2_LED_TFT_GREEN.hex \


# All Target
all: main-build

# Main-build Target
main-build: APP2_LED_TFT_GREEN.elf secondary-outputs

# Tool invocations
APP2_LED_TFT_GREEN.elf APP2_LED_TFT_GREEN.map: $(OBJS) $(USER_OBJS) H:\test\ARM_prgect\eclipse_workspace\bootloader_project\APP2_LED_TFT_GREEN\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "APP2_LED_TFT_GREEN.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"H:\test\ARM_prgect\eclipse_workspace\bootloader_project\APP2_LED_TFT_GREEN\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="APP2_LED_TFT_GREEN.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

APP2_LED_TFT_GREEN.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "APP2_LED_TFT_GREEN.list"
	@echo 'Finished building: $@'
	@echo ' '

APP2_LED_TFT_GREEN.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "APP2_LED_TFT_GREEN.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) APP2_LED_TFT_GREEN.elf APP2_LED_TFT_GREEN.hex APP2_LED_TFT_GREEN.list APP2_LED_TFT_GREEN.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
