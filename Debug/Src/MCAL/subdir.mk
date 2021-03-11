################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/ADC_program.c \
../Src/MCAL/AFIO_program.c \
../Src/MCAL/EXTI_program.c \
../Src/MCAL/GPIO_program.c \
../Src/MCAL/NVIC_program.c \
../Src/MCAL/RCC_program.c \
../Src/MCAL/Timer_program.c \
../Src/MCAL/USART1_program.c 

OBJS += \
./Src/MCAL/ADC_program.o \
./Src/MCAL/AFIO_program.o \
./Src/MCAL/EXTI_program.o \
./Src/MCAL/GPIO_program.o \
./Src/MCAL/NVIC_program.o \
./Src/MCAL/RCC_program.o \
./Src/MCAL/Timer_program.o \
./Src/MCAL/USART1_program.o 

C_DEPS += \
./Src/MCAL/ADC_program.d \
./Src/MCAL/AFIO_program.d \
./Src/MCAL/EXTI_program.d \
./Src/MCAL/GPIO_program.d \
./Src/MCAL/NVIC_program.d \
./Src/MCAL/RCC_program.d \
./Src/MCAL/Timer_program.d \
./Src/MCAL/USART1_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/ADC_program.o: ../Src/MCAL/ADC_program.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/MCAL/ADC_program.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/MCAL/AFIO_program.o: ../Src/MCAL/AFIO_program.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/MCAL/AFIO_program.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/MCAL/EXTI_program.o: ../Src/MCAL/EXTI_program.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/MCAL/EXTI_program.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/MCAL/GPIO_program.o: ../Src/MCAL/GPIO_program.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/MCAL/GPIO_program.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/MCAL/NVIC_program.o: ../Src/MCAL/NVIC_program.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/MCAL/NVIC_program.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/MCAL/RCC_program.o: ../Src/MCAL/RCC_program.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/MCAL/RCC_program.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/MCAL/Timer_program.o: ../Src/MCAL/Timer_program.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/MCAL/Timer_program.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/MCAL/USART1_program.o: ../Src/MCAL/USART1_program.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/MCAL/USART1_program.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

