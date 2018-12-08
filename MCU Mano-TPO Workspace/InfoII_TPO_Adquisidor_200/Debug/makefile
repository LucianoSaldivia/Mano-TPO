################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Primitivas/src/subdir.mk
-include Drivers/src/subdir.mk
-include Aplicacion/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: LPC1769\ Mano\ 2.2.axf

# Tool invocations
LPC1769\ Mano\ 2.2.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="LPC1769 Mano 2.2.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "LPC1769_Mano_2_2_Debug.ld" -o "LPC1769 Mano 2.2.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) "LPC1769 Mano 2.2.axf"
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "LPC1769 Mano 2.2.axf"; # arm-none-eabi-objcopy -v -O binary "LPC1769 Mano 2.2.axf" "LPC1769 Mano 2.2.bin" ; # checksum -p LPC1769 -d "LPC1769 Mano 2.2.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
