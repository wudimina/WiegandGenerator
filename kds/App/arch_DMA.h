#include "DMA_config.h"

#ifndef ARCH_DMA_HEADER

#define ARCH_DMA_HEADER

extern void arch_DMA_init(enum eDMA_channel channel);
extern void arch_DMA_transfer(enum eDMA_channel channel, const void * dst, const void * src, size_t len);

#endif

