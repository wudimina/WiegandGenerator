#include "MKL25Z4.h"
#include "arch_ADC.h"

static void arch_ADC_calibrate()
{
    uint16_t cal_var;

    //calibrate here
    ADC0_BASE_PTR->SC3 |= (ADC_SC3_AVGE_MASK & ADC_SC3_AVGS_MASK);

    ADC0_BASE_PTR->SC3 |= (ADC_SC3_CAL_MASK);

    while(ADC0_BASE_PTR->SC1[0] & ADC_SC1_COCO_MASK);

    cal_var=0;
    cal_var += ADC0_BASE_PTR->CLP0;
    cal_var += ADC0_BASE_PTR->CLP1;
    cal_var += ADC0_BASE_PTR->CLP2;
    cal_var += ADC0_BASE_PTR->CLP3;
    cal_var += ADC0_BASE_PTR->CLP4;
    cal_var += ADC0_BASE_PTR->CLPS;
    cal_var = 0x8000U | (cal_var>>1U);

    ADC0_BASE_PTR->PG = cal_var;

    ADC0_BASE_PTR->SC3 &= ~(ADC_SC3_CAL_MASK);
}

void arch_ADC_init()
{
    SIM_SCGC6 |= (SIM_SCGC6_ADC0_MASK);
    ADC0_BASE_PTR->CFG1 = ((eADC_mode_16_bit<<ADC_CFG1_MODE_SHIFT)|(eADC_clock_asy_clk)|ADC_CFG1_ADLSMP_MASK);
    ADC0_BASE_PTR->CFG2 = (ADC_CFG2_ADACKEN_MASK);
    ADC0_BASE_PTR->SC2 = 0;
    ADC0_BASE_PTR->SC3 = 0;

    arch_ADC_calibrate();

}

uint32_t arch_ADC_measure(enum eADC_channel ch)
{
    ADC0_BASE_PTR->SC1[0] = (ch & ADC_SC1_ADCH_MASK);

    while(ADC0_BASE_PTR->SC1[0] & ADC_SC1_COCO_MASK);
    
    return ADC0_BASE_PTR->R[0];
}
