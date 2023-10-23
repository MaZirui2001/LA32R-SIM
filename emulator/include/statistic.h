#ifndef __STATISTIC_H__
#define __STATISTIC_H__

#include <common.h>

class statistic {
private:
    uint64_t total_clocks = 0;
    uint64_t total_insts = 0;
    uint64_t total_commits = 0;
    uint64_t commit_1 = 0;
    uint64_t commit_2 = 0;
    uint64_t commit_3 = 0;
    uint64_t commit_4 = 0;
    uint64_t bubble_by_predict_fail = 0;
    bool is_bubbling_by_predict_fail = false;
    uint64_t stall_by_fetch_queue = 0;
    uint64_t stall_by_rename = 0;
    uint64_t stall_by_rob = 0;
    uint64_t stall_by_iq1 = 0;
    uint64_t stall_by_iq2 = 0;
    uint64_t stall_by_iq3 = 0;
    uint64_t stall_by_iq4 = 0;
    uint64_t stall_by_sb = 0;

public:
    void ipc_update(uint32_t commit_num);

    void mul_commit_update(uint32_t commit_num);

    void predict_update(bool predict_fail, uint32_t commit_num);

    void stall_update(bool stall_by_fetch_queue, bool stall_by_rename, bool stall_by_rob, bool stall_by_iq1, bool stall_by_iq2, bool stall_by_iq3, bool stall_by_iq4, bool stall_by_sb);

    void print_stat();
};

#endif
