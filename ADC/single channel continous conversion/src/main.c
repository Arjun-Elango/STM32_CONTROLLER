#include "stm32f4xx.h"
#include "usart.h"
#include "adc.h"
#include <stdio.h>
#include <stdint.h>

uint32_t adc_value;

int main (void){
	/*USART init*/
	usart_init();

	/*initialize adc*/
	adc_init();
	/*start the conversion*/
	adc_start_conversion();
	while(1)
	{
		adc_value=adc_read(); //read adc

		printf("ADC value =%ld\n\r",adc_value);
	}
}
