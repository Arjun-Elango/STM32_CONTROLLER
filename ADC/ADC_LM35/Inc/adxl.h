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
void adxl_read(uint8_t addresss, uint8_t *rxdata);
void adxl_write(uint8_t address, uint8_t value);


#endif /* ADXL_H_ */
