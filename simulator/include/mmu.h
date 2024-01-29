#ifndef __MMU_H__
#define __MMU_H__
#include <stdint.h>
void tlb_read(uint32_t idx);
void tlb_write(uint32_t idx);
void tlb_srch();
bool tlb_invalid(uint32_t op, uint32_t asid, uint32_t va);
uint64_t tlb_convert(uint32_t va, uint32_t mem_type);
uint64_t addr_translate(uint32_t vaddr, uint32_t mem_type);
#endif