################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ap/ap.c 

OBJS += \
./src/ap/ap.o 

C_DEPS += \
./src/ap/ap.d 


# Each subdirectory must supply rules for building sources it contributes
src/ap/%.o src/ap/%.su src/ap/%.cyclo: ../src/ap/%.c src/ap/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F407xx -c -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/03_timer/src" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/03_timer/src/ap" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/03_timer/src/bsp" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/03_timer/src/common" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/03_timer/src/hw" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/03_timer/src/bsp/cmsis" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/03_timer/src/bsp/cmsis/Include" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/03_timer/src/bsp/ldscript" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/03_timer/src/bsp/startup" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/03_timer/src/lib/STM32F4xx_HAL_Driver/Inc" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/03_timer/src/common/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-ap

clean-src-2f-ap:
	-$(RM) ./src/ap/ap.cyclo ./src/ap/ap.d ./src/ap/ap.o ./src/ap/ap.su

.PHONY: clean-src-2f-ap

