#include "hal_DMA.h"
#include "arch_DMA.h"

void hal_DMA_init(enum eDMA_channel channel)
{
    arch_DMA_init(channel);
}


void hal_DMA_transfer(enum eDMA_channel channel, const void * dst, const void * src, size_t len)
{
    arch_DMA_transfer(channel, dst, src, len);
}
