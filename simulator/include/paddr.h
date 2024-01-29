#ifndef __PADDR_H__
#define __PADDR_H__

#include <stdint.h>
uint32_t paddr_read(uint32_t addr, uint32_t len);
void paddr_write(uint32_t addr, uint32_t data, uint32_t len);
uint8_t* addr_convert(uint32_t addr);
bool in_pmem(uint32_t addr);

void host_write(uint8_t* p, uint32_t data, uint32_t len);
uint32_t host_read(uint8_t* p, uint32_t len);

std::pair<uint32_t, uint32_t> vaddr_check(uint32_t vaddr, uint32_t align_mask, uint32_t mem_type);

#endif

