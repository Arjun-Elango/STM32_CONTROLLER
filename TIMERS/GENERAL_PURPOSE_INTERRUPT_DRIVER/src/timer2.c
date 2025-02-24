/*process for 1hz init function
 * Enable clock to timer2 (APB1ENR)
 * set Prescalar value (PSC)
 * set automatic reload register(ARR)
 * clear counter register(CNT)
 * Enable timer(CR1)
 * Enable timer 2 interrupt(DIER)
 * Enable timer2 interrupt from NVIC [NVIC_EnableIRQ(TIM2IRQn)]*/
#include "stm32f4xx.h"
#define TIMER2EN (1U<<0)
#define PSC_VALUE_10KHZ  (1600-1)
#define ARR_VALUE_1HZ (10000-1)
#define CEN  (1U<<0)

#define UIE  (1U<<0)

void timer2_1hz_interrupt_init(void){
	// enable clock
	RCC->APB1ENR |= TIMER2EN ;
	//set prescalar register for 10khz counter
	TIM2->PSC = PSC_VALUE_10KHZ;

	TIM2->ARR = ARR_VALUE_1HZ;

	/*clear counter Register*/
	TIM2->CNT =0;

	/*enable timer CONTROL REGISTER 1 TO enable bit0 should 1*/
	TIM2->CR1 |=CEN;

	// enable timer 2 interrupt
	TIM2->DIER |=UIE;

	//enable timer2 interrupt in NVIC
	NVIC_EnableIRQ(TIM2_IRQn);
}


void timer2_1hz_init(void){
	// enable clock
	RCC->APB1ENR |= TIMER2EN ;
	//set prescalar register for 10khz counter
	TIM2->PSC = PSC_VALUE_10KHZ;

	TIM2->ARR = ARR_VALUE_1HZ;

	/*clear counter Register*/
	TIM2->CNT =0;

	/*enable timer CONTROL REGISTER 1 TO enable bit0 should 1*/
	TIM2->CR1 |=CEN;
}

