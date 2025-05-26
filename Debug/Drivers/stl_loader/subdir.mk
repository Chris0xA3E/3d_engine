################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/stl_loader/stl_loader.c 

OBJS += \
./Drivers/stl_loader/stl_loader.o 

C_DEPS += \
./Drivers/stl_loader/stl_loader.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/stl_loader/%.o Drivers/stl_loader/%.su Drivers/stl_loader/%.cyclo: ../Drivers/stl_loader/%.c Drivers/stl_loader/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"/home/master/Workspace/STM32/3d_engine/Drivers/stl_loader" -I"/home/master/Workspace/STM32/3d_engine/Drivers/mpu-6050" -I"/home/master/Workspace/STM32/3d_engine/Drivers/3d_engine" -I"/home/master/Workspace/STM32/3d_engine/Utilities" -I"/home/master/Workspace/STM32/3d_engine/Drivers/BSP/STM32746G-Discovery" -I"/home/master/Workspace/STM32/3d_engine/Drivers/BSP/Components" -I../FATFS/Target -I../FATFS/App -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FatFs/src -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../LIBJPEG/App -I../LIBJPEG/Target -I../Middlewares/Third_Party/LibJPEG/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-stl_loader

clean-Drivers-2f-stl_loader:
	-$(RM) ./Drivers/stl_loader/stl_loader.cyclo ./Drivers/stl_loader/stl_loader.d ./Drivers/stl_loader/stl_loader.o ./Drivers/stl_loader/stl_loader.su

.PHONY: clean-Drivers-2f-stl_loader

