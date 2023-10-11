#ifndef __CPU_H__
#define __CPU_H__

#include <common.h>
#include <VCPU.h>
#include "verilated_vcd_c.h"
extern CPU_State cpu;
extern VCPU *dut;
extern VerilatedVcdC *m_trace;
extern size_t sim_time;
void reset();
void cpu_exec(uint64_t n);
#endif