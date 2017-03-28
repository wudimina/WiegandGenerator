#include "MKL25Z4.h"
#include "arch_DMA.h"

void arch_DMA_init(enum eDMA_channel channel)
{
    DMA0->DMA[channel].SAR = 0;
    DMA0->DMA[channel].DAR = 0;
    DMA0->DMA[channel].DSR_BCR = 0;
    DMA0->DMA[channel].DCR = 0;
}

void arch_DMA_transfer(enum eDMA_channel channel, const void * dst, const void * src, size_t len)
{
    DMA0->DMA[channel].DCR |= (DMA_DCR_CS_MASK|DMA_DCR_DINC_MASK|DMA_DCR_SINC_MASK);
    DMA0->DMA[channel].SAR = src;
    DMA0->DMA[channel].DAR = dst;
    DMA0->DMA[channel].DSR_BCR |= (len&DMA_DSR_BCR_BCR_MASK);

    //start transfer
    DMA0->DMA[channel].DCR |= (DMA_DCR_START_MASK);
    while(DMA0->DMA[channel].DSR_BCR&DMA_DSR_BCR_DONE_MASK);
}
