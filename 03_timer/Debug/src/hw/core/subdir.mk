################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hw/core/button.c \
../src/hw/core/led.c \
../src/hw/core/timer.c 

OBJS += \
./src/hw/core/button.o \
./src/hw/core/led.o \
./src/hw/core/timer.o 

C_DEPS += \
./src/hw/core/button.d \
./src/hw/core/led.d \
./src/hw/core/timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/hw/core/%.o src/hw/core/%.su src/hw/core/%.cyclo: ../src/hw/core/%.c src/hw/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F407xx -c -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/03_timer/src" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/03_timer/src/ap" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/03_timer/src/bsp" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/03_timer/src/common" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/03_timer/src/hw" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/03_timer/src/bsp/cmsis" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/03_timer/src/bsp/cmsis/Include" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/03_timer/src/bsp/ldscript" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/03_timer/src/bsp/startup" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/03_timer/src/lib/STM32F4xx_HAL_Driver/Inc" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/03_timer/src/common/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-hw-2f-core

clean-src-2f-hw-2f-core:
	-$(RM) ./src/hw/core/button.cyclo ./src/hw/core/button.d ./src/hw/core/button.o ./src/hw/core/button.su ./src/hw/core/led.cyclo ./src/hw/core/led.d ./src/hw/core/led.o ./src/hw/core/led.su ./src/hw/core/timer.cyclo ./src/hw/core/timer.d ./src/hw/core/timer.o ./src/hw/core/timer.su

.PHONY: clean-src-2f-hw-2f-core

