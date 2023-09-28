#include <common.h>
#include <command.h>
#include <cpu.h>
#include <monitor.h>
#include <mmio.h>

CPU_State cpu;
int main(int argc, char* argv[]){
    init_monitor(argc, argv);
    reset();
    command_mainloop();
    free_io_space();
    
    return cpu.state == SIM_ABORT;
}