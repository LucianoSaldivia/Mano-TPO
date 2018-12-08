################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/src/FW_GPIO.c \
../Drivers/src/FW_IO.c \
../Drivers/src/FW_PINSEL.c \
../Drivers/src/FW_SysTick.c \
../Drivers/src/FW_UART.c \
../Drivers/src/cr_startup_lpc175x_6x.c \
../Drivers/src/crp.c \
../Drivers/src/dr_ADC_5canales_timer.c 

OBJS += \
./Drivers/src/FW_GPIO.o \
./Drivers/src/FW_IO.o \
./Drivers/src/FW_PINSEL.o \
./Drivers/src/FW_SysTick.o \
./Drivers/src/FW_UART.o \
./Drivers/src/cr_startup_lpc175x_6x.o \
./Drivers/src/crp.o \
./Drivers/src/dr_ADC_5canales_timer.o 

C_DEPS += \
./Drivers/src/FW_GPIO.d \
./Drivers/src/FW_IO.d \
./Drivers/src/FW_PINSEL.d \
./Drivers/src/FW_SysTick.d \
./Drivers/src/FW_UART.d \
./Drivers/src/cr_startup_lpc175x_6x.d \
./Drivers/src/crp.d \
./Drivers/src/dr_ADC_5canales_timer.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/src/%.o: ../Drivers/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/LPC1769 Mano 2.2/Aplicacion/inc" -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/LPC1769 Mano 2.2/Drivers/inc" -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/LPC1769 Mano 2.2/Primitivas/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


