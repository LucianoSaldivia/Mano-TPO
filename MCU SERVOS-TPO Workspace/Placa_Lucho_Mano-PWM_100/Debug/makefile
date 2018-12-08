################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Primitivas/subdir.mk
-include Drivers/subdir.mk
-include Aplicacion/subdir.mk
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
all: Placa_Lucho_Mano-PWM_100.axf

# Tool invocations
Placa_Lucho_Mano-PWM_100.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="Placa_Lucho_Mano-PWM_100.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "Placa_Lucho_Mano-PWM_100_Debug.ld" -o "Placa_Lucho_Mano-PWM_100.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) Placa_Lucho_Mano-PWM_100.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Placa_Lucho_Mano-PWM_100.axf"; # arm-none-eabi-objcopy -v -O binary "Placa_Lucho_Mano-PWM_100.axf" "Placa_Lucho_Mano-PWM_100.bin" ; # checksum -p LPC1769 -d "Placa_Lucho_Mano-PWM_100.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
