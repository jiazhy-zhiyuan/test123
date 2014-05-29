#ifndef __I2C_WRAPPER_20130411_H
#define __I2C_WRAPPER_20130411_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum I2C_BUS_NR
{
	I2C_BUS_1,
	I2C_BUS_2
}I2C_BUS_NR;

unsigned char read_i2c_byte8(I2C_BUS_NR bus, int chipaddr, int regaddr);
void write_i2c_byte8(I2C_BUS_NR bus, int chipaddr, int regaddr, unsigned char regvalue);

#ifdef __cplusplus
}
#endif

#endif

