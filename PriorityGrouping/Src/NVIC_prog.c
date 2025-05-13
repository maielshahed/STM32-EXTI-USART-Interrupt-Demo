/*
 * NVIC_prog.c
 *
 *  Created on: Apr 19, 2025
 *      Author: Mai El Shahed
 */


#include <stdint.h>
#include <stddef.h>

#include "NVIC_interface.h"
#include "Stm32F446xx.h"
#include "errtype.h"



uint8_t ENABLE_interrupt(uint8_t IRQNUM){
	uint8_t local_u8errorstate=OK;

	uint8_t RegNum=IRQNUM/32;
	uint8_t BitNum=IRQNUM%32;

	if( IRQNUM < 96 ){
		NVIC->ISER[RegNum]=(1<<BitNum);
	}else{
		 local_u8errorstate= NOK;
	}

	return local_u8errorstate;

}


uint8_t DISABLED_interrupt(uint8_t IRQNUM){
	uint8_t local_u8errorstate=OK;

	uint8_t RegNum=IRQNUM/32;
	uint8_t BitNum=IRQNUM%32;

	if(IRQNUM < 96){
		NVIC->ICER[RegNum]=(1<<BitNum);
	}else{
		 local_u8errorstate= NOK;
	}

	return local_u8errorstate;

}


uint8_t SET_PendingFlag(uint8_t IRQNUM){

	uint8_t local_u8errorstate=OK;

		uint8_t RegNum=IRQNUM/32;
		uint8_t BitNum=IRQNUM%32;

		if(IRQNUM < 96){
			NVIC->ISPR[RegNum]=(1<<BitNum);
		}else{
			 local_u8errorstate= NOK;
		}

		return local_u8errorstate;
}


uint8_t Clear_PendingFlag(uint8_t IRQNUM){

	uint8_t local_u8errorstate=OK;

		uint8_t RegNum=IRQNUM/32;
		uint8_t BitNum=IRQNUM%32;

		if(IRQNUM < 96){
			NVIC->ICPR[RegNum]=(1<<BitNum);
		}else{
			 local_u8errorstate= NOK;
		}

		return local_u8errorstate;
}



uint8_t Active_PendingFlag(uint8_t IRQNUM){

	uint8_t local_u8errorstate=OK;

		uint8_t RegNum=IRQNUM/32;
		uint8_t BitNum=IRQNUM%32;

		if(IRQNUM < 96){
	        local_u8errorstate = (NVIC->IABR[RegNum] >> BitNum) & 1;
		}else{
			 local_u8errorstate= NOK;
		}

		return local_u8errorstate;
}


void SetInterruptPriority(uint8_t IRQNUM, uint32_t priority)
{
    if (IRQNUM >= 0) // Only for external interrupts, not for faults
    {
        NVIC->IPR[IRQNUM] = (priority << 4);
    }
}



void NVIC_ConfigurePriorityGrouping(uint8_t priorityGroup)
{
    if (priorityGroup > 7U) priorityGroup = 7U;

    SCB-> AIRCR = (0x5FAU << SCB_AIRCR_VECTKEY_Pos) | (priorityGroup << SCB_AIRCR_PRIGROUP_Pos);
}


void SYSCFG_EXTILineConfig(port_t port,pin_t pin)

{
    uint8_t regIndex = pin / 4;
    uint8_t position = (pin % 4) * 4;

    // Clear the old 4 bits
    SYSCFG->EXTICR[regIndex] &= ~(0xF << position);

    // Put the port number in the correct place
    SYSCFG->EXTICR[regIndex] |= (port << position);
}

void EXTI_ConfigLine(pin_t pin, uint8_t edge_type)
{
	//Enable interrupt for the specified EXTI line

	     EXTI->IMR |= (1 << pin);  // Interrupt mask

	// We choose the type of edge
	if (edge_type == FALLING_EDGE) {
        EXTI->FTSR |= (1 << pin);   // Falling edge
        EXTI->RTSR &= ~(1 << pin);  // Disable rising
    }
    else if (edge_type == RISING_EDGE) {
        EXTI->RTSR |= (1 << pin);   // Rising edge
        EXTI->FTSR &= ~(1 << pin);  // Disable falling
    }
    else if (edge_type == BOTH_EDGES) {
        EXTI->RTSR |= (1 << pin);   // Enable both
        EXTI->FTSR |= (1 << pin);
    }
}
