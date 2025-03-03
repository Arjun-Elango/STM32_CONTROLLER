#include "stm32f4xx.h"
#include "usart.h"
#include "i2c.h"
#include "adxl.h"
#include <stdio.h>
#include <stdint.h>

#define DATA_START_ADDR (0x32)

int16_t x,y,z;

uint8_t data_rec[6];

int main (void){
	/*USART init*/
	usart_init();

	/*initialize adxl*/
	adxl_init();
	printf("PB8 state: %d\n", (GPIOB->IDR & (1 << 8)) ? 1 : 0);

	while(1)
	{
		adxl_read_values(DATA_START_ADDR);
		x = ((data_rec[1]<<8) | (data_rec[0]));
		y = ((data_rec[3]<<8) | (data_rec[2]));
		z = ((data_rec[5]<<8) | (data_rec[4]));

		printf("X = %d\r\n",(int)x);
		printf("Y = %d\r\n",(int)y);
		printf("Z = %d\r\n",(int)z);
	}
}
