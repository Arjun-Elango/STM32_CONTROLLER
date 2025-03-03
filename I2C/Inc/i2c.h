/*
 * i2c.h
 *
 *  Created on: Mar 2, 2025
 *      Author: PY-DOM
 */

#ifndef I2C_H_
#define I2C_H_

void i2c_gpio_init(void);
void i2c_config(void);
void i2c_byteRead(char saddr , char maddr, char *data);
void i2c_burstRead(char saddr , char maddr, int n , char *data);
void i2c_burstWrite(char saddr , char maddr, int n , char *data);

#endif /* I2C_H_ */
