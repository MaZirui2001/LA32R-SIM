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

public:
    void ipc_update(uint32_t commit_num);

    void mul_commit_update(uint32_t commit_num);

    void predict_update(bool predict_fail, uint32_t commit_num);

    void print_stat();
};

#endif
