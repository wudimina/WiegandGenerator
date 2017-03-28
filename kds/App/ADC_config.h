#include <stdint.h>

#ifndef ADC_HEADER
#define ADC_HEADER

enum eADC_channel
{
	eADC_channel_tempsensor = 26,
};

enum eADC_mode
{
    eADC_mode_8_bitm,
    eADC_mode_12_bit,
    eADC_mode_10_bit,
    eADC_mode_16_bit,
};

enum eADC_clock
{
    eADC_clock_bus_clk,
    eADC_clock_bus_clk_div_2,
    eADC_clock_alt_clk,
    eADC_clock_asy_clk,
};

#endif
