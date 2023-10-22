#include <statistic.h>

void statistic::ipc_update(uint32_t commit_num) {
    total_clocks++;
    total_insts += commit_num;
}
void statistic::mul_commit_update(uint32_t commit_num){
    if(commit_num != 0){
        total_commits++;
    }
    switch (commit_num){
    case 1:
        commit_1++;
        break;
    case 2:
        commit_2++;
        break;
    case 3:
        commit_3++;
        break;
    case 4:
        commit_4++;
        break;
    default:
        break;
    }
}
void statistic::predict_update(bool predict_fail, uint32_t commit_num){
    if(predict_fail){
        is_bubbling_by_predict_fail = true;
    }
    else if(is_bubbling_by_predict_fail){
        if(commit_num != 0){
            is_bubbling_by_predict_fail = false;
        }
        else{
            bubble_by_predict_fail++;
        }
    }
}
void statistic::stall_update(bool _stall_by_fetch_queue, bool _stall_by_rename, bool _stall_by_rob, bool _stall_by_iq1, bool _stall_by_iq2, bool _stall_by_iq3, bool _stall_by_iq4){
    stall_by_fetch_queue += _stall_by_fetch_queue;
    stall_by_rename += _stall_by_rename;
    stall_by_rob += _stall_by_rob;
    stall_by_iq1 += _stall_by_iq1;
    stall_by_iq2 += _stall_by_iq2;
    stall_by_iq3 += _stall_by_iq3;
    stall_by_iq4 += _stall_by_iq4;
}
void statistic::print_stat(){
    Log("Total instructions = %lu, Total clocks = %lu, IPC = %lf", total_insts, total_clocks, double(total_insts) / total_clocks);
    Log("Commit rate: 1 = %.2lf%%, 2 = %.2lf%%, 3 = %.2lf%%, 4 = %.2lf%%", double(commit_1) / total_commits * 100, double(commit_2) / total_commits * 100, double(commit_3) / total_commits * 100, double(commit_4) / total_commits * 100);
    Log("Bubbles by predict fail = %lu, Bubble rate = %lf", bubble_by_predict_fail, double(bubble_by_predict_fail) / total_clocks);
    Log("Stall by fetch queue = %.3lf%%, Stall by rename = %.3lf%%, Stall by rob = %.3lf%%, Stall by iq1 = %.3lf%%, Stall by iq2 = %.3lf%%, Stall by iq3 = %.3lf%%, Stall by iq4 = %.3lf%%", double(stall_by_fetch_queue) / total_clocks * 100, double(stall_by_rename) / total_clocks * 100, double(stall_by_rob) / total_clocks * 100, double(stall_by_iq1) / total_clocks * 100, double(stall_by_iq2) / total_clocks * 100, double(stall_by_iq3) / total_clocks * 100, double(stall_by_iq4) / total_clocks * 100);
}

