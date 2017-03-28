#include "ADC_config.h"

#ifndef ARCH_ADC_HEADER
#define ARCH_ADC_HEADER

extern void arch_ADC_init();
extern uint32_t arch_ADC_measure(enum eADC_channel ch);

#endif
