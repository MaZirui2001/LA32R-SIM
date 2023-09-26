#include <common.h>
#include <paddr.h>
#include <cpu.h>
#include <decode.h>
#include <disasm.h>

void reset(){
    cpu.state = SIM_STOP;
    cpu.pc = RESET_VECTOR;
}

void cpu_exec(uint64_t n){
    char buf[100];
    switch(cpu.state){
        case SIM_ABORT: case SIM_END:
        std::cout << "Program execution has ended." << std::endl;
        return;
        default: cpu.state = SIM_RUNNING;
    }
    while(n--){
        uint32_t inst = inst_fetch(cpu.pc);
        std::cout << "pc = " << std::hex << cpu.pc << '\t';
        disasm(buf, inst);
        std::cout << buf << std::endl;
        decode_exec(inst);
        if(cpu.state != SIM_RUNNING) break;
        if(inst == 0x002a0000) break;

    }
    switch(cpu.state){
        case SIM_END: 
        Log("simulation %s at pc = " FMT_WORD, (cpu.reg[4] == 0 ? INLINE_FMT("HIT GOOD TRAP", ANSI_FG_GREEN) : 
            INLINE_FMT("HIT BAD TRAP", ANSI_FG_RED)), cpu.halt_pc); break;
        case SIM_ABORT:
        break;
    }

}