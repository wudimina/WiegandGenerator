
#include "i2c_config.h"

extern void arch_i2c_init(hal_i2c_config *conf);
extern void arch_i2c_write(hal_i2c_config *conf, uint32_t address, uint8_t *data, uint8_t length);
extern void arch_i2c_read(hal_i2c_config *conf, uint32_t address, uint8_t *data, uint8_t length);
