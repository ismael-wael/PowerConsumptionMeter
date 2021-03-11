################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/HLCD_config.c \
../Src/HAL/HLCD_program.c \
../Src/HAL/Hswitch_config.c \
../Src/HAL/Hswitch_program.c \
../Src/HAL/Led_config.c \
../Src/HAL/Led_porogram.c 

OBJS += \
./Src/HAL/HLCD_config.o \
./Src/HAL/HLCD_program.o \
./Src/HAL/Hswitch_config.o \
./Src/HAL/Hswitch_program.o \
./Src/HAL/Led_config.o \
./Src/HAL/Led_porogram.o 

C_DEPS += \
./Src/HAL/HLCD_config.d \
./Src/HAL/HLCD_program.d \
./Src/HAL/Hswitch_config.d \
./Src/HAL/Hswitch_program.d \
./Src/HAL/Led_config.d \
./Src/HAL/Led_porogram.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/HLCD_config.o: ../Src/HAL/HLCD_config.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/HAL/HLCD_config.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/HAL/HLCD_program.o: ../Src/HAL/HLCD_program.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/HAL/HLCD_program.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/HAL/Hswitch_config.o: ../Src/HAL/Hswitch_config.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/HAL/Hswitch_config.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/HAL/Hswitch_program.o: ../Src/HAL/Hswitch_program.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/HAL/Hswitch_program.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/HAL/Led_config.o: ../Src/HAL/Led_config.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/HAL/Led_config.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/HAL/Led_porogram.o: ../Src/HAL/Led_porogram.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/HAL/Led_porogram.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

