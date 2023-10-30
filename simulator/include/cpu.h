#ifndef __CPU_H__
#define __CPU_H__

#include <arch.h>
#include <stdint.h>
extern CPU_State cpu;
void reset();
void cpu_exec(uint64_t n);
#endif