/*USART receiver driver
 * based on the received value a led is turn on /off At PA5
 * the actual function written in "USART.C"
 * Created a header for calling the function
 * by using this type of method we can reduce the repeated code
 * for the same function for different operation
 *also for simple and structured Main.c file
 */
#include "stm32f4xx.h"
#include "usart.h"
#include <stdio.h>
#define LED     (1U<<5)
int main(void){
	usart_init();
	// clock for port A
	RCC->AHB1ENR |= (1U<<0);
	// set PA5 as output using MODER
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	int ch; // the receiving value
	while(1)
	{
		ch = usart_read(); //reading the value
		usart_write(ch); // write the same value
		if(ch == 'H'){
			GPIOA->ODR |= LED ;
		}if(ch == 'L'){
			GPIOA->ODR &=~ LED;
		}
        for(int i=0;i<100000;i++);

    }

}
