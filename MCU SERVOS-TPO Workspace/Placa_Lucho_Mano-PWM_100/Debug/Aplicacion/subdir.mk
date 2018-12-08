################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Aplicacion/AP_UART_0.c \
../Aplicacion/MDE_Guante_Mano.c \
../Aplicacion/MDE_PC_Mano.c \
../Aplicacion/Placa_Lucho_Mano-PWM_100.c 

OBJS += \
./Aplicacion/AP_UART_0.o \
./Aplicacion/MDE_Guante_Mano.o \
./Aplicacion/MDE_PC_Mano.o \
./Aplicacion/Placa_Lucho_Mano-PWM_100.o 

C_DEPS += \
./Aplicacion/AP_UART_0.d \
./Aplicacion/MDE_Guante_Mano.d \
./Aplicacion/MDE_PC_Mano.d \
./Aplicacion/Placa_Lucho_Mano-PWM_100.d 


# Each subdirectory must supply rules for building sources it contributes
Aplicacion/%.o: ../Aplicacion/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU SERVOS-TPO Workspace/Placa_Lucho_Mano-PWM_100/Aplicacion/inc" -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU SERVOS-TPO Workspace/Placa_Lucho_Mano-PWM_100/Drivers/inc" -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU SERVOS-TPO Workspace/Placa_Lucho_Mano-PWM_100/Primitivas/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


