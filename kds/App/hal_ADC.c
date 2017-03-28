#include "hal_ADC.h"
#include "arch_ADC.h"

void hal_ADC_init()
{
    arch_ADC_init();
}

uint32_t hal_ADC_measure(enum eADC_channel ch)
{
    arch_ADC_measure(ch);
}

