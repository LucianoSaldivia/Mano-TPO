################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Aplicacion/AP_UART_0.c \
../Aplicacion/AP_muestreo_mano.c \
../Aplicacion/MDE_Adquisidor.c \
../Aplicacion/main.c 

OBJS += \
./Aplicacion/AP_UART_0.o \
./Aplicacion/AP_muestreo_mano.o \
./Aplicacion/MDE_Adquisidor.o \
./Aplicacion/main.o 

C_DEPS += \
./Aplicacion/AP_UART_0.d \
./Aplicacion/AP_muestreo_mano.d \
./Aplicacion/MDE_Adquisidor.d \
./Aplicacion/main.d 


# Each subdirectory must supply rules for building sources it contributes
Aplicacion/%.o: ../Aplicacion/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/InfoII_TPO_Adquisidor_213/Aplicacion/inc" -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/InfoII_TPO_Adquisidor_213/Drivers/inc" -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/InfoII_TPO_Adquisidor_213/Drivers" -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/InfoII_TPO_Adquisidor_213/Primitivas/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


