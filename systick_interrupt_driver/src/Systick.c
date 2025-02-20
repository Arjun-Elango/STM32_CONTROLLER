#include "stm32f4xx.h"

#define SYSTICK_LOAD_VALUE 8000000
#define ENABLE (1U<<0)
#define CLKSOURCE (1U<<2)
#define COUNTFLAG  (1U<<16)
#define SYSTICK_ONE_SECOND (8000000*1000)
#define  TICKINT (1U<<1)

void systickMs(int delay)
{
	/*load as per the 1ms (SYST_RVR)
	 * RVR - reload value register
	 * Load SVR register with a value dependent on required delay and processor clock*/
	SysTick->LOAD = SYSTICK_ONE_SECOND;

	/* clear CVR*/
	SysTick->VAL=0;

	// ENABLE SysTick
	SysTick->CTRL|=ENABLE;

	// ENABLE PROCESSOR CLOCK
	SysTick->CTRL|=CLKSOURCE;

	for(int i=0; i<delay;i++){
			/*CHECK COUTFLAG bit for terminal count */
		    while((SysTick->CTRL & COUNTFLAG)==0);
		}
		/*stop Systick*/
		SysTick->CTRL=0;



}

void systick_interrupt_init(void)
{
	/*load as per the 1ms (SYST_RVR)
	 * RVR - reload value register
	 * Load SVR register with a value dependent on required delay and processor clock*/
	SysTick->LOAD = SYSTICK_LOAD_VALUE;

	/* clear CVR*/
	SysTick->VAL=0;

	// ENABLE SysTick
	SysTick->CTRL|=ENABLE;

	// ENABLE PROCESSOR CLOCK
	SysTick->CTRL|=CLKSOURCE;

	/*enable SysTick Interrupt*/
	SysTick->CTRL |= TICKINT;

}
