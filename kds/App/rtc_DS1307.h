
//#include "common.h"
#include "hal_i2c.h"

#define DS1307_ADDR		0x68

#define DATE_TIME_REGISTER_ADDR	(0x00)

#define DATE_TIME_SIZE				(7)
#define REGISTER_SIZE				(1)
#define REGISTER_ADRS_SIZE			(1)

#define CTRL_REGISTER_ADDR		(0x07)

#define RAM_REGISTER_ADDRESS	(0x08)
#define NO_OF_RAM_REGISTER		(56)

#define RTC_CONTROL_OUT		(0x80)
#define RTC_CONTROL_SQWE	(0x10)
#define RTC_CONTROL_RS1		(0x02)
#define RTC_CONTROL_RS0		(0x01)

typedef struct
{
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t day;
	uint8_t date;
	uint8_t months;
	uint8_t year;
}tDateTime;

typedef struct
{
	uint8_t ctrl_reg;
}tRTCControl;

extern void InitRTC(enum e_i2c_index i2c_index);
extern void GetDateTime(tDateTime* pdatetime);
extern void SetDateTime(tDateTime* pdatetime);
extern void WriteCTRLREG(tRTCControl* pctrl);
extern void ReadCTRLREG(tRTCControl* pctrl);
extern void WriteRAM(uint8_t address, uint8_t*data, uint8_t length);
extern void ReadRAM(uint8_t address, uint8_t*data, uint8_t length);
