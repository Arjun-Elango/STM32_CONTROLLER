/*
 * adc.h
 *
 *  Created on: Mar 2, 2025
 *      Author: PY-DOM
 */

#ifndef ADC_H_
#define ADC_H_

void adc_init(void);
void adc_start_conversion(void);
uint32_t adc_read(void);

#endif /* ADC_H_ */
