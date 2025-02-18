 /*USAT RX is available at PA3 and it connect to AHB
 * SO AHB1ENR FOR CLOCK PLUSE Because it is connect to Port A
 * Set PA3 to alternate function(MODER)
 * Set PA3 as USART RX (AFR[0])
 * Enable Clock for USART2 using ABH1ENR
 * set Baud Rate (BRR)
 * Enable RECEIVER (CR1)
 * Enable USART2 (CR1)
 * WAIT TILL THE RECEIVER RECEIVE A BYTE(SR)
 * READ data byte (DR)*/
#include "stm32f4xx.h"
#define GPIOAEN (1U<<0)
#define USART2EN (1U<<17)

#define PERIPHCLK 16000000
#define BAUDRATE 115200

#define TE (1U<<3)
#define RE (1U<<2)
#define UE (1U<<13)
#define TXE (1U<<7) //it ensure the last bit data transfered
#define RXE (1U<<5) //it ensure the received data is ready to be read

void usart_init(void){
	/*Enable clock for PORT A*/
	RCC->AHB1ENR |= GPIOAEN;
	//Set PA2(USART_TX) to alternate function
	GPIOA->MODER &=~(1U<<4); // bit4 =0
	GPIOA->MODER |= (1U<<5); // bit5 =1
	//Set PA3(USART_RX) to alternate function
	GPIOA->MODER &=~(1U<<6); // bit6 =0
	GPIOA->MODER |= (1U<<7); // bit7 =1
	/*we need to set PA3 TO USART_RX Using AFR[0]
	 * which is AFRLy: Alternate function register low
	 * for port x bit y(y=0..7)
	 * IF need to configure more than bit 7 , we can use
	 * AFR[1] WHICH AFRHy for PORT x Bit y (y=8..15)
	 * reference to alternate function mapping we have USART_RX
	 * at column AF07 to set this Bit11 ->0 , Bit10,9,8->1
	 */
	// PA2 as USART_TXD
	GPIOA->AFR[0]&=~(1U<<11); //BIT11->0
	GPIOA->AFR[0]|= (1U<<10);
	GPIOA->AFR[0]|= (1U<<9);
	GPIOA->AFR[0]|= (1U<<8);
	//PA3 AS USART_RXD BIT15->0, BIT14,13,12->1
	GPIOA->AFR[0]&=~(1U<<15); //BIT15->0
	GPIOA->AFR[0]|= (1U<<14);
	GPIOA->AFR[0]|= (1U<<13);
	GPIOA->AFR[0]|= (1U<<12);
	// clock for USART2_TX
	RCC->APB1ENR |= USART2EN;
	/*Set baudrate*/
	USART2->BRR = (PERIPHCLK + (BAUDRATE/2))/BAUDRATE;
	//ENABLE Transmitter CR1 bit3->1
	USART2->CR1 = TE;
	//ENABLE Receiver CR1 bit3->1
	USART2->CR1 = RE;
	//enable USART CR1 bit13->1
	USART2->CR1 = UE;
}

void usart_write(int ch){
	// to wait until the last BYTE of data transfered
	while((USART2->SR & TXE)==0);
	// if '&' operation give 1 then it show the data is transfered
	/*send the data*/
	USART2->DR = (ch & 0xff);
}

int usart_read(void){
	// to wait until the bit5 of SR is 0-> data is not received
	while((USART2->SR & RXE)==0);
	/*receiver has a data byte , read to read*/
	return USART2->DR;
}

int __io_putchar(int ch){
	usart_write(ch);
	return ch;
}
