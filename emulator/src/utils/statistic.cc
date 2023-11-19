#include <statistic.h>
#include <fstream>
using namespace std;

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

void statistic::predict_update(VCPU* dut){
    if(dut->io_commit_is_br1){
        total_br_type[dut->io_commit_br_type1]++;
        failed_br_type[dut->io_commit_br_type1] += dut->io_commit_predict_fail1;
        predict_fail_time += dut->io_commit_predict_fail1;
    }
    if(dut->io_commit_is_br2){
        total_br_type[dut->io_commit_br_type2]++;
        failed_br_type[dut->io_commit_br_type2] += dut->io_commit_predict_fail2;
        predict_fail_time += dut->io_commit_predict_fail2;
    }
    if(dut->io_commit_is_br3){
        total_br_type[dut->io_commit_br_type3]++;
        failed_br_type[dut->io_commit_br_type3] += dut->io_commit_predict_fail3;
        predict_fail_time += dut->io_commit_predict_fail3;
    }
    if(dut->io_commit_is_br4){
        total_br_type[dut->io_commit_br_type4]++;
        failed_br_type[dut->io_commit_br_type4] += dut->io_commit_predict_fail4;
        predict_fail_time += dut->io_commit_predict_fail4;
    }
}
void statistic::stall_update(VCPU* dut){
    stall_by_fetch_queue += dut->io_commit_stall_by_fetch_queue;
    stall_by_rename += dut->io_commit_stall_by_rename;
    stall_by_rob += dut->io_commit_stall_by_rob;
    stall_by_iq1 += dut->io_commit_stall_by_iq1;
    stall_by_iq2 += dut->io_commit_stall_by_iq2;
    stall_by_iq3 += dut->io_commit_stall_by_iq3;
    stall_by_iq4 += dut->io_commit_stall_by_iq4;
    stall_by_iq5 += dut->io_commit_stall_by_iq5;
    stall_by_sb += dut->io_commit_stall_by_sb;
}

void statistic::issue_update(VCPU* dut){
    total_issue += dut->io_commit_iq1_issue || dut->io_commit_iq2_issue || dut->io_commit_iq3_issue || dut->io_commit_iq4_issue || dut->io_commit_iq5_issue;
    uint64_t issue_num = dut->io_commit_iq1_issue + dut->io_commit_iq2_issue + dut->io_commit_iq3_issue + dut->io_commit_iq4_issue + dut->io_commit_iq5_issue;
    iq1_issue += dut->io_commit_iq1_issue;
    iq2_issue += dut->io_commit_iq2_issue;
    iq3_issue += dut->io_commit_iq3_issue;
    iq4_issue += dut->io_commit_iq4_issue;
    iq5_issue += dut->io_commit_iq5_issue;
    switch (issue_num){
    case 1:
        issue_1++;
        break;
    case 2:
        issue_2++;
        break;
    case 3:
        issue_3++;
        break;
    case 4:
        issue_4++;
        break;
    case 5:
        issue_5++;
        break;
    default:
        break;
    }
}

void statistic::cache_update(VCPU* dut){
    icache_visit += dut->io_commit_icache_visit;
    icache_miss += dut->io_commit_icache_miss;
    dcache_visit += dut->io_commit_dcache_visit;
    dcache_miss += dut->io_commit_dcache_miss;
    stall_by_icache += dut->io_commit_stall_by_icache;
    stall_by_dcache += dut->io_commit_stall_by_dcache;
}
void statistic::print_stat(){
    Log("Total instructions = %lu, Total clocks = %lu, IPC = %lf", total_insts, total_clocks, double(total_insts) / total_clocks);
}

void statistic::show_ipc_now(){
    double ipc = double(total_insts) / total_clocks;
    // 清除掉上一次的输出
    printf("\r");
    // 输出当前的IPC
    printf("IPC = %lf", ipc);
    // 刷新输出缓冲区，使输出立即生效
    fflush(stdout);
}

void statistic::generate_markdown_report(){
    ofstream fout = ofstream("reports/report-" + name + ".md");
    fout << "# 处理器运行报告" << endl;
    fout << "## 程序运行情况" << endl;
    fout << "|程序名|总指令数|总时钟数|IPC|" << endl;
    fout << "|---|---|---|---|" << endl;
    fout << "|" << name << "|" << total_insts << "|" << total_clocks << "|" << double(total_insts) / total_clocks << "|" << endl;
    fout << endl;

    fout << "## 分支预测（含预译码纠正）" << endl;
    fout << "### 整体情况" << endl;
    fout << "|总分支数|总预测正确数|总预测正确率|" << endl;
    fout << "|---|---|---|" << endl;
    uint64_t total_br = total_br_type[0] + total_br_type[1] + total_br_type[2];
    uint64_t failed_br = failed_br_type[0] + failed_br_type[1] + failed_br_type[2];
    fout << "|" << total_br << "|" << total_br - failed_br << "|" << (total_br == 0 ? 100 : double(total_br - failed_br) / total_br * 100) << "%|" << endl;
    fout << endl;

    fout << "### 各类指令预测" << endl;
    fout << "|分支类型|总分支数|总预测正确数|总预测正确率|" << endl;
    fout << "|---|---|---|---|" << endl;
    fout << "|**Branch**| " << total_br_type[0] << " | " << total_br_type[0] - failed_br_type[0] << " | " << (total_br_type[0] == 0 ? 100 : double(total_br_type[0] - failed_br_type[0]) / total_br_type[0] * 100) << "%|" << endl;
    fout << "|**JIRL**| " << total_br_type[1] << " | " << total_br_type[1] - failed_br_type[1] << " | " << (total_br_type[1] == 0 ? 100 : double(total_br_type[1] - failed_br_type[1]) / total_br_type[1] * 100) << "%|" << endl;
    fout << "|**BL**| " << total_br_type[2] << " | " << total_br_type[2] - failed_br_type[2] << " | " << (total_br_type[2] == 0 ? 100 : double(total_br_type[2] - failed_br_type[2]) / total_br_type[2] * 100) << "%|" << endl;
    fout << endl;

    fout << "### 高速缓存命中" << endl;
    fout << "|高速缓存|访问次数|命中次数|命中率|" << endl;
    fout << "|---|---|---|---|" << endl;
    fout << "|**指令高速缓存**| " << icache_visit << " | " << icache_visit - icache_miss << " | " << (icache_visit == 0 ? 100 : double(icache_visit - icache_miss) / icache_visit * 100) << "%|" << endl;
    fout << "|**数据高速缓存**| " << dcache_visit << " | " << dcache_visit - dcache_miss << " | " << (dcache_visit == 0 ? 100 : double(dcache_visit - dcache_miss) / dcache_visit * 100) << "%|" << endl;

    fout << "## 流水线阻塞" << endl;
    fout << "|阻塞原因|阻塞时钟数|阻塞率|" << endl;
    fout << "|---|---|---|" << endl;
    fout << "|**指令高速缓存缺失**| " << stall_by_icache << " | " << (total_clocks == 0 ? 0 : double(stall_by_icache) / total_clocks * 100) << "%|" << endl;
    fout << "|**数据高速缓存缺失**| " << stall_by_dcache << " | " << (total_clocks == 0 ? 0 : double(stall_by_dcache) / total_clocks * 100) << "%|" << endl;
    fout << "|**取指队列满**| " << stall_by_fetch_queue << " | " << (total_clocks == 0 ? 0 : double(stall_by_fetch_queue) / total_clocks * 100) << "%|" << endl;
    fout << "|**重命名空闲列表空**|" << stall_by_rename << " | " << (total_clocks == 0 ? 0 : double(stall_by_rename) / total_clocks * 100) << "%|" << endl;
    fout << "|**重排序缓冲区满**|" << stall_by_rob << " | " << (total_clocks == 0 ? 0 : double(stall_by_rob) / total_clocks * 100) << "%|" << endl;
    fout << "|**第一算数发射队列满**|" << stall_by_iq1 << " | " << (total_clocks == 0 ? 0 : double(stall_by_iq1) / total_clocks * 100) << "%|" << endl;
    fout << "|**算数分支发射队列满**|" << stall_by_iq2 << " | " << (total_clocks == 0 ? 0 : double(stall_by_iq2) / total_clocks * 100) << "%|" << endl;
    fout << "|**内存读写发射队列满**|" << stall_by_iq3 << " | " << (total_clocks == 0 ? 0 : double(stall_by_iq3) / total_clocks * 100) << "%|" << endl;
    fout << "|**乘除法发射队列满**|" << stall_by_iq4 << " | " << (total_clocks == 0 ? 0 : double(stall_by_iq4) / total_clocks * 100) << "%|" << endl;
    fout << "|**第二算数发射队列满**|" << stall_by_iq5 << " | " << (total_clocks == 0 ? 0 : double(stall_by_iq5) / total_clocks * 100) << "%|" << endl;
    fout << "|**写缓冲满**|" << stall_by_sb << " | " << (total_clocks == 0 ? 0 : double(stall_by_sb) / total_clocks * 100) << "%|" << endl;
    fout << endl;
    
    fout << "## 发射阶段" << endl;
    fout << "### 多发射率" << endl;
    fout << "|总发射数|发射率|单发射率|双发射率|三发射率|四发射率|五发射率|" << endl;
    fout << "|---|---|---|---|---|---|" << endl;
    fout << "|" << total_issue << "|" << (total_clocks == 0 ? 0 : double(total_issue) / total_clocks * 100) << "%|" << 
            (total_issue == 0 ? 0 : double(issue_1) / total_issue * 100) << "%|" << (total_issue == 0 ? 0 : double(issue_2) / total_issue * 100) << "%|" << (total_issue == 0 ? 0 : double(issue_3) / total_issue * 100) << "%|" << (total_issue == 0 ? 0 : double(issue_4) / total_issue * 100) << "%|" << (total_issue == 0 ? 0 : double(issue_5) / total_issue * 100) << "%|" << endl;
    fout << endl;
    fout << "### 各发射队列发射率" << endl;
    fout << "|发射队列名称|发射率|" << endl;
    fout << "|---|---|" << endl;
    fout << "|**第一算数发射队列**|" << (total_clocks == 0 ? 0 : double(iq1_issue) / total_clocks * 100) << "%|" << endl;
    fout << "|**算数分支发射队列**|" << (total_clocks == 0 ? 0 : double(iq2_issue) / total_clocks * 100) << "%|" << endl;
    fout << "|**内存读写发射队列**|" << (total_clocks == 0 ? 0 : double(iq3_issue) / total_clocks * 100) << "%|" << endl;
    fout << "|**乘除法发射队列**|" << (total_clocks == 0 ? 0 : double(iq4_issue) / total_clocks * 100) << "%|" << endl;
    fout << "|**第二算数发射队列**|" << (total_clocks == 0 ? 0 : double(iq5_issue) / total_clocks * 100) << "%|" << endl;
    fout << endl;


    fout << "## 提交阶段" << endl;
    fout << "|总提交数|提交率|1条提交率|2条提交率|3条提交率|4条提交率|" << endl;
    fout << "|---|---|---|---|---|---|" << endl;
    fout << "|" << total_commits << "|" << (total_clocks == 0 ? 0 : double(total_commits) / total_clocks * 100) << "%|" << 
            (total_commits == 0 ? 0 : double(commit_1) / total_commits * 100) << "%|" << (total_commits == 0 ? 0 : double(commit_2) / total_commits * 100) << "%|" << (total_commits == 0 ? 0 : double(commit_3) / total_commits * 100) << "%|" << (total_commits == 0 ? 0 : double(commit_4) / total_commits * 100) << "%|" << endl;
    
    
    fout.close();
}

