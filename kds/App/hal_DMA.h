#include "DMA_config.h"

extern void hal_DMA_init(enum eDMA_channel channel);
extern void hal_DMA_transfer(enum eDMA_channel channel, const void * dst, const void * src, size_t len);
