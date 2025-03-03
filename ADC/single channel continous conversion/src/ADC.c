#include "stm32f4xx.h"
#include <stdint.h>

#define GPIOAEN (1U<<0)
#define ADC1EN  (1U<<8)
#define ADON    (1U<<0)
#define SWSTART (1U<<30)
#define EOC (1U<<1)
#define CONT (1U<<1)

void adc_init(void){
	/*enable clock for GPIOA */
	RCC->AHB1ENR |=GPIOAEN;

	/*set PA1 as analog (MODER)*/
	GPIOA->MODER |=(1U<<3);
	GPIOA->MODER |=(1U<<2);

	/*enable clock for adc*/
	RCC->APB2ENR |= ADC1EN;

	/*set sequence - PA1 only (ADC1_IN1)*/
	ADC1->SQR3 &=~(1U<<4);
	ADC1->SQR3 &=~(1U<<3);
	ADC1->SQR3 &=~(1U<<2);
	ADC1->SQR3 &=~(1U<<1);
	ADC1->SQR3 |= (1U<<0);

	/*set conversion length to 1*/
	ADC1->SQR1 &=~(1U<<23);
	ADC1->SQR1 &=~(1U<<22);
	ADC1->SQR1 &=~(1U<<21);
	ADC1->SQR1 &=~(1U<<20);

	/*enable adc*/
	ADC1->CR2 |= ADON;

	/*enable continuous convertion*/
	ADC1->CR2 |=CONT;
}

void adc_start_conversion(void){
	/*start the conversion */
	ADC1->CR2 |= SWSTART;
}

uint32_t adc_read(void){
	/*wait for the conversion to end*/
	while((ADC1->SR & (EOC))==0);
	/*read and return DR*/
	return ADC1->DR;
}

