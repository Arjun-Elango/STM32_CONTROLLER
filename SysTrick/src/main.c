#include "stm32f4xx.h"
#include "usart.h"
#include "systick.h"
#include <stdio.h>

int main(void)
{
	usart_init();

	while(1)
	{
		systickMs(1000);
        printf("1 second is over");
	}

}



















