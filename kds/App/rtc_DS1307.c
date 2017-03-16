
#include "rtc_DS1307.h"
#include "hal_i2c.h"

hal_i2c_config rtc_i2c;

void InitRTC(enum e_i2c_index i2c_index)
{
	rtc_i2c.index = i2c_index;
	rtc_i2c.addressing =  e_i2c_addressing_7bit;
	rtc_i2c.mode = e_i2c_mode_Master;
	hal_i2c_init(&rtc_i2c);
}

void GetDateTime(tDateTime* pdatetime)
{
	uint8_t temp_reg = DATE_TIME_REGISTER_ADDR;
	hal_i2c_write(&rtc_i2c, DS1307_ADDR, &temp_reg, REGISTER_ADRS_SIZE);
	hal_i2c_read(&rtc_i2c, DS1307_ADDR, (uint8_t*) pdatetime, DATE_TIME_SIZE);
}
	
void SetDateTime(tDateTime* pdatetime)
{
	uint8_t tempdata[REGISTER_ADRS_SIZE + DATE_TIME_SIZE];
	
	tempdata[0] = DATE_TIME_REGISTER_ADDR;
	memcpy(&tempdata[0], pdatetime, DATE_TIME_SIZE);
	hal_i2c_write(&rtc_i2c, DS1307_ADDR, tempdata, REGISTER_ADRS_SIZE + DATE_TIME_SIZE);
}

void WriteCTRLREG(tRTCControl* pctrl)
{
	uint8_t tempdata[REGISTER_ADRS_SIZE + REGISTER_SIZE];
	tempdata[0] = CTRL_REGISTER_ADDR;
	tempdata[1] = pctrl->ctrl_reg;
	
	hal_i2c_write(&rtc_i2c, DS1307_ADDR, tempdata, REGISTER_ADRS_SIZE + REGISTER_SIZE);
}

void ReadCTRLREG(tRTCControl* pctrl)
{
	uint8_t temp_reg = CTRL_REGISTER_ADDR;
	
	hal_i2c_write(&rtc_i2c, DS1307_ADDR, &temp_reg, REGISTER_ADRS_SIZE);
	hal_i2c_write(&rtc_i2c, DS1307_ADDR, &pctrl->ctrl_reg, REGISTER_SIZE);
}

void WriteRAM(uint8_t address, uint8_t*data, uint8_t length)
{
	uint8_t temp_reg = RAM_REGISTER_ADDRESS;
	
	if(address+length>NO_OF_RAM_REGISTER)
	{
		//error
		return;
	}
	
	hal_i2c_write(&rtc_i2c, DS1307_ADDR, &temp_reg, REGISTER_ADRS_SIZE);
	hal_i2c_write(&rtc_i2c, DS1307_ADDR, data, REGISTER_ADRS_SIZE + length);
}

void ReadRAM(uint8_t address, uint8_t*data, uint8_t length)
{
	uint8_t temp_reg = RAM_REGISTER_ADDRESS;

	if(address+length>NO_OF_RAM_REGISTER)
	{
		//error
		return;
	}
	
	hal_i2c_write(&rtc_i2c, DS1307_ADDR, &temp_reg, REGISTER_ADRS_SIZE);
	hal_i2c_read(&rtc_i2c, DS1307_ADDR, data, REGISTER_ADRS_SIZE + length);
}
