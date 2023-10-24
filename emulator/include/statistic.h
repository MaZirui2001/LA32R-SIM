#ifndef __STATISTIC_H__
#define __STATISTIC_H__

#include <common.h>
#include <VCPU.h>

class statistic {
private:
    std::string name;
    uint64_t total_clocks = 0;
    uint64_t total_insts = 0;
    uint64_t total_commits = 0;
    uint64_t commit_1 = 0;
    uint64_t commit_2 = 0;
    uint64_t commit_3 = 0;
    uint64_t commit_4 = 0;
    uint64_t predict_fail_time = 0;
    uint64_t total_br_type[3] = {0};
    uint64_t failed_br_type[3] = {0};
    uint64_t stall_by_fetch_queue = 0;
    uint64_t stall_by_rename = 0;
    uint64_t stall_by_rob = 0;
    uint64_t stall_by_iq1 = 0;
    uint64_t stall_by_iq2 = 0;
    uint64_t stall_by_iq3 = 0;
    uint64_t stall_by_iq4 = 0;
    uint64_t stall_by_sb = 0;

public:
    void set_name(const char* name){
        this->name = name;
    }
    void ipc_update(uint32_t commit_num);

    void mul_commit_update(uint32_t commit_num);

    void predict_update(VCPU* dut);

    void stall_update(VCPU* dut);

    void print_stat();

    void generate_markdown_report();
};

void init_statistic(const char* name);
#endif
