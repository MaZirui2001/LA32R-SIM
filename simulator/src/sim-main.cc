#include <common.h>
#include <command.h>
#include <cpu.h>
#include <monitor.h>

CPU_State cpu;
int main(int argc, char* argv[]){
    init_monitor(argc, argv);
    reset();
    command_mainloop();
    return cpu.state == SIM_ABORT;
}