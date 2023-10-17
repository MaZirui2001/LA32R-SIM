#include <common.h>
#include <command.h>
#include <cpu.h>
#include <monitor.h>
#include <device.h>
#include <statistic.h>
#include "verilated_vcd_c.h"
#include "VCPU.h"

CPU_State cpu;
VCPU *dut = new VCPU;
VerilatedVcdC *m_trace = new VerilatedVcdC;
size_t sim_time = 0;

int main(int argc, char* argv[]){
    init_monitor(argc, argv);

    Verilated::traceEverOn(true);
    dut->trace(m_trace, 5);
    m_trace->open("waveform.vcd");
    
    reset();
    command_mainloop();
    free_device();

    m_trace->close();

    return cpu.state == SIM_ABORT;
}