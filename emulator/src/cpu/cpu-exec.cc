#include <common.h>
#include <paddr.h>
#include <cpu.h>
#include <disasm.h>
#include <device.h>

#ifdef ITRACE
typedef struct{
    uint32_t pc;
    uint32_t inst;
}inst_log_t;

#define ILOG_SIZE 16
static inst_log_t ilog[ILOG_SIZE];
static int ilog_idx = 0;
void print_ilog(){
    for(int i = 0; i < ILOG_SIZE; i++){
        std::cout << std::hex << std::setw(8) << std::setfill('0') << ilog[(ilog_idx+i)%ILOG_SIZE].pc << ": ";
        std::cout << std::hex << std::setw(8) << std::setfill('0') << ilog[(ilog_idx+i)%ILOG_SIZE].inst << '\t';
        char buf[100];
        disasm(buf, ilog[(ilog_idx+i)%ILOG_SIZE].inst);
        std::cout << buf << std::endl;
    }
}
void add_ilog(uint32_t pc, uint32_t inst){
    ilog[ilog_idx].pc = pc;
    ilog[ilog_idx].inst = inst;
    ilog_idx = (ilog_idx + 1) % ILOG_SIZE;
}
#endif

inline bool test_break(uint32_t inst){
    return inst == 0x002a0000;
}

uint32_t set_cpu_state(uint32_t pc, uint32_t rd, bool rd_valid, uint32_t rf_wdata){
    if(rd_valid){
        cpu.reg[rd] = rf_wdata;
    }
    cpu.pc = pc;
    return paddr_read(pc, 4);
}

bool commit_update(bool commit_en, uint32_t pc, uint32_t rd, bool rd_valid, uint32_t rf_wdata){
    if(commit_en){
        auto inst = set_cpu_state(pc, rd, rd_valid, rf_wdata);
        cpu.state = test_break(inst) ? SIM_END : cpu.state;
#ifdef ITRACE
        add_ilog(pc, inst);
#endif
        return true;
    }
    return false;
}
void single_cycle(){
    dut->clock = 0;
    dut->io_inst1_IF = paddr_read(dut->io_pc_IF, 4);
    dut->io_inst2_IF = paddr_read(dut->io_pc_IF + 4, 4);
    dut->io_inst3_IF = paddr_read(dut->io_pc_IF + 8, 4);
    dut->io_inst4_IF = paddr_read(dut->io_pc_IF + 12, 4);
    dut->eval();
    if(dut->io_mem_type_ex != 0){
        if(BITS(dut->io_mem_type_ex, 4, 4)){
            dut->io_mem_rdata_ex = paddr_read(uint32_t(dut->io_mem_addr_ex), 1 << ((dut->io_mem_type_ex) % 4));
        }
        else {
            paddr_write(uint32_t(dut->io_mem_addr_ex), dut->io_mem_wdata_ex, 1 << ((dut->io_mem_type_ex) % 4));
        }
    }
    m_trace->dump(sim_time++);
    dut->clock = 1;
    dut->eval();
    m_trace->dump(sim_time++);
}

void reset(){
    cpu.state = SIM_STOP;
    cpu.pc = RESET_VECTOR;
    dut->reset = 1;
    dut->clock = 0;
    dut->eval();
    dut->clock = 1;
    dut->eval();
    dut->reset = 0;
    std::cout << "Reset at pc = " << std::hex << dut->io_pc_IF << std::endl;
}

void cpu_exec(uint64_t n){
#ifndef CONFIG_REF
    switch(cpu.state){
        case SIM_ABORT: case SIM_END:
        std::cout << "Program execution has ended." << std::endl;
        return;
        default: cpu.state = SIM_RUNNING;
    }
#endif
    while(n--){
        uint32_t commit_num = 0;
        commit_num += commit_update(dut->io_commit_en1, dut->io_commit_pc_1, dut->io_commit_rd1, dut->io_commit_rd_valid1, dut->io_commit_rf_wdata1);
        commit_num += commit_update(dut->io_commit_en2, dut->io_commit_pc_2, dut->io_commit_rd2, dut->io_commit_rd_valid2, dut->io_commit_rf_wdata2);
        commit_num += commit_update(dut->io_commit_en3, dut->io_commit_pc_3, dut->io_commit_rd3, dut->io_commit_rd_valid3, dut->io_commit_rf_wdata3);
        commit_num += commit_update(dut->io_commit_en4, dut->io_commit_pc_4, dut->io_commit_rd4, dut->io_commit_rd_valid4, dut->io_commit_rf_wdata4);
        if(cpu.state != SIM_RUNNING) break;
        single_cycle();
    }
#ifndef CONFIG_REF
#ifdef ITRACE
    print_ilog();
#endif
    switch(cpu.state){
        case SIM_END: 
        Log("simulation %s at pc = " FMT_WORD, (cpu.reg[4] == 0 ? INLINE_FMT("HIT GOOD TRAP", ANSI_FG_GREEN) : 
            INLINE_FMT("HIT BAD TRAP", ANSI_FG_RED)), cpu.halt_pc); break;
        case SIM_ABORT:
        Log("simulation %s at pc = " FMT_WORD, INLINE_FMT("ABORT", ANSI_FG_RED), cpu.halt_pc); break;
        case SIM_STOP:
        Log("simulation %s at pc = " FMT_WORD, INLINE_FMT("STOP", ANSI_FG_YELLOW), cpu.halt_pc); break;
        break;
    }
#endif
}

