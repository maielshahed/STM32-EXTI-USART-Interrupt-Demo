################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/EXTI_prog.c \
../Src/GPIO_prog.c \
../Src/SysCfg_prog.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/EXTI_prog.o \
./Src/GPIO_prog.o \
./Src/SysCfg_prog.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/EXTI_prog.d \
./Src/GPIO_prog.d \
./Src/SysCfg_prog.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/EXTI_prog.cyclo ./Src/EXTI_prog.d ./Src/EXTI_prog.o ./Src/EXTI_prog.su ./Src/GPIO_prog.cyclo ./Src/GPIO_prog.d ./Src/GPIO_prog.o ./Src/GPIO_prog.su ./Src/SysCfg_prog.cyclo ./Src/SysCfg_prog.d ./Src/SysCfg_prog.o ./Src/SysCfg_prog.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

