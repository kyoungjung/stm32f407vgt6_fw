################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/common/core/qbuffer.c 

OBJS += \
./src/common/core/qbuffer.o 

C_DEPS += \
./src/common/core/qbuffer.d 


# Each subdirectory must supply rules for building sources it contributes
src/common/core/%.o src/common/core/%.su src/common/core/%.cyclo: ../src/common/core/%.c src/common/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F407xx -c -I"D:/work/1000_Git/stm32f407vgt6/09_uart2_3/src/lib/stm32f407vgt6_cube/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/work/1000_Git/stm32f407vgt6/09_uart2_3/src/lib/stm32f407vgt6_cube/Drivers/CMSIS/Include" -I"D:/work/1000_Git/stm32f407vgt6/09_uart2_3/src" -I"D:/work/1000_Git/stm32f407vgt6/09_uart2_3/src/lib/stm32f407vgt6_cube/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/work/1000_Git/stm32f407vgt6/09_uart2_3/src/ap" -I"D:/work/1000_Git/stm32f407vgt6/09_uart2_3/src/bsp" -I"D:/work/1000_Git/stm32f407vgt6/09_uart2_3/src/common" -I"D:/work/1000_Git/stm32f407vgt6/09_uart2_3/src/hw" -I"D:/work/1000_Git/stm32f407vgt6/09_uart2_3/src/bsp/ldscript" -I"D:/work/1000_Git/stm32f407vgt6/09_uart2_3/src/bsp/startup" -I"D:/work/1000_Git/stm32f407vgt6/09_uart2_3/src/common/include" -I"D:/work/1000_Git/stm32f407vgt6/09_uart2_3/src/common/core" -I"D:/work/1000_Git/stm32f407vgt6/09_uart2_3/src/lib/stm32f407vgt6_cube/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/work/1000_Git/stm32f407vgt6/09_uart2_3/src/lib/stm32f407vgt6_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/work/1000_Git/stm32f407vgt6/09_uart2_3/src/lib/stm32f407vgt6_cube/USB_DEVICE/App" -I"D:/work/1000_Git/stm32f407vgt6/09_uart2_3/src/lib/stm32f407vgt6_cube/USB_DEVICE/Target" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-common-2f-core

clean-src-2f-common-2f-core:
	-$(RM) ./src/common/core/qbuffer.cyclo ./src/common/core/qbuffer.d ./src/common/core/qbuffer.o ./src/common/core/qbuffer.su

.PHONY: clean-src-2f-common-2f-core

