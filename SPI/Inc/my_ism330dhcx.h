#ifndef MY_ISM330DHCX_H_
#define MY_ISM330DHCX_H_

#include "spi.h"
#include <stdint.h>

#define ISM330_READ_OPERATION (0x80) //define the bit to specify a read operation

#define CTRL3_C	(0x12) //register address;
#define IF_INC	(1 << 2) // enable multi-byte read/write at register CTRL3_C

#define CTRL1_XL (0x10) //accelerometer control register
#define XL_ODR_104_HZ	(0x5 << 4) //104 Hz ODR
#define XL_FS_2G	(0x0 << 2)

#define OUTX_L_A	(0x28)
#define OUTX_H_A	(0x29)
#define OUTY_L_A	(0x2A)
#define OUTY_H_A	(0x2B)
#define OUTZ_L_A	(0x2C)
#define OUTZ_H_A	(0x2D)

void my_ism330_init(void);
uint8_t my_ism330_read_reg(uint8_t reg);
void my_ism330_write_reg(uint8_t reg, uint8_t value);
void my_ism330_read_multi(uint8_t reg, uint8_t *buffer, uint8_t len);

void my_ism330_accel_init(void);
void my_ism330_get_accel(int16_t *ax, int16_t *ay, int16_t *az);
#endif

