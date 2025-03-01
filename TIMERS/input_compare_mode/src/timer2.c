/*process for 1hz init function
 * Enable clock to timer2 (APB1ENR)
 * set Prescalar value (PSC)
 * set automatic reload register(ARR)
 * clear counter register(CNT)
 * Enable timer(CR1)
 * process for interrupt init function
 * Enable timer 2 interrupt(DIER)
 * Enable timer2 interrupt from NVIC [NVIC_EnableIRQ(TIM2IRQn)]
 * process : timer output compare mode init
 * Enable clock to GPIOA  AHB1ENR
 * Set PA5 to alternate function (MODER)
 * set PA5 to Alternate function TMR2_CH1(AFR[0])
 *TIMER OUTPUT MODE
 * Enable clock acess to timer2 (APB1ENR)
 * SET counter clock frequency (PSC)
 * set Auto RELOAD value for required delay (ARR)
 * ser output compare to toggle mode(CCMR1)
 * put timer2 to compare mode(CCER)
 * Clear Timer counter(CNT)
 * enable timer (CR1)
 * */
#include "stm32f4xx.h"
#define TIMER2EN         (1U<<0)
#define TIM3EN           (1U<<1)
#define PSC_VALUE_10KHZ  (800000-1)
#define ARR_VALUE_1HZ    (1000-1)
#define CEN              (1U<<0)
#define GPIOAEN          (1U<<0)
#define UIE              (1U<<0)
#define ARR_VALUE_2HZ    (5000-1)
#define CC1E             (1U<<0)

void timer3_input_compare_init(void){
	/*enable clock to GPIOA (AHB1ENR)*/
	RCC->AHB1ENR |= GPIOAEN;
	/*set PA6 to alternate function[AF02] (MODER)*/
	GPIOA->MODER |=(1U<<13); //1
	GPIOA->MODER &=~(1U<<12);//0
	/*set alternate function AF02 AFR[0] as timer3*/
	GPIOA->AFR[0]|=(1U<<25);
	GPIOA->AFR[0]&=~(1U<<24);
	GPIOA->AFR[0]&=~(1U<<26);
	GPIOA->AFR[0]&=~(1U<<27);
	/*enable clock access for timer3 */
	RCC->APB1ENR |= TIM3EN;
	/*set prescalar register for 10khz count*/
	TIM3->PSC =PSC_VALUE_10KHZ;
	/*CCMR TO SET TIM3 as input*/
	TIM3->CCMR1 &=~(1U<<1);
	TIM3->CCMR1 |= (1U<<0);
	/*Enable capture by CCER for TIm3 at channel3 if bit 0 is 1 it is enabled */
	TIM3->CCER |= CC1E;
	/*ENABLE TIMER3*/
	TIM3->CR1 |= CEN;
}

void timer2_output_compare_init(void){
	/*enable clock for GPIOA */
	RCC->AHB1ENR |= GPIOAEN;
	//set PA5 in alternate function mode
	GPIOA->MODER |=(1U<<11); //1
	GPIOA->MODER &=~(1U<<10);//0
	/*refering Alternate function mapping table
	table 9 COLUMN AF01 FOR TIMER here row number 6 FOR PA5
	connect to TMR2_CH1
	so set 20bit->1 , 21,22,23->0 for AF01*/
	GPIOA->AFR[0]|=(1U<<20);
	GPIOA->AFR[0]&=~(1U<<21);
	GPIOA->AFR[0]&=~(1U<<20);
	GPIOA->AFR[0]&=~(1U<<20);

	/*enable clock access to timer2*/
	RCC->APB1ENR |=TIMER2EN;
	//set prescalar register for 10khz counter
	TIM2->PSC = PSC_VALUE_10KHZ;
    //SET ARR FOR 2HZ
	TIM2->ARR = ARR_VALUE_1HZ;

	/*put Timer in toggle mode*/
	TIM2->CCMR1 &=~(1U<<6);
	TIM2->CCMR1 |=(1U<<5);
	TIM2->CCMR1 |=(1U<<4);

	/*put Timer 2 in compare mode*/
	TIM2->CCER |= CC1E;

	/*clear counter CNT*/
	TIM2->CNT =0;
	/*enable timer CONTROL REGISTER 1 TO enable bit0 should 1*/
	TIM2->CR1 |=CEN;
}

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

