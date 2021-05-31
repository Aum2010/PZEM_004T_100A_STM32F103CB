################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../PZEM_004T_100A_103CB_LIB/PZEM_004T_100A_103CB_LIB.cpp 

OBJS += \
./PZEM_004T_100A_103CB_LIB/PZEM_004T_100A_103CB_LIB.o 

CPP_DEPS += \
./PZEM_004T_100A_103CB_LIB/PZEM_004T_100A_103CB_LIB.d 


# Each subdirectory must supply rules for building sources it contributes
PZEM_004T_100A_103CB_LIB/PZEM_004T_100A_103CB_LIB.o: ../PZEM_004T_100A_103CB_LIB/PZEM_004T_100A_103CB_LIB.cpp PZEM_004T_100A_103CB_LIB/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"G:/103C8/103CB_PZEM_004T_100A_OOP/PZEM_004T_100A_103CB_LIB" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"PZEM_004T_100A_103CB_LIB/PZEM_004T_100A_103CB_LIB.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

