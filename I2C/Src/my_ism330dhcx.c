#include "my_ism330dhcx.h"
#include <stdio.h>



void my_ism330_init(void){
	/*Enable I2C gpio*/
	i2c1_init();


	/*Config accel to 104Hz 2G*/
	uint8_t config = 0;
	config |= (XL_ODR_104_HZ|XL_FS_2G);
	my_ism330_write_reg(CTRL1_XL, config);

}


uint8_t my_ism330_read_reg(uint8_t reg){
	uint8_t data;

	i2c1_byte_read(ISM330_DEVICE_ADDR ,reg, &data);

	return data;
}


void my_ism330_write_reg(uint8_t reg, uint8_t value){
	char data[1];
	data[0] = value;
	i2c1_burst_write(ISM330_DEVICE_ADDR, reg, 1, data);
}


void my_ism330_read_multi(uint8_t reg, uint8_t *buffer, uint8_t len){

	i2c1_burst_read(ISM330_DEVICE_ADDR, reg, len, (char *) buffer);
}

void my_ism330_get_accel(int16_t *ax, int16_t *ay, int16_t *az){
	uint8_t accel[6];

	my_ism330_read_multi(OUTX_L_A, accel, 6);

	*ax = (int16_t)((accel[1] << 8) | accel[0]);
	*ay =  (int16_t)((accel[3] << 8) | accel[2]);
	*az = (int16_t)((accel[5] << 8) | accel[4]);
}



