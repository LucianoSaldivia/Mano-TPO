################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Aplicacion/src/AP_MdE.c \
../Aplicacion/src/AP_muestreo_mano.c \
../Aplicacion/src/main.c 

OBJS += \
./Aplicacion/src/AP_MdE.o \
./Aplicacion/src/AP_muestreo_mano.o \
./Aplicacion/src/main.o 

C_DEPS += \
./Aplicacion/src/AP_MdE.d \
./Aplicacion/src/AP_muestreo_mano.d \
./Aplicacion/src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Aplicacion/src/%.o: ../Aplicacion/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/LPC1769 Mano 2.2/Aplicacion/inc" -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/LPC1769 Mano 2.2/Drivers/inc" -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/LPC1769 Mano 2.2/Primitivas/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


