#include <common.h>
#include <cpu.h>
#include <mmio.h>
#include <mmu.h>

//uint8_t pmem[CONFIG_PMEM_SIZE];
std::unordered_map<uint32_t, uint32_t> pmem;

bool in_pmem(uint32_t addr) {
    //return addr >= CONFIG_PMEM_BASE && addr < CONFIG_PMEM_BASE + CONFIG_PMEM_SIZE;
    return !(addr >= 0xa0000000 && addr < 0xafffffff);
}

uint8_t* addr_convert(uint32_t addr){
    // return pmem + addr - CONFIG_PMEM_BASE;
    // std::cout << "addr_convert: " << std::hex << addr << std::endl;
    return (uint8_t*)&pmem[addr >> 2] + (addr & 0x3);
}
// uint32_t get_mem_elem(uint32_t addr){
//     return pmem[addr];
// }

std::pair<uint32_t, uint32_t> vaddr_check(uint32_t vaddr, uint32_t align_mask, uint32_t mem_type){
    // if(BITS(cpu.csr[CSR_IDX::CRMD], 1, 0) == 0x3 && (vaddr & 0x80000000)){
    //     std::cout << vaddr << std::endl;
    //     return std::make_pair(vaddr, ADEM);
    // }
    if(vaddr & align_mask){
        // ALE
        return std::make_pair(vaddr, ALE);
    }
    // tlb
    return addr_translate(vaddr, mem_type); //std::make_pair((uint32_t)(paddr), (uint32_t)(paddr >> 32));
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
    // std::cout << "pmem_read: " << std::hex << addr << std::endl;
    return host_read(p, len);
    // return pmem[addr >> 2] >> ((addr & 0x03) << 3);
}

uint32_t paddr_read(uint32_t addr, uint32_t len) {
    if(!in_pmem(addr)){
#ifndef DEVICE
        // std::cout << "Read: Physical address " << std::hex << addr << " is outside of physical memory!" << std::endl;
        // cpu.state = SIM_ABORT;
        return 0;
#else
        return mmio_read(addr, len);
#endif
    }
    return pmem_read(addr, len);
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
    //pmem[addr >> 2] = (pmem[addr >> 2] & ~(((uint32_t)0xff) << ((addr & 0x03) << 3))) | (data << ((addr & 0x03) << 3));
}
void paddr_write(uint32_t addr, uint32_t data, uint32_t len) {
    if(!in_pmem(addr)){
#ifndef DEVICE
        // std::cout << "Write: Physical address " << std::hex << addr - CONFIG_PMEM_BASE << " is outside of physical memory!" << std::endl;
        // cpu.state = SIM_ABORT;
        return;
#else
        mmio_write(addr, data, len);
        return;
#endif
    }
    pmem_write(addr, data, len);
    return;
}