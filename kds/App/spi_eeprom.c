//spi_eeprom.c

#include "spi_eeprom.h"

struct hal_spi_config eeprom_spi;

void eeprom_delay( uint32_t uiCount );

void eeprom_delay( uint32_t uiCount )
{
	uint32_t i,j;
	
	for( i=0;i<uiCount;i++ )
	{
		for(j=0;j<100;j++);
	}
}

void init_eeprom(void)
{
	eeprom_spi.index = E_SPI_INDEX_1;
	eeprom_spi.cphamode = E_SPI_CPHAMODE_0;
	eeprom_spi.cpolmode = E_SPI_CPOLMODE_0;
	eeprom_spi.mode = E_SPI_MODE_MASTER;
	eeprom_spi.sspin = E_SPI_SSPIN_DISABLE;
	hal_spi_init(&eeprom_spi);
	
	hal_GPIO_init(SPI_SSPIN_CONTROL);
	DEASSERT_SPI_SS(SPI_SSPIN_CONTROL);
}

uint8_t eeprom_read_status()
{	
	uint8_t tempdata;
	
	ASSERT_SPI_SS(SPI_SSPIN_CONTROL);
	hal_spi_write(&eeprom_spi,(uint8_t*) RDSR, 1); 
	hal_spi_read(&eeprom_spi, &tempdata, 1);
	DEASSERT_SPI_SS(SPI_SSPIN_CONTROL);
	
	return tempdata;
}

void read_eeprom(uint8_t* read_data, uint16_t eeprom_address)
{
	uint8_t readsequence[3];
	
	readsequence[0]=READ;
	readsequence[1]=eeprom_address>>8;
	readsequence[2]=eeprom_address;
	
	ASSERT_SPI_SS(SPI_SSPIN_CONTROL);
	hal_spi_write(&eeprom_spi, readsequence, 3); 
	hal_spi_read(&eeprom_spi, read_data, 1);
	eeprom_delay(400);
	DEASSERT_SPI_SS(SPI_SSPIN_CONTROL);
}

void write_eeprom(uint8_t* write_data, uint32_t eeprom_address)
{
	uint8_t writesequence[3];
	uint8_t tempwrendata;
	tempwrendata = WREN;
	
	writesequence[0]=WRITE;
	writesequence[1]=eeprom_address>>8;
	writesequence[2]=eeprom_address;
	
	ASSERT_SPI_SS(SPI_SSPIN_CONTROL);	
	hal_spi_write(&eeprom_spi, &tempwrendata, 1); 
	eeprom_delay(400);
	DEASSERT_SPI_SS(SPI_SSPIN_CONTROL);
	
	//wait
	
	ASSERT_SPI_SS(SPI_SSPIN_CONTROL);	
	hal_spi_write(&eeprom_spi, writesequence, 3);
	hal_spi_write(&eeprom_spi, write_data, 1);
	eeprom_delay(400);
	DEASSERT_SPI_SS(SPI_SSPIN_CONTROL);
	//while(eeprom_read_status()&STATUS_RDY_BIT);
}
