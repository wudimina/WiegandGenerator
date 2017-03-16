//arch_spi

#include "arch_spi.h"
#include "MKL25Z4.h"

void arch_spi_init(struct hal_spi_config* types)
{
	uint8_t temp_c1_reg;
	
	if(types->index > 2)
	{
		//error
		return;
	}
	
	
	PORTA_PCR6 = PORT_PCR_MUX(3); //MISO Pin
	PORTA_PCR7 = PORT_PCR_MUX(3); //MOSI Pin
	PORTB_PCR0 = PORT_PCR_MUX(3); //SCK Pin
	
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;	
	
	temp_c1_reg = SPI_C1_MSTR_MASK | SPI_C1_SSOE_MASK;	
	
	if(types->cpolmode == E_SPI_CPOLMODE_1)
	{
		temp_c1_reg |= SPI_C1_CPOL_MASK;
	}
	
	if(types->cphamode == E_SPI_CPHAMODE_1)
	{
		temp_c1_reg |= SPI_C1_CPHA_MASK;	
	}
	SPI0_C1 = temp_c1_reg;
	
	if(types->sspin == E_SPI_SSPIN_ENABLE)
	{
		PORTA_PCR5 = PORT_PCR_MUX(3); //SS Pin
		SPI0_C2 = SPI_C2_MODFEN_MASK;
	}
	else if(types->sspin ==E_SPI_SSPIN_DISABLE)
	{
		SPI0_C2 = 0;
	}
	SPI0_BR = 0x78;	
	SPI0_C1 |= SPI_C1_SPE_MASK;
}

void arch_spi_writeread(struct hal_spi_config* types, uint8_t* write_data, uint8_t* read_data, uint8_t length)
{
	uint8_t i;
	
	for(i=0;i<length;i++)
	{
		while ((SPI0_S & SPI_S_SPTEF_MASK) == 0);
		SPI0_D = *write_data;
		while ((SPI0_S & SPI_S_SPRF_MASK) == 0);
		*read_data = SPI0_D;
		write_data++;
		read_data++;
	}
}

void arch_spi_write(struct hal_spi_config* types, uint8_t* write_data, uint8_t length)
{
	uint8_t i;
	
	for(i=0;i<length;i++)
	{
		while ((SPI0_S & SPI_S_SPTEF_MASK) == 0);
		SPI0_D = *write_data;
		write_data++;
	}
}

void arch_spi_read(struct hal_spi_config* types, uint8_t* read_data, uint8_t length)
{
	uint8_t i;
	
	if(SPI0_S & SPI_S_SPRF_MASK)
		i = SPI0_D;	//clear buffer
	
	for(i=0;i<length;i++)
	{
		while ((SPI0_S & SPI_S_SPTEF_MASK) == 0);
		SPI0_D = 0xff;	//send dummy
		while ((SPI0_S & SPI_S_SPRF_MASK) == 0);
		*read_data = SPI0_D;
		read_data++;
	}
}
