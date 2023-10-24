################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/bsp.c \
../src/bsp/stm32f4xx_it.c 

OBJS += \
./src/bsp/bsp.o \
./src/bsp/stm32f4xx_it.o 

C_DEPS += \
./src/bsp/bsp.d \
./src/bsp/stm32f4xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/%.o src/bsp/%.su src/bsp/%.cyclo: ../src/bsp/%.c src/bsp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F407xx -c -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/05_uart/src" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/05_uart/src/ap" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/05_uart/src/bsp" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/05_uart/src/common" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/05_uart/src/hw" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/05_uart/src/bsp/cmsis" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/05_uart/src/bsp/cmsis/Include" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/05_uart/src/bsp/ldscript" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/05_uart/src/bsp/startup" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/05_uart/src/lib/STM32F4xx_HAL_Driver/Inc" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/05_uart/src/common/include" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/05_uart/src/common/core" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-bsp

clean-src-2f-bsp:
	-$(RM) ./src/bsp/bsp.cyclo ./src/bsp/bsp.d ./src/bsp/bsp.o ./src/bsp/bsp.su ./src/bsp/stm32f4xx_it.cyclo ./src/bsp/stm32f4xx_it.d ./src/bsp/stm32f4xx_it.o ./src/bsp/stm32f4xx_it.su

.PHONY: clean-src-2f-bsp

