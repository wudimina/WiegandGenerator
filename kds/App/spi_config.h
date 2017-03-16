//spi_config

#include "stdint.h"

#ifndef _HAL_SPI_DEF_H
#define _HAL_SPI_DEF_H

enum hal_spi_index
{
	E_SPI_INDEX_1,
};

enum hal_spi_cpolmode
{
	E_SPI_CPOLMODE_0,
	E_SPI_CPOLMODE_1
};

enum hal_spi_cphamode
{
	E_SPI_CPHAMODE_0,
	E_SPI_CPHAMODE_1
};

enum hal_spi_mode
{
	E_SPI_MODE_MASTER,
	E_SPI_MDOE_SLAVE
};

enum hal_spi_sspin
{
	E_SPI_SSPIN_ENABLE,
	E_SPI_SSPIN_DISABLE
};

struct hal_spi_config
{
	enum hal_spi_index		index;
	enum hal_spi_cpolmode	cpolmode;
	enum hal_spi_cphamode	cphamode;
	enum hal_spi_mode		mode;
	enum hal_spi_sspin		sspin;

};

#endif
