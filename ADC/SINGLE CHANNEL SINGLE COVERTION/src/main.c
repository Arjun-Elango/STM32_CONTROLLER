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
	while(1)
	{
		/*start the conversion*/
		adc_start_conversion();
		adc_value=adc_read(); //read adc

		printf("ADC value =%ld\n\r",adc_value);
		for(int i=0 ;i<1000000;i++);
	}
}
