#include <common.h>
#include <command.h>
#include <cpu.h>
#include <monitor.h>
#include <device.h>
#include <random>
#include <time.h>

CPU_State cpu;
int main(int argc, char* argv[]){
    srand(time(0));
    init_monitor(argc, argv);
    reset();
    command_mainloop();
    free_device();

    
    return cpu.state == SIM_ABORT;
}