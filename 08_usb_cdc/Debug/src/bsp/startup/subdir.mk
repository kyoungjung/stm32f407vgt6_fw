################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../src/bsp/startup/startup_stm32f407vgtx.s 

OBJS += \
./src/bsp/startup/startup_stm32f407vgtx.o 

S_DEPS += \
./src/bsp/startup/startup_stm32f407vgtx.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/startup/%.o: ../src/bsp/startup/%.s src/bsp/startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/08_usb_cdc/src/common/core" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/08_usb_cdc/src/lib/stm32f407vgt6_cube/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/08_usb_cdc/src/lib/stm32f407vgt6_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/08_usb_cdc/src/lib/stm32f407vgt6_cube/USB_DEVICE/App" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/08_usb_cdc/src/lib/stm32f407vgt6_cube/USB_DEVICE/Target" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-src-2f-bsp-2f-startup

clean-src-2f-bsp-2f-startup:
	-$(RM) ./src/bsp/startup/startup_stm32f407vgtx.d ./src/bsp/startup/startup_stm32f407vgtx.o

.PHONY: clean-src-2f-bsp-2f-startup

