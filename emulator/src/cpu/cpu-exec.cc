#include <common.h>
#include <paddr.h>
#include <cpu.h>
#include <disasm.h>
#include <device.h>
#include <difftest.h>
#include <statistic.h>
#include <iomanip>
// #define DUMP_WAVE
// #define FRONT_END_4
#ifdef ITRACE
typedef struct{
    uint32_t pc;
    uint32_t inst;
    uint32_t rf_wdata;
    uint32_t prd;
    uint32_t prj;
    uint32_t prk;
}inst_log_t;

uint32_t reg_rename_table[32];
static statistic stat;


#define ILOG_SIZE 16
static inst_log_t ilog[ILOG_SIZE];
static int ilog_idx = 0;
void print_ilog(){
    std::cout << std::left << std::setw(16) << std::setfill(' ') << "PC" ;
    std::cout << std::left << std::setw(46) << std::setfill(' ') << "INSTRUCTION" << '\t' << "RF_WDATA" << std::endl;
    std::cout << std::left << std::setw(16+46+10) << std::setfill('-') << "" << std::endl;
    for(int i = 0; i < ILOG_SIZE; i++){
        std::cout << std::hex << std::setw(8) << std::setfill('0') << ilog[(ilog_idx+i)%ILOG_SIZE].pc << ": \t";
        char buf[100];
        disasm(buf, ilog[(ilog_idx+i)%ILOG_SIZE].inst, ilog[(ilog_idx+i)%ILOG_SIZE].prd, ilog[(ilog_idx+i)%ILOG_SIZE].prj, ilog[(ilog_idx+i)%ILOG_SIZE].prk);
        std::cout << std::left << std::setw(46) << std::setfill(' ') << buf << '\t';
        std::cout << std::right << std::hex << std::setw(8) << std::setfill('0') << ilog[(ilog_idx+i)%ILOG_SIZE].rf_wdata << std::endl;
    }
}
void add_ilog(uint32_t pc, uint32_t inst, uint32_t rf_wdata, uint32_t prd, uint32_t rd, bool rd_valid, uint32_t rj, uint32_t rk){
    ilog[ilog_idx].pc = pc;
    ilog[ilog_idx].inst = inst;
    ilog[ilog_idx].rf_wdata = rf_wdata;
    if(rd_valid && rd != 0){
        reg_rename_table[rd] = prd;
    }
    ilog[ilog_idx].prj = reg_rename_table[rj];
    ilog[ilog_idx].prk = reg_rename_table[rk];

    ilog[ilog_idx].prd = rd == 0 ? 0 : prd;

    ilog_idx = (ilog_idx + 1) % ILOG_SIZE;
}
#endif

inline bool test_break(uint32_t inst){
    return inst == 0x80000000;
}

void set_cpu_state(uint32_t pc, uint32_t rd, bool rd_valid, uint32_t rf_wdata, uint32_t csr, uint32_t csr_wdata, bool csr_we){
    if(rd_valid){
        cpu.reg[rd] = rf_wdata;
    }
    if(csr_we){
        cpu.csr[csr] = csr_wdata;
    }
    cpu.pc = pc;
}
bool commit_update(bool commit_en, uint32_t pc, uint32_t rd, bool rd_valid, uint32_t rf_wdata, uint32_t prd, uint32_t csr, uint32_t csr_wdata, bool csr_we){
    if(commit_en){
        auto inst = pmem_read(cpu.pc, 4);
        #ifdef ITRACE
            if(cpu.state == SIM_RUNNING) {
                auto rd = BITS(inst, 31, 26) == 0x15 ? 0 : BITS(inst, 4, 0);
                add_ilog(cpu.pc, inst, rf_wdata, prd, rd, rd_valid, BITS(inst, 9, 5), BITS(inst, 14, 10));
            }
        #endif
        set_cpu_state(pc, rd, rd_valid, rf_wdata, csr, csr_wdata, csr_we);

        if(test_break(inst)){
            cpu.state = SIM_END;
            cpu.halt_pc = pc;
        }
        return true;
    }
    return false;
}

void single_cycle(){
    dut->clock = 0;
    dut->eval();
    paddr_write(dut);
    paddr_read(dut);

    dut->clock = 1;
    dut->eval();
#ifdef DUMP_WAVE
    sim_time++;
    //if(sim_time >= 2700000 && sim_time <= 2800000)
        m_trace->dump(sim_time);
#endif
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
    std::cout << "Reset at pc = " << std::hex << 0x1c000000 << std::endl;
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
        commit_num += commit_update(dut->io_commit_en_0, dut->io_commit_pc_0, dut->io_commit_rd_0, dut->io_commit_rd_valid_0, dut->io_commit_rf_wdata_0, dut->io_commit_prd_0, dut->io_commit_csr_waddr_0, dut->io_commit_csr_wdata_0, dut->io_commit_csr_we_0);
        commit_num += commit_update(dut->io_commit_en_1, dut->io_commit_pc_1, dut->io_commit_rd_1, dut->io_commit_rd_valid_1, dut->io_commit_rf_wdata_1, dut->io_commit_prd_1, dut->io_commit_csr_waddr_1, dut->io_commit_csr_wdata_1, dut->io_commit_csr_we_1);
    #ifdef FRONT_END_4
        commit_num += commit_update(dut->io_commit_en_2, dut->io_commit_pc_2, dut->io_commit_rd_2, dut->io_commit_rd_valid_2, dut->io_commit_rf_wdata_2, dut->io_commit_prd_2, dut->io_commit_csr_waddr_2, dut->io_commit_csr_wdata_2, dut->io_commit_csr_we_2);
        commit_num += commit_update(dut->io_commit_en_3, dut->io_commit_pc_3, dut->io_commit_rd_3, dut->io_commit_rd_valid_3, dut->io_commit_rf_wdata_3, dut->io_commit_prd_3, dut->io_commit_csr_waddr_3, dut->io_commit_csr_wdata_3, dut->io_commit_csr_we_3);
    #endif
        if(cpu.state != SIM_RUNNING) break;
#ifdef DIFFTEST
        bool uncache = dut->io_commit_is_ucread_0 || dut->io_commit_is_ucread_1;
    #ifdef FRONT_END_4
        uncache = uncache || dut->io_commit_is_ucread_2 || dut->io_commit_is_ucread_3;
    #endif
        if(uncache){
            difftest_sync();
        }
        else if(commit_num != 0) difftest_step(commit_num);
#endif
        stat.ipc_update(commit_num);
        stat.mul_commit_update(commit_num);
        stat.predict_update(dut);
        stat.stall_update(dut);
        stat.issue_update(dut);
        stat.cache_update(dut);
        if((n & (16384-1)) == 0)
            stat.show_ipc_now();
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
    stat.print_stat();
    stat.generate_markdown_report();
#endif
}

void init_statistic(const char* name){
    std::string sname(name);
    auto start = sname.find_last_of('/');
    auto end = sname.find_first_of('.');
    // auto cname = sname.substr(start + 1, end - start - 1).c_str();
    // std::cout << sname.substr(start + 1, end - start - 1).c_str() << " " << start << " " << end << std::endl;
    stat.set_name(sname.substr(start + 1, end - start - 1).c_str());
}

