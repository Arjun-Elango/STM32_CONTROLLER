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
#include <stdint.h>

uint32_t old_timestamp, new_timestamp;
#define CC1F (1U<<1)


int main(void)
{
	/*TIMER2 output compare*/
	timer2_output_compare_init();
	/*TIMER3 input capture mode*/
	timer3_input_compare_init();
	/*USART INIT*/
	usart_init();
    while(1){
    	old_timestamp = new_timestamp;
    	while((TIM3->SR & CC1F)==0);
    	/*read CCR1*/
    	new_timestamp= TIM3->CCR1;
    	/*print new timestamp*/
    	printf("timestamp =%d",(int)new_timestamp);


    }
}

