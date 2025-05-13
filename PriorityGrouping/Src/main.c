/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mai El Shahed
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "RCC_interface.h"
#include "SysTick_interface.h"
#include "NVIC_interface.h"
#include "GPIO_interface.h"

volatile uint8_t USART3_interrupt_flag = 0;
volatile uint8_t EXIT13_interrupt_flag = 0;

int main(void)
{
    RCC_SETCLK(HSI,RCC_ON);
    RCC_SETSYSCLK(SW_HSI);  //  Switch system clock to PLL
    SystemCoreClockUpdate();   // Update core clock variable
 	SysTick_Init(ProcessorAHB); // Initialize SysTick with new frequency

	    RCC_AHB1_enable(GPIOAEN);   // Enable GPIOA
	    RCC_AHB1_enable(GPIOCEN);   // Enable GPIOC



	    RCC_APB2_enable(SYSCFGEN);   //System Configuration Controller   ---EXTI13 and PC13 are binding correctly.

	    ENABLE_interrupt(USART3);
	    SET_PendingFlag(USART3);

	    ENABLE_interrupt(EXTI15_10);


 NVIC_ConfigurePriorityGrouping(4);
 SetInterruptPriority(USART3, 5);
 SetInterruptPriority(EXTI15_10, 0);

 SYSCFG_EXTILineConfig(PORTC, PIN13);
 EXTI_ConfigLine(PIN13,BOTH_EDGES);


pin_configer_t PINA5_LED={
.port=PORTA,
.pinNum=5,
.mode=OUTPUT,
.speed=LOW,
.outputtype=PUSH_PULL,
.pulltype=NOPULL
};

GPIO_u8pininit(&PINA5_LED);




pin_configer_t PINC13_BUTTON={
.port=PORTC,
.pinNum=13,
.mode=INPUT,
.pulltype=PULLUP
};

GPIO_u8pininit(&PINC13_BUTTON);




}

void USART3_IRQHandler(void)
{
    GPIO_u8setpinvalue(PORTA, PIN5, PIN_HIGH);  // نled on
}



void EXTI15_10_IRQHandler(void)
{
	pinval_t button_value;
    if (EXTI->PR & (1 << 13))  // Check if from line 13
    {
        EXTI->PR |= (1 << 13);  // Clear pending flag
        GPIO_u8readpinvalue(PORTC, PIN13,&button_value);
        if ( button_value == 0) // pressed button
        {
            GPIO_u8setpinvalue(PORTA, PIN5, PIN_LOW);  // off led
        }
        else // Raised button
        {
            SET_PendingFlag(USART3);  // Trigger USART3 interrupt to light the lamp
        }
    }
}


