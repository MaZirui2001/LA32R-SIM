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
void statistic::print_stat(){
    Log("Total instructions = %lu, Total clocks = %lu, IPC = %lf", total_insts, total_clocks, double(total_insts) / total_clocks);
    Log("1 commit rate = %lf, 2 commit rate = %lf, 3 commit rate = %lf, 4 commit rate = %lf", double(commit_1) / total_commits, double(commit_2) / total_commits, double(commit_3) / total_commits, double(commit_4) / total_commits);
    Log("Bubbles by predict fail = %lu, Bubble rate = %lf", bubble_by_predict_fail, double(bubble_by_predict_fail) / total_clocks);

}

