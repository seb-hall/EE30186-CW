# 1 ".\\mbed-os\\targets\\TARGET_STM\\TARGET_STM32F0\\TARGET_STM32F070xB\\TOOLCHAIN_ARM\\startup_stm32f070xb.S"
# 1 "<built-in>" 1
# 370 "<built-in>"
# 1 "./BUILD/NUCLEO_F070RB/ARMC6\\mbed_config.h" 1
# 371 "<built-in>" 2
# 1 ".\\mbed-os\\targets\\TARGET_STM\\TARGET_STM32F0\\TARGET_STM32F070xB\\TOOLCHAIN_ARM\\startup_stm32f070xb.S" 2
;*******************************************************************************
;* File Name : startup_stm32f070xb.s
;* Author : MCD Application Team
;* Description : STM32F070x8/1 devices vector table for MDK-ARM toolchain.
;* This module performs:
;* - Set the initial SP
;* - Set the initial PC == Reset_Handler
;* - Set the vector table entries with the exceptions ISR address
;* - Branches to __main in the C library (which eventually
;* calls main()).
;* After Reset the CortexM0 processor is in Thread mode,
;* priority is Privileged, and the Stack is set to Main.
;********************************************************************************
;* @attention
;*
;* Copyright (c) 2016 STMicroelectronics.
;* All rights reserved.
;*
;* This software component is licensed by ST under BSD 3-Clause license,
;* the "License"; You may not use this file except in compliance with the
;* License. You may obtain a copy of the License at:
;* opensource.org/licenses/BSD-3-Clause
;*
;*******************************************************************************
;* <<< Use Configuration Wizard in Context Menu >>>
;

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA RESET, DATA, READONLY
                EXPORT __Vectors
                EXPORT __Vectors_End
                EXPORT __Vectors_Size

                IMPORT |Image$$ARM_LIB_STACK$$ZI$$Limit|
__Vectors DCD |Image$$ARM_LIB_STACK$$ZI$$Limit| ; Top of Stack
                DCD Reset_Handler ; Reset Handler
                DCD NMI_Handler ; NMI Handler
                DCD HardFault_Handler ; Hard Fault Handler
                DCD 0 ; Reserved
                DCD 0 ; Reserved
                DCD 0 ; Reserved
                DCD 0 ; Reserved
                DCD 0 ; Reserved
                DCD 0 ; Reserved
                DCD 0 ; Reserved
                DCD SVC_Handler ; SVCall Handler
                DCD 0 ; Reserved
                DCD 0 ; Reserved
                DCD PendSV_Handler ; PendSV Handler
                DCD SysTick_Handler ; SysTick Handler

                ; External Interrupts
                DCD WWDG_IRQHandler ; Window Watchdog
                DCD 0 ; Reserved
                DCD RTC_IRQHandler ; RTC through EXTI Line
                DCD FLASH_IRQHandler ; FLASH
                DCD RCC_IRQHandler ; RCC
                DCD EXTI0_1_IRQHandler ; EXTI Line 0 and 1
                DCD EXTI2_3_IRQHandler ; EXTI Line 2 and 3
                DCD EXTI4_15_IRQHandler ; EXTI Line 4 to 15
                DCD 0 ; Reserved
                DCD DMA1_Channel1_IRQHandler ; DMA1 Channel 1
                DCD DMA1_Channel2_3_IRQHandler ; DMA1 Channel 2 and Channel 3
                DCD DMA1_Channel4_5_IRQHandler ; DMA1 Channel 4 and Channel 5
                DCD ADC1_IRQHandler ; ADC1
                DCD TIM1_BRK_UP_TRG_COM_IRQHandler ; TIM1 Break, Update, Trigger and Commutation
                DCD TIM1_CC_IRQHandler ; TIM1 Capture Compare
                DCD 0 ; Reserved
                DCD TIM3_IRQHandler ; TIM3
                DCD TIM6_IRQHandler ; TIM6
                DCD TIM7_IRQHandler ; TIM7
                DCD TIM14_IRQHandler ; TIM14
                DCD TIM15_IRQHandler ; TIM15
                DCD TIM16_IRQHandler ; TIM16
                DCD TIM17_IRQHandler ; TIM17
                DCD I2C1_IRQHandler ; I2C1
                DCD I2C2_IRQHandler ; I2C2
                DCD SPI1_IRQHandler ; SPI1
                DCD SPI2_IRQHandler ; SPI2
                DCD USART1_IRQHandler ; USART1
                DCD USART2_IRQHandler ; USART2
                DCD USART3_4_IRQHandler ; USART3 & USART4
                DCD 0 ; Reserved
                DCD USB_IRQHandler ; USB

__Vectors_End

__Vectors_Size EQU __Vectors_End - __Vectors

                AREA |.text|, CODE, READONLY

; Reset handler routine
Reset_Handler PROC
                 EXPORT Reset_Handler [WEAK]
        IMPORT __main
        IMPORT SystemInit
                 LDR R0, =SystemInit
                 BLX R0
                 LDR R0, =__main
                 BX R0
                 ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler PROC
                EXPORT NMI_Handler [WEAK]
                B .
                ENDP
HardFault_Handler PROC

                EXPORT HardFault_Handler [WEAK]
                B .
                ENDP
SVC_Handler PROC
                EXPORT SVC_Handler [WEAK]
                B .
                ENDP
PendSV_Handler PROC
                EXPORT PendSV_Handler [WEAK]
                B .
                ENDP
SysTick_Handler PROC
                EXPORT SysTick_Handler [WEAK]
                B .
                ENDP

Default_Handler PROC

                EXPORT WWDG_IRQHandler [WEAK]
                EXPORT RTC_IRQHandler [WEAK]
                EXPORT FLASH_IRQHandler [WEAK]
                EXPORT RCC_IRQHandler [WEAK]
                EXPORT EXTI0_1_IRQHandler [WEAK]
                EXPORT EXTI2_3_IRQHandler [WEAK]
                EXPORT EXTI4_15_IRQHandler [WEAK]
                EXPORT DMA1_Channel1_IRQHandler [WEAK]
                EXPORT DMA1_Channel2_3_IRQHandler [WEAK]
                EXPORT DMA1_Channel4_5_IRQHandler [WEAK]
                EXPORT ADC1_IRQHandler [WEAK]
                EXPORT TIM1_BRK_UP_TRG_COM_IRQHandler [WEAK]
                EXPORT TIM1_CC_IRQHandler [WEAK]
                EXPORT TIM3_IRQHandler [WEAK]
                EXPORT TIM6_IRQHandler [WEAK]
                EXPORT TIM7_IRQHandler [WEAK]
                EXPORT TIM14_IRQHandler [WEAK]
                EXPORT TIM15_IRQHandler [WEAK]
                EXPORT TIM16_IRQHandler [WEAK]
                EXPORT TIM17_IRQHandler [WEAK]
                EXPORT I2C1_IRQHandler [WEAK]
                EXPORT I2C2_IRQHandler [WEAK]
                EXPORT SPI1_IRQHandler [WEAK]
                EXPORT SPI2_IRQHandler [WEAK]
                EXPORT USART1_IRQHandler [WEAK]
                EXPORT USART2_IRQHandler [WEAK]
                EXPORT USART3_4_IRQHandler [WEAK]
                EXPORT USB_IRQHandler [WEAK]


WWDG_IRQHandler
RTC_IRQHandler
FLASH_IRQHandler
RCC_IRQHandler
EXTI0_1_IRQHandler
EXTI2_3_IRQHandler
EXTI4_15_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_3_IRQHandler
DMA1_Channel4_5_IRQHandler
ADC1_IRQHandler
TIM1_BRK_UP_TRG_COM_IRQHandler
TIM1_CC_IRQHandler
TIM3_IRQHandler
TIM6_IRQHandler
TIM7_IRQHandler
TIM14_IRQHandler
TIM15_IRQHandler
TIM16_IRQHandler
TIM17_IRQHandler
I2C1_IRQHandler
I2C2_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
USART3_4_IRQHandler
USB_IRQHandler

                B .

                ENDP

                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************

                 END

;************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE*****
