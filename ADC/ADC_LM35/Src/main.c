#include "stm32f4xx.h"
#include "usart.h"
#include "adc.h"
#include <stdio.h>
#include <stdint.h>

uint32_t adc_value;
#define STEP_SIZE 3.3/4096

int main (void){
	/*USART init*/
	usart_init();

	/*initialize adc*/
	adc_init();
	/*start the conversion*/

	while(1)
	{
		adc_start_conversion();
		adc_value=adc_read(); //read adc
		double mV_temp = adc_value*STEP_SIZE*1000;
		double tempC = mV_temp/10;
		printf("adc value %ld\r\n" , adc_value);
		printf("temperature in C %d\r\n" ,(int)tempC);
		printf("***********************\r\n");
		for(int i=0;i<1000000;i++);

	}
}
