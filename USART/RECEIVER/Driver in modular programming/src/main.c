/*USART RECEIVE a data from user to read
 * the actual function written in "USART.C"
 * Created a header for calling the function
 * by using this type of method we can reduce the repeated code
 * for the same function for different operation
 *also for simple and structured Main.c file
 */
#include "stm32f4xx.h"
#include "usart.h"
#include <stdio.h>

int main(void){
	usart_init();
	int ch; // the receiving value to store in variable
	while(1)
	{
		ch = usart_read(); //reading the value
		usart_write(ch); // write the same value
        for(int i=0;i<100000;i++);

    }

}
