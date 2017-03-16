//hal_spi

#include "spi_config.h"

extern void hal_spi_init(struct hal_spi_config* types);
extern void hal_spi_writeread(struct hal_spi_config* types, uint8_t* write_data, uint8_t* read_data, uint8_t length);
extern void hal_spi_write(struct hal_spi_config* types, uint8_t* write_data, uint8_t length);
extern void hal_spi_read(struct hal_spi_config* types, uint8_t* read_data, uint8_t length);
