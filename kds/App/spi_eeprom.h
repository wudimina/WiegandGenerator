//spi_eeprom.h

#include "hal_spi.h"
#include "hal_GPIO.h"

#define WREN  6
#define WRDI  4
#define RDSR  5
#define WRSR  1
#define READ  3
#define WRITE 2

#define STATUS_WPEN_BIT	0x80
#define STATUS_BP1_BIT	0x08
#define STATUS_BP0_BIT	0x04
#define STATUS_WEL_BIT	0x02
#define STATUS_RDY_BIT	0x01

#define SPI_SSPIN_CONTROL eGPIOPORTA5

#define ASSERT_SPI_SS(x)	hal_GPIO_control(x,eGPIOControlOFF);
#define DEASSERT_SPI_SS(x)	hal_GPIO_control(x,eGPIOControlON);

extern void init_eeprom(void);
extern void read_eeprom(uint8_t* read_data, uint16_t eeprom_address);
extern void write_eeprom(uint8_t* write_data, uint32_t eeprom_address);


