
#include "hal_i2c.h"
#include "arch_i2c.h"

void hal_i2c_init(hal_i2c_config *conf)
{
	arch_i2c_init(conf);
}

void hal_i2c_write(hal_i2c_config *conf, uint32_t address, uint8_t *data, uint8_t length)
{
	arch_i2c_write(conf, address, data, length);
}

void hal_i2c_read(hal_i2c_config *conf, uint32_t address, uint8_t *data, uint8_t length)
{
	arch_i2c_read(conf, address, data, length);
}
