################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.c \
../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.c \
../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.c \
../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.c 

OBJS += \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.o \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.o \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.o \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.o 

C_DEPS += \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.d \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.d \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.d \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USB_Host_Library/Core/Src/%.o Middlewares/ST/STM32_USB_Host_Library/Core/Src/%.su Middlewares/ST/STM32_USB_Host_Library/Core/Src/%.cyclo: ../Middlewares/ST/STM32_USB_Host_Library/Core/Src/%.c Middlewares/ST/STM32_USB_Host_Library/Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../LWIP/App -I../LWIP/Target -I../USB_HOST/App -I../USB_HOST/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FatFs/src -I../Drivers/BSP/Components/lan8742 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-STM32_USB_Host_Library-2f-Core-2f-Src

clean-Middlewares-2f-ST-2f-STM32_USB_Host_Library-2f-Core-2f-Src:
	-$(RM) ./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.cyclo ./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.d ./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.o ./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.su ./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.cyclo ./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.d ./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.o ./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.su ./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.cyclo ./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.d ./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.o ./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.su ./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.cyclo ./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.d ./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.o ./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.su

.PHONY: clean-Middlewares-2f-ST-2f-STM32_USB_Host_Library-2f-Core-2f-Src

