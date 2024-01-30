#ifndef __DECODE_H__
#define __DECODE_H__

#include <stdint.h>
#include <iostream>
std::pair<uint32_t, uint32_t> inst_fetch(uint32_t pc);
void decode_exec(uint32_t inst, uint32_t exception_fetch);
void cpu_exec(uint64_t n);
#endif
