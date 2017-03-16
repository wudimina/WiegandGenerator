//hal_spi

#include "arch_spi.h"
#include "hal_spi.h"

void hal_spi_init(struct hal_spi_config* types)
{
	arch_spi_init(types);
}

void hal_spi_writeread(struct hal_spi_config* types, uint8_t* write_data, uint8_t* read_data, uint8_t length)
{
	arch_spi_writeread(types, write_data, read_data, length);
}

void hal_spi_write(struct hal_spi_config* types, uint8_t* write_data, uint8_t length)
{
	arch_spi_write(types, write_data, length);
}

void hal_spi_read(struct hal_spi_config* types, uint8_t* read_data, uint8_t length)
{
	arch_spi_read(types, read_data, length);
}
