/*SysTick interrupt Driver*/

#include "stm32f4xx.h"

#include "systick.h"
#include <stdio.h>

#define GPIOAEN (1U<<0)
#define LED (1U<<5)

int main(void)
{
	//CLOCK
	RCC->AHB1ENR |= GPIOAEN;
	//SET DIRECTION AS output
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	//init Systick interrupt
	systick_interrupt_init();
	while(1)
	{


	}

}

static void systick_callback(void){
	GPIOA->ODR^=LED;
}

void SysTick_Handler(void){
	/*do something*/

	systick_callback();
}

















