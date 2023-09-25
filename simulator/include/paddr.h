#ifndef __PADDR_H__
#define __PADDR_H__

#include <common.h>
uint32_t paddr_read(uint32_t addr, uint32_t len);
void paddr_write(uint32_t addr, uint32_t data, uint32_t len);

#endif

