/*
 * usart.h
 *
 *  Created on: Feb 16, 2025
 *      Author: PY-DOM
 */

#ifndef USART_H_
#define USART_H_

void usart_init(void);
void usart_write(int ch);
int usart_read(void);

#endif /* USART_H_ */
