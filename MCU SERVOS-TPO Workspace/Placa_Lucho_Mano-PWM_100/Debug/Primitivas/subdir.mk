################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Primitivas/PR_LCD.c \
../Primitivas/PR_PWM.c \
../Primitivas/PR_Teclas.c \
../Primitivas/PR_UART_0.c 

OBJS += \
./Primitivas/PR_LCD.o \
./Primitivas/PR_PWM.o \
./Primitivas/PR_Teclas.o \
./Primitivas/PR_UART_0.o 

C_DEPS += \
./Primitivas/PR_LCD.d \
./Primitivas/PR_PWM.d \
./Primitivas/PR_Teclas.d \
./Primitivas/PR_UART_0.d 


# Each subdirectory must supply rules for building sources it contributes
Primitivas/%.o: ../Primitivas/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU SERVOS-TPO Workspace/Placa_Lucho_Mano-PWM_100/Aplicacion/inc" -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU SERVOS-TPO Workspace/Placa_Lucho_Mano-PWM_100/Drivers/inc" -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU SERVOS-TPO Workspace/Placa_Lucho_Mano-PWM_100/Primitivas/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


