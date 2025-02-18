/*USART Transmit a single character Using Modular code
 * the actual function written in "USART.C"
 * Created a header for calling the function
 * by using this type of method we can reduce the repeated code
 * for the same function for different operation
 *also for simple and structured Main.c file
 */
#include "stm32f4xx.h"
#include "usart.h"

int main(void){
	usart_init(); // calling the function Initialization
	// it get all the initial steps from Usart.c by Usart.h
    while(1){
    	usart_write('k');
    	for(int i=0;i<1000000;i++);
    }

}
