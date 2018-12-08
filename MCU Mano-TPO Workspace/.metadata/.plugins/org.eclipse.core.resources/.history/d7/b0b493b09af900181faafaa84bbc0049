################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Aplicacion/AP_Guante_Muestreo.c \
../Aplicacion/AP_UART_1.c \
../Aplicacion/MDE_Adquisidor.c \
../Aplicacion/main.c 

OBJS += \
./Aplicacion/AP_Guante_Muestreo.o \
./Aplicacion/AP_UART_1.o \
./Aplicacion/MDE_Adquisidor.o \
./Aplicacion/main.o 

C_DEPS += \
./Aplicacion/AP_Guante_Muestreo.d \
./Aplicacion/AP_UART_1.d \
./Aplicacion/MDE_Adquisidor.d \
./Aplicacion/main.d 


# Each subdirectory must supply rules for building sources it contributes
Aplicacion/%.o: ../Aplicacion/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/InfoII_TPO_Adquisidor_400_UART1/Aplicacion/inc" -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/InfoII_TPO_Adquisidor_400_UART1/Drivers/inc" -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/InfoII_TPO_Adquisidor_400_UART1/Drivers" -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/InfoII_TPO_Adquisidor_400_UART1/Primitivas/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


