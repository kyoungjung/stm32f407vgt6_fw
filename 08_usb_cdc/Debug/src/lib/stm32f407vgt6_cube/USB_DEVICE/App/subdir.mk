################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lib/stm32f407vgt6_cube/USB_DEVICE/App/usb_device.c \
../src/lib/stm32f407vgt6_cube/USB_DEVICE/App/usbd_cdc_if.c \
../src/lib/stm32f407vgt6_cube/USB_DEVICE/App/usbd_desc.c 

OBJS += \
./src/lib/stm32f407vgt6_cube/USB_DEVICE/App/usb_device.o \
./src/lib/stm32f407vgt6_cube/USB_DEVICE/App/usbd_cdc_if.o \
./src/lib/stm32f407vgt6_cube/USB_DEVICE/App/usbd_desc.o 

C_DEPS += \
./src/lib/stm32f407vgt6_cube/USB_DEVICE/App/usb_device.d \
./src/lib/stm32f407vgt6_cube/USB_DEVICE/App/usbd_cdc_if.d \
./src/lib/stm32f407vgt6_cube/USB_DEVICE/App/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
src/lib/stm32f407vgt6_cube/USB_DEVICE/App/%.o src/lib/stm32f407vgt6_cube/USB_DEVICE/App/%.su src/lib/stm32f407vgt6_cube/USB_DEVICE/App/%.cyclo: ../src/lib/stm32f407vgt6_cube/USB_DEVICE/App/%.c src/lib/stm32f407vgt6_cube/USB_DEVICE/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F407xx -c -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/08_usb_cdc/src/lib/stm32f407vgt6_cube/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/08_usb_cdc/src/lib/stm32f407vgt6_cube/Drivers/CMSIS/Include" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/08_usb_cdc/src" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/08_usb_cdc/src/lib/stm32f407vgt6_cube/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/08_usb_cdc/src/ap" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/08_usb_cdc/src/bsp" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/08_usb_cdc/src/common" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/08_usb_cdc/src/hw" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/08_usb_cdc/src/bsp/ldscript" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/08_usb_cdc/src/bsp/startup" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/08_usb_cdc/src/common/include" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/08_usb_cdc/src/common/core" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/08_usb_cdc/src/lib/stm32f407vgt6_cube/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/08_usb_cdc/src/lib/stm32f407vgt6_cube/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/08_usb_cdc/src/lib/stm32f407vgt6_cube/USB_DEVICE/App" -I"D:/git/stm32f407vgt6/stm32f407vgt6_fw/08_usb_cdc/src/lib/stm32f407vgt6_cube/USB_DEVICE/Target" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-lib-2f-stm32f407vgt6_cube-2f-USB_DEVICE-2f-App

clean-src-2f-lib-2f-stm32f407vgt6_cube-2f-USB_DEVICE-2f-App:
	-$(RM) ./src/lib/stm32f407vgt6_cube/USB_DEVICE/App/usb_device.cyclo ./src/lib/stm32f407vgt6_cube/USB_DEVICE/App/usb_device.d ./src/lib/stm32f407vgt6_cube/USB_DEVICE/App/usb_device.o ./src/lib/stm32f407vgt6_cube/USB_DEVICE/App/usb_device.su ./src/lib/stm32f407vgt6_cube/USB_DEVICE/App/usbd_cdc_if.cyclo ./src/lib/stm32f407vgt6_cube/USB_DEVICE/App/usbd_cdc_if.d ./src/lib/stm32f407vgt6_cube/USB_DEVICE/App/usbd_cdc_if.o ./src/lib/stm32f407vgt6_cube/USB_DEVICE/App/usbd_cdc_if.su ./src/lib/stm32f407vgt6_cube/USB_DEVICE/App/usbd_desc.cyclo ./src/lib/stm32f407vgt6_cube/USB_DEVICE/App/usbd_desc.d ./src/lib/stm32f407vgt6_cube/USB_DEVICE/App/usbd_desc.o ./src/lib/stm32f407vgt6_cube/USB_DEVICE/App/usbd_desc.su

.PHONY: clean-src-2f-lib-2f-stm32f407vgt6_cube-2f-USB_DEVICE-2f-App

