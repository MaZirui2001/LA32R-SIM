#ifndef __PADDR_H__
#define __PADDR_H__

#include <stdint.h>
uint32_t paddr_read(uint32_t addr, uint32_t len);
void paddr_write(uint32_t addr, uint32_t data, uint32_t len);
uint8_t* addr_convert(uint32_t addr);
bool in_pmem(uint32_t addr);

void host_write(uint8_t* p, uint32_t data, uint32_t len);
uint32_t host_read(uint8_t* p, uint32_t len);

void tlb_read(uint32_t idx);
void tlb_write(uint32_t idx);
void tlb_srch();
bool tlb_invalid(uint32_t op, uint32_t asid, uint32_t va);
uint64_t tlb_convert(uint32_t va, uint32_t mem_type);

#endif

