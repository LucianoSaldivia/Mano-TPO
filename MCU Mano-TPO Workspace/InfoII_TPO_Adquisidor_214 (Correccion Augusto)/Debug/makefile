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
all: InfoII_TPO_Adquisidor_214\ (Correccion\ Augusto).axf

# Tool invocations
InfoII_TPO_Adquisidor_214\ (Correccion\ Augusto).axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="InfoII_TPO_Adquisidor_214 (Correccion Augusto).map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "LPC1769_Mano_Adquisidor_Debug.ld" -o "InfoII_TPO_Adquisidor_214 (Correccion Augusto).axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) "InfoII_TPO_Adquisidor_214 (Correccion Augusto).axf"
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "InfoII_TPO_Adquisidor_214 (Correccion Augusto).axf"; # arm-none-eabi-objcopy -v -O binary "InfoII_TPO_Adquisidor_214 (Correccion Augusto).axf" "InfoII_TPO_Adquisidor_214 (Correccion Augusto).bin" ; # checksum -p LPC1769 -d "InfoII_TPO_Adquisidor_214 (Correccion Augusto).bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
