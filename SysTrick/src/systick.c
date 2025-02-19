#include "stm32f4xx.h"

#define SYSTICK_LOAD_VALUE 16000
#define ENABLE (1U<<0)
#define CLKSOURCE (1U<<2)
#define COUNTFLAG  (1U<<16)

void systickMs(int delay)
{
	/*load as per the 1ms (SYST_RVR)
	 * RVR - reload value register
	 * Load SVR register with a value dependent on required delay and processor clock*/
	SysTick->LOAD = SYSTICK_LOAD_VALUE;
	
	/* clear CVR*/
	SysTick->VAL = 0;
	
	// ENABLE SysTick
	SysTick->CTRL |= ENABLE;
	
	// ENABLE PROCESSOR CLOCK
	SysTick->CTRL |= CLKSOURCE; 
	for(int i=0; i<delay;i++){
	/*CHECK COUTFLAG bit for terminal count */
	while((SysTick->CTRL & COUNTFLAG)==0);
	}
	/*stop Systick*/
	SysTick->CTRL =0;

}
