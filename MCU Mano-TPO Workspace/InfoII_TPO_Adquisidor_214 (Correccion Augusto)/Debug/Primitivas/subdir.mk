################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Primitivas/PR_LCD.c \
../Primitivas/PR_Mediana_5canales.c \
../Primitivas/PR_UART_0.c 

OBJS += \
./Primitivas/PR_LCD.o \
./Primitivas/PR_Mediana_5canales.o \
./Primitivas/PR_UART_0.o 

C_DEPS += \
./Primitivas/PR_LCD.d \
./Primitivas/PR_Mediana_5canales.d \
./Primitivas/PR_UART_0.d 


# Each subdirectory must supply rules for building sources it contributes
Primitivas/%.o: ../Primitivas/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/InfoII_TPO_Adquisidor_214 (Correccion Augusto)/Aplicacion/inc" -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/InfoII_TPO_Adquisidor_214 (Correccion Augusto)/Drivers/inc" -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/InfoII_TPO_Adquisidor_214 (Correccion Augusto)/Drivers" -I"/home/cha/UTN FRBA/info2_Proyecto_2018/MCU Mano-TPO Workspace/InfoII_TPO_Adquisidor_214 (Correccion Augusto)/Primitivas/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


