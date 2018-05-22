################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/delay.c \
../src/ff.c \
../src/fpu.c \
../src/main.c \
../src/sdmodule.c \
../src/sensor.c \
../src/spi_sd.c \
../src/syscalls.c \
../src/system_stm32f4xx.c \
../src/tm_stm32f4_delay.c \
../src/tm_stm32f4_gpio.c \
../src/tm_stm32f4_hd44780.c 

OBJS += \
./src/delay.o \
./src/ff.o \
./src/fpu.o \
./src/main.o \
./src/sdmodule.o \
./src/sensor.o \
./src/spi_sd.o \
./src/syscalls.o \
./src/system_stm32f4xx.o \
./src/tm_stm32f4_delay.o \
./src/tm_stm32f4_gpio.o \
./src/tm_stm32f4_hd44780.o 

C_DEPS += \
./src/delay.d \
./src/ff.d \
./src/fpu.d \
./src/main.d \
./src/sdmodule.d \
./src/sensor.d \
./src/spi_sd.d \
./src/syscalls.d \
./src/system_stm32f4xx.d \
./src/tm_stm32f4_delay.d \
./src/tm_stm32f4_gpio.d \
./src/tm_stm32f4_hd44780.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -DSTM32F4DISCOVERY -DDEBUG -DSTM32F40XX -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -I"C:/Users/Staszek/Documents/GitHub/TrueOrFalseGame/Utilities" -I"C:/Users/Staszek/Documents/GitHub/TrueOrFalseGame/StdPeriph_Driver/inc" -I"C:/Users/Staszek/Documents/GitHub/TrueOrFalseGame/inc" -I"C:/Users/Staszek/Documents/GitHub/TrueOrFalseGame/CMSIS/device" -I"C:/Users/Staszek/Documents/GitHub/TrueOrFalseGame/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


