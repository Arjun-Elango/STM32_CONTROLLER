#include "stm32f4xx.h"
#include "usart.h"
#include "systick.h"
#include <stdio.h>

int main(void)
{
	usart_init();

	while(1)
	{
		printf("Start\n\r");
		systickMs(1000);  // Should delay exactly 1 second
		printf("End\n\r");
        systickMs(1000);
        printf("2 second is over!..\n\r");

	}

}


















