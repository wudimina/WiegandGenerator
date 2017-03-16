
#include "stdint.h"

#ifndef _I2C_CONFIG_H
#define _I2C_CONFIG_H

enum e_i2c_index
{
	e_i2c_index1,
	e_i2c_index2,
};

enum e_i2c_addressing
{
	e_i2c_addressing_7bit,
	e_i2c_addressing_10bit,
};

enum e_i2c_mode
{
	e_i2c_mode_Master,
	e_i2c_mode_Slave,
};

typedef struct
{
	enum e_i2c_index index;
	enum e_i2c_addressing addressing;
	enum e_i2c_mode mode;
	uint32_t clockspeed_kHz; 
}hal_i2c_config;

#endif
