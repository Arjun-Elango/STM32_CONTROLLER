#include "spi.h"
#include <stdint.h>

#define MULTIPLE_BYTE_EN (0x40)
#define READ_OPERSTION   (0x80)

#define DATA_FORMAT_R (0x31)
#define FOUR_G (0x01)
#define POWER_CTL_R (0x2D)
#define RESET (0x00)
#define MEASURE (0x04)

void adxl_read(uint8_t address, uint8_t *rxdata){
	/*set read operation*/
	address |= READ_OPERSTION;

	/*Enable Multiple byte*/
	address |= MULTIPLE_BYTE_EN;

	/*enable slave*/
	cs_enable();

	spi1_transmit(&address, 1);

	/*Read operation*/
	spi1_receive(rxdata, 6);

	/*Disable slave*/
	cs_disable();
}

void adxl_write(uint8_t address, uint8_t value)
{
	uint8_t data[2];
	/*enable multi-byte*/
	data[0] = address | MULTIPLE_BYTE_EN;

	/*place data*/
	data[1] = value;

	/*enable slave*/
	cs_enable();

	/*transmit address of register +data*/
	spi1_transmit(data, 2);

	/*disable slave */
	cs_disable();
}

void adxl_init(void){
	/*enable GPIO for SPI*/
	spi_gpio_init();

	/*configure SPI*/
	spi1_config();

	/*set data format to +-4g*/
	adxl_write(DATA_FORMAT_R, FOUR_G);

	/*reset power control register*/
	adxl_write(POWER_CTL_R, RESET);

	/*set adxl345 in measurement*/
	adxl_write(POWER_CTL_R, MEASURE);

}


