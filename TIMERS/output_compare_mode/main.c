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
	timer2_output_compare_init();
    while(1){


    }
}

