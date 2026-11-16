#include "my_ism330dhcx.h"
#include <stdio.h>
void my_ism330_init(void){
	/*Enable SPI gpio*/
	spi_gpio_init();

	/*Config SPI*/
	spi1_config();

	cs_disable();

    //enable multi-byte read
	uint8_t ctrl3 = my_ism330_read_reg(CTRL3_C);
	 ctrl3 |= IF_INC;
	 my_ism330_write_reg(CTRL3_C, ctrl3);

	my_ism330_accel_init();


}

uint8_t my_ism330_read_reg(uint8_t reg){
	uint8_t value;


	//Set read operation
	reg |= ISM330_READ_OPERATION;

	//Assert chip select (active low)
	cs_enable();

	/*Send register address and read command*/
	spi1_transfer(reg);

	/*Generate 8 clock pulses and receive register data*/
	value = spi1_transfer(0x00);


	/*Wait until SPI transfer is complete*/
	while(SPI1->SR & SR_BSY);

	/*Deassert chip select*/
	cs_disable();

	return value;

}

void my_ism330_write_reg(uint8_t reg, uint8_t value){
	//Clear read bit for write operation
	reg &=~ (ISM330_READ_OPERATION);


	//Assert chip select (active low)
	cs_enable();

	/*Send register address (read bit cleared for write)*/
	spi1_transfer(reg);

	/*Send data*/
	spi1_transfer(value);

	/*Wait until SPI transfer is complete*/
	while(SPI1->SR & SR_BSY);


	/*Deassert chip select*/
	cs_disable();
}


void my_ism330_read_multi(uint8_t reg, uint8_t *buffer, uint8_t len){

	reg |= ISM330_READ_OPERATION;

    cs_enable();

    spi1_transfer(reg);
    for(uint8_t i = 0; i < len; i++){
    	buffer[i] = spi1_transfer(0x00);
    }

    while(SPI1->SR & SR_BSY);

    cs_disable();
}


void my_ism330_accel_init(void){
	uint8_t config = 0;

	config |= (XL_ODR_104_HZ|XL_FS_2G);

	my_ism330_write_reg(CTRL1_XL, config);

}

void my_ism330_get_accel(int16_t *ax, int16_t *ay, int16_t *az){
	uint8_t accel[6];

	my_ism330_read_multi(OUTX_L_A, accel, 6);

	*ax = (int16_t)((accel[1] << 8) | accel[0]);
	*ay =  (int16_t)((accel[3] << 8) | accel[2]);
	*az = (int16_t)((accel[5] << 8) | accel[4]);
}
