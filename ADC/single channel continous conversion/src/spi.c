#include "stm32f4xx.h"
#include <stdint.h>

#define GPIOAEN (1U<<0)
#define SPI1EN (1U<<12)


void spi1_receive(uint8_t *data , uint32_t size)
{
	while(size){
		/*send dummy data*/
		SPI1->DR =0;

		/*wait for the receiver not empty*/
		while((SPI1->SR&(1U<<0))==0); //RXNE

		/*read the data*/
		*data++ = SPI1->DR;

		size--;
	}
}

void cs_enable(void){
	/*enable slave*/
	GPIOA->ODR &=~(1U<<9);
}

void cs_disable(void){
	/*disable slave*/
	GPIOA->ODR |=(1U<<9);
}

void spi1_transmit(uint8_t *data, uint32_t size)
{
	uint32_t i = 0;
	uint8_t temp;

	while(i<size){
		/*wait for transmit buffer to be empty*/
		while((SPI1->SR &(1U<<1))==0);
		/*TRANSMIT DATA*/
		SPI1->DR = data[i];
		i++;
		}
	/*wait for transmit buffer to be empty*/
	while((SPI1->SR &(1U<<1))==0);

	/*wait for bus NOT busy*/
	while((SPI1->SR )& ((1U<<7)!=0));

	/*clear overrun flag*/
	temp = SPI1->DR;
	temp = SPI1->SR;
}
void spi1_config(void){
	/*enable clock for spi1*/
	RCC->APB2ENR |= SPI1EN;

	//set BAUD RATE
	SPI1->CR1 &=~(1U<<5);
	SPI1->CR1 &=~(1U<<4);
	SPI1->CR1 |=(1U<<3);

	/*set bus mode to mode3*/
	SPI1->CR1 |= (1U<<0); //CPOL
	SPI1->CR1 |= (1U<<1); //CPHA

	/*enable full duplex mode*/
	SPI1->CR1 &=~(1U<<10);

	/*MSB first*/
	SPI1->CR1 &=~(1U<<7);

	// SET AS MASTER
	SPI1->CR1 |= (1U<<2);

	/*8 Bit data frame*/
	SPI1->CR1 &=~(1U<<11);

	/*enable software slave management*/
	SPI1->CR1 |=(1U<<9);
	SPI1->CR1 |= (1U<<8);

	// Enable SPI1
	SPI1->CR1 |= (1U<<6);
}


void spi_gpio_init(void)
{
	/*Enable GPIOA Clock*/
	RCC->AHB1ENR |= GPIOAEN;
	/*PA5*/
	GPIOA->MODER |=(1U<<11);
	GPIOA->MODER &=~(1U<<10);

	/*PA6*/
	GPIOA->MODER |=(1U<<13);
	GPIOA->MODER &=~(1U<<12);
	/*PA7*/
	GPIOA->MODER |=(1U<<15);
	GPIOA->MODER &=~(1U<<14);
	/*PA9 -> output*/
	GPIOA->MODER |=(1U<<18);
	GPIOA->MODER &=~(1U<<19);

	/*PA5, PA6 and PA7 in AF05*/
	/*PA5*/
	GPIOA->AFR[0] &=~(1U<<23);
	GPIOA->AFR[0] |=(1U<<22);
	GPIOA->AFR[0] &=~(1U<<21);
	GPIOA->AFR[0] |=(1U<<20);

	/*PA6*/
	GPIOA->AFR[0] &=~(1U<<27);
	GPIOA->AFR[0] |=(1U<<26);
	GPIOA->AFR[0] &=~(1U<<25);
	GPIOA->AFR[0] |=(1U<<24);

	/*PA7*/
	GPIOA->AFR[0] &=~(1U<<31);
	GPIOA->AFR[0] |=(1U<<30);
	GPIOA->AFR[0] &=~(1U<<29);
	GPIOA->AFR[0] |=(1U<<28);

}
