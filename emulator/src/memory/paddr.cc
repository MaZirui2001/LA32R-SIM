#include <common.h>
#include <cpu.h>
#include <mmio.h>

uint8_t pmem[CONFIG_PMEM_SIZE];

bool in_pmem(uint32_t addr) {
    return addr >= CONFIG_PMEM_BASE && addr < CONFIG_PMEM_BASE + CONFIG_PMEM_SIZE;
}
uint8_t* addr_convert(uint32_t addr){
    return pmem + addr - CONFIG_PMEM_BASE;
}
uint32_t host_read(uint8_t* p, uint32_t len){
    switch(len){
        case 1: return *p;
        case 2: return *(uint16_t*)p;
        case 4: return *(uint32_t*)p;
        default: assert(0);
    }
}
uint32_t pmem_read(uint32_t addr, uint32_t len) {
    uint8_t* p = addr_convert(addr);
    return host_read(p, len);
}
// uint32_t paddr_read(uint32_t addr, uint32_t len) {
//     if(!in_pmem(addr)){
// #ifndef DEVICE
//         std::cout << "Read: Physical address " << std::hex << addr << " is outside of physical memory!" << std::endl;
//         cpu.state = SIM_ABORT;
//         return 0;
// #else   
//         return mmio_read(addr, len);
// #endif
//     }
//     return pmem_read(addr, len);
// }
static uint32_t rstate = 0;
static uint32_t araddr = 0;
static uint32_t arlen = 0;
static uint32_t arsize = 0;
static uint32_t rcnt = 0;
void paddr_read(VCPU *dut){
    if(rstate == 0){
        dut->io_rvalid = 0;
        rcnt = 0;
        dut->io_arready = 1;
        if(dut->io_arvalid){
            araddr = dut->io_araddr;
            arlen = dut->io_arlen + 1;
            arsize = 1 << dut->io_arsize;
            rstate = 1;
        }
    }
    else if(rstate == 1){
        dut->io_arready = 0;
        dut->io_rvalid = 1;
        dut->io_rlast = (rcnt == arlen - 1);
        if(in_pmem(araddr + rcnt * arsize)) dut->io_rdata = pmem_read(araddr + rcnt * arsize, arsize);
        else mmio_read(araddr + rcnt * arsize, arsize);
        rcnt += dut->io_rready;
        if(dut->io_rlast && dut->io_rready){
            rstate = 0;
        }
    }
}

void host_write(uint8_t* p, uint32_t data, uint32_t len){
    switch(len){
        case 1: *p = data; break;
        case 2: *(uint16_t*)p = data; break;
        case 4: *(uint32_t*)p = data; break;
        default: assert(0);
    }
}
void pmem_write(uint32_t addr, uint32_t data, uint32_t len) {
    uint8_t* p = addr_convert(addr);
    host_write(p, data, len);
}
// void paddr_write(uint32_t addr, uint32_t data, uint32_t len) {
//     if(!in_pmem(addr)){
// #ifndef DEVICE
//         std::cout << "Write: Physical address " << std::hex << addr - CONFIG_PMEM_BASE << " is outside of physical memory!" << std::endl;
//         cpu.state = SIM_ABORT;
//         return;
// #else
//         mmio_write(addr, data, len);
//         return;
// #endif
//     }
//     pmem_write(addr, data, len);
//     return;
// }
static uint32_t wstate = 0;
static uint32_t awaddr = 0;
static uint32_t awlen = 0;
static uint32_t awsize = 0;
static uint32_t wcnt = 0;

void paddr_write(VCPU* dut){
    if(wstate == 0){
        if(dut->io_awvalid){
            awaddr = dut->io_awaddr;
            awlen = dut->io_awlen + 1;
            awsize = 1 << dut->io_awsize;
            wstate = 1;
        }
        dut->io_bvalid = 0;
        dut->io_awready = 1;
        wcnt = 0;
    }
    else if(wstate == 1){
        dut->io_awready = 0;
        dut->io_wready = 1;
        // std::cout << "awaddr = " << std::hex << awaddr << std::endl;
        // std::cout << "wdata  = " << std::hex << dut->io_wdata << std::endl;
        if(dut->io_wvalid){
            if(in_pmem(awaddr)){
                for(int i = 0; i < awsize; i++){
                    if(dut->io_wstrb & (1 << i)){
                        pmem_write(awaddr + wcnt * awsize + i, dut->io_wdata >> (i * 8), 1);
                    }
                }
            }
            else{
                mmio_write(awaddr, dut->io_wdata, awsize);
            }
            wcnt++;

            if(dut->io_wlast){
                wstate = 2;
            }
        }
    }
    else if(wstate == 2){
        dut->io_bvalid = 1;
        dut->io_wready = 0;
        if(dut->io_bready){
            wstate = 0;
        }
    }
}