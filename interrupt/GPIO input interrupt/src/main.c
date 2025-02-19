/*input interrupt driver
 * generate an interrupt using the user button (PC13)
 * TOGGLE the user LED when the above interrupt occurs
 *-> set PA5 as output
 *-> check interrupt pending bit for PC13 (PR)
 *-> clear interrupt pending bit(PR)
 *-> call callback function
 *-> toggle LED
 *-> delay*/

#include "stm32f4xx.h"
#include "usart.h"
#include "exti.h"
#include <stdio.h>

#define PR13 (1U<<13)
#define LED  (1U<<5)

int main(void)
{
	usart_init();
	// call init function for the interrupt
	exti_PC13_init();

	RCC->AHB1ENR |= (1U<<0);//CLOCK
	/*set PA5 as output*/
	GPIOA->MODER |= (1U<<10); //1
	GPIOA->MODER &=~(1U<<11); //0 act as output

	while(1){

	}

}

static void exti_callback(void){
	GPIOA->ODR ^=LED;
	printf("INTERRUPT OCCURRED!..... \n\r");
	for(int i=0;i<100000;i++);
}

void EXTI15_10_IRQHandler(void)
{
	if((EXTI->PR & PR13)!=0)
	{
	  EXTI->PR |= PR13; //CLEARING PR13

	  /*do something*/
	  exti_callback();
	}
}


















