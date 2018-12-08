################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Primitivas/src/PR_LCD.c \
../Primitivas/src/PR_Serie.c \
../Primitivas/src/pr_muestreo_5canales.c 

OBJS += \
./Primitivas/src/PR_LCD.o \
./Primitivas/src/PR_Serie.o \
./Primitivas/src/pr_muestreo_5canales.o 

C_DEPS += \
./Primitivas/src/PR_LCD.d \
./Primitivas/src/PR_Serie.d \
./Primitivas/src/pr_muestreo_5canales.d 


# Each subdirectory must supply rules for building sources it contributes
Primitivas/src/%.o: ../Primitivas/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/LPC1769 Mano 2.2/Aplicacion/inc" -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/LPC1769 Mano 2.2/Drivers/inc" -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/LPC1769 Mano 2.2/Primitivas/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


