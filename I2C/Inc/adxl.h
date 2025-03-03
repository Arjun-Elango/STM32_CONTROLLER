/*
 * adxl.h
 *
 *  Created on: Mar 1, 2025
 *      Author: PY-DOM
 */

#ifndef ADXL_H_
#define ADXL_H_
#include <stdint.h>
void adxl_init(void);
void adxl_read_address(uint8_t reg);
void adxl_read_values(uint8_t reg);
void adxl_write(uint8_t reg, char value);


#endif /* ADXL_H_ */
