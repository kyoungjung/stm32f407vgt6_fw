################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.c \
../src/lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_eth.c 

OBJS += \
./src/lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.o \
./src/lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_eth.o 

C_DEPS += \
./src/lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.d \
./src/lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_eth.d 


# Each subdirectory must supply rules for building sources it contributes
src/lib/STM32F4xx_HAL_Driver/Src/Legacy/%.o src/lib/STM32F4xx_HAL_Driver/Src/Legacy/%.su src/lib/STM32F4xx_HAL_Driver/Src/Legacy/%.cyclo: ../src/lib/STM32F4xx_HAL_Driver/Src/Legacy/%.c src/lib/STM32F4xx_HAL_Driver/Src/Legacy/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F407xx -c -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/01_led/src" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/01_led/src/ap" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/01_led/src/bsp" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/01_led/src/common" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/01_led/src/hw" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/01_led/src/bsp/cmsis" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/01_led/src/bsp/cmsis/Include" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/01_led/src/bsp/ldscript" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/01_led/src/bsp/startup" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/01_led/src/lib/STM32F4xx_HAL_Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-lib-2f-STM32F4xx_HAL_Driver-2f-Src-2f-Legacy

clean-src-2f-lib-2f-STM32F4xx_HAL_Driver-2f-Src-2f-Legacy:
	-$(RM) ./src/lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.cyclo ./src/lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.d ./src/lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.o ./src/lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_can.su ./src/lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_eth.cyclo ./src/lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_eth.d ./src/lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_eth.o ./src/lib/STM32F4xx_HAL_Driver/Src/Legacy/stm32f4xx_hal_eth.su

.PHONY: clean-src-2f-lib-2f-STM32F4xx_HAL_Driver-2f-Src-2f-Legacy

