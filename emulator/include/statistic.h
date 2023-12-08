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
    uint64_t stall_by_iq5 = 0;
    uint64_t stall_by_sb = 0;
    uint64_t stall_by_icache = 0;
    uint64_t stall_by_dcache = 0;
    uint64_t stall_by_div = 0;
    uint64_t icache_visit = 0;
    uint64_t icache_miss = 0;
    uint64_t dcache_visit = 0;
    uint64_t dcache_miss = 0;

    uint64_t total_issue = 0;
    uint64_t iq1_issue = 0;
    uint64_t iq2_issue = 0;
    uint64_t iq3_issue = 0;
    uint64_t iq4_issue = 0;
    uint64_t iq5_issue = 0;
    uint64_t issue_1 = 0;
    uint64_t issue_2 = 0;
    uint64_t issue_3 = 0;
    uint64_t issue_4 = 0;
    uint64_t issue_5 = 0;

public:
    void set_name(const char* name){
        this->name = name;
    }
    void ipc_update(uint32_t commit_num);

    void mul_commit_update(uint32_t commit_num);

    void predict_update(VCPU* dut);

    void stall_update(VCPU* dut);

    void issue_update(VCPU* dut);

    void cache_update(VCPU* dut);

    void print_stat();

    void show_ipc_now();

    void generate_markdown_report();
};

void init_statistic(const char* name);
#endif
