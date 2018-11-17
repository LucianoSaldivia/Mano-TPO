################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
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
all: Para_Proyecto_Version_02_1.axf

# Tool invocations
Para_Proyecto_Version_02_1.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L/home/lsldv/Descargas/Bibliotecas_de_Giura -Xlinker -Map="Para_Proyecto_Version_02_1.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "pruebaBiblioteca_Debug.ld" -o "Para_Proyecto_Version_02_1.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) Para_Proyecto_Version_02_1.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Para_Proyecto_Version_02_1.axf"; # arm-none-eabi-objcopy -v -O binary "Para_Proyecto_Version_02_1.axf" "Para_Proyecto_Version_02_1.bin" ; # checksum -p LPC1769 -d "Para_Proyecto_Version_02_1.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
