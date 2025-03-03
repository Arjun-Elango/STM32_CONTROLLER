#include "i2c.h"
#include <stdint.h>

#define MULTIPLE_BYTE_EN (0x40)
#define READ_OPERSTION   (0x80)

#define DATA_FORMAT_R (0x31)
#define FOUR_G (0x01)
#define POWER_CTL_R (0x2D)
#define RESET (0x00)
#define MEASURE (0x04)
#define DEVICE_ADDR (0x53)
#define DEVID    (0x00)
char data;
extern uint8_t data_rec[6];

void adxl_read_address(uint8_t reg){
	i2c_byteRead(DEVICE_ADDR , reg, &data);
}

void adxl_read_values(uint8_t reg){
	i2c_burstRead(DEVICE_ADDR , reg, 6 , data_rec);
}

void adxl_write(uint8_t reg, char value)
{
	char data[1];
	data[0]= value;

	i2c_burstWrite(DEVICE_ADDR , reg, 1,data);
}

void adxl_init(void){
	i2c_config();

	/*read device ID*/
    adxl_read_address(DEVID);

	/*set data format to +-4g*/
	adxl_write(DATA_FORMAT_R, FOUR_G);

	/*reset power control register*/
	adxl_write(POWER_CTL_R, RESET);

	/*set adxl345 in measurement*/
	adxl_write(POWER_CTL_R, MEASURE);

}


