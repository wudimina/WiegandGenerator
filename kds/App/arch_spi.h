//arch_spi

#include "spi_config.h"

extern void arch_spi_init(struct hal_spi_config* types);
extern void arch_spi_writeread(struct hal_spi_config* types, uint8_t* write_data, uint8_t* read_data, uint8_t length);
extern void arch_spi_write(struct hal_spi_config* types, uint8_t* write_data, uint8_t length);
extern void arch_spi_read(struct hal_spi_config* types, uint8_t* read_data, uint8_t length);
