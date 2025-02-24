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
	/*init timer2 interrupt*/
	timer2_1hz_interrupt_init();

    RCC->AHB1ENR|=GPIOAEN;
    // SET PA5 AS OUTPUT
    GPIOA->MODER |= (1U<<10);
    GPIOA->MODER &=~(1U<<11);
    while(1){
    
    }
}

static void timer2_callback(void){
	/*Toggle user LED(PA5) */
	GPIOA->ODR ^=LED;
	/*PRINT A MESSAGE through UART*/
	printf("1 second has passed , This is from timer2 interrupt \r\n");
}

void TIM2_IRQHandler(void)
{
	/*clear the UIF bit */
	TIM2->SR &=~UIF;

	timer2_callback();
}

