/* Process for exti_PC13_init()
 *-> disable global interrupt
 *-> enable clock for GPIOC(AHB1ENR)
 *-> enable clock for sysconfig {APB22ENR}
 *-> PC13 as input (MODER)
 *-> use PC13 for EXTI13 (EXTICR[3])
 *-> unmask interrupt request for PC13
 *-> Enable falling edge trigger
 *-> enable interrupt [exti15_10] from NVIC
 *-> Enable global interrupt
 *
 */

#include "stm32f4xx.h"

void exti_PC13_init(void)
{
	/*disable global interrupt*/
	__disable_irq();

	/*enable clock for GPIOC(AHB1ENR)*/
	RCC->AHB1ENR |= (1U<<2);

	/* enable clock for sysconfig {APB22ENR}*/
	RCC->APB2ENR |= (1U<<14);

	/* PC13 as input (MODER)*/
	GPIOC->MODER &=~(1U<<27);
	GPIOC->MODER &=~(1U<<26);

	/*use PC13 for EXTI13 (EXTICR[3])*/
	SYSCFG->EXTICR[3] &=~(1U<<7);
	SYSCFG->EXTICR[3] &=~(1U<<6);
	SYSCFG->EXTICR[3] |=(1U<<5);
	SYSCFG->EXTICR[3] &=~(1U<<4);

	/*unmask interrupt request for PC13*/
	EXTI->IMR |=(1U<<13);

	/*Enable falling edge trigger*/
	EXTI->FTSR |=(1U<<13);

	/*enable interrupt [exti15_10] from NVIC*/
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	/* Enable global interrupt*/
	__enable_irq();
}
