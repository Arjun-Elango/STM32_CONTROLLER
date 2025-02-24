/*setup LED and Wait for timer to overflow
 * Enable GPIOA (AHB1ENR)
 * set PA5 as Output (moder)
 * Check timer update flag (SR)
 * clear timer update flag (SR)
 * TOGGLE (ODR)
 * PRINT MESSAGE[USART]
 * */
#include "stm32f4xx.h"
#include "usart.h"
#include "Timer.h"
#include <stdio.h>

#define GPIOAEN (1U<<0)
#define LED     (1U<<5)

#define UIF     (1U<<0)

int main(void)
{
	/*init UART*/
	usart_init();
	/*init timer2*/
	timer2_1hz_init();
    RCC->AHB1ENR|=GPIOAEN;
    // SET PA5 AS OUTPUT
    GPIOA->MODER |= (1U<<10);
    GPIOA->MODER &=~(1U<<11);
    while(1){
    	 /*wait for timer overflow*/
    	while((TIM2->SR & UIF)==0);

    	/*Clear UIF*/
    	TIM2->SR &=~UIF;

    	/*Toggle user LED(PA5) */
    	GPIOA->ODR ^=LED;

    	/*PRINT A MESSAGE through UART*/
    	printf("1 second has passed..! \r\n");

    }
}







