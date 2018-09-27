################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/AP_Prueba1.c \
../src/AP_PruebaUART.c \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/main.c 

OBJS += \
./src/AP_Prueba1.o \
./src/AP_PruebaUART.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/main.o 

C_DEPS += \
./src/AP_Prueba1.d \
./src/AP_PruebaUART.d \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I/home/lsldv/Descargas/Bibliotecas_de_Giura -I"/home/lsldv/Documents/MCUXpresso_10.2.0_759/workspace/Prueba1/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


