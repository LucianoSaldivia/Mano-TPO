################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DR_ADC_5canales_Timer.c \
../Drivers/DR_GPIO.c \
../Drivers/DR_Init.c \
../Drivers/DR_LED_IO.c \
../Drivers/DR_PINSEL.c \
../Drivers/DR_SysTick.c \
../Drivers/DR_Teclas.c \
../Drivers/DR_UART_0.c \
../Drivers/FW_LCD.c \
../Drivers/cr_startup_lpc175x_6x.c \
../Drivers/crp.c 

OBJS += \
./Drivers/DR_ADC_5canales_Timer.o \
./Drivers/DR_GPIO.o \
./Drivers/DR_Init.o \
./Drivers/DR_LED_IO.o \
./Drivers/DR_PINSEL.o \
./Drivers/DR_SysTick.o \
./Drivers/DR_Teclas.o \
./Drivers/DR_UART_0.o \
./Drivers/FW_LCD.o \
./Drivers/cr_startup_lpc175x_6x.o \
./Drivers/crp.o 

C_DEPS += \
./Drivers/DR_ADC_5canales_Timer.d \
./Drivers/DR_GPIO.d \
./Drivers/DR_Init.d \
./Drivers/DR_LED_IO.d \
./Drivers/DR_PINSEL.d \
./Drivers/DR_SysTick.d \
./Drivers/DR_Teclas.d \
./Drivers/DR_UART_0.d \
./Drivers/FW_LCD.d \
./Drivers/cr_startup_lpc175x_6x.d \
./Drivers/crp.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/%.o: ../Drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/InfoII_TPO_Adquisidor_400/Aplicacion/inc" -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/InfoII_TPO_Adquisidor_400/Drivers/inc" -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/InfoII_TPO_Adquisidor_400/Drivers" -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/InfoII_TPO_Adquisidor_400/Primitivas/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


