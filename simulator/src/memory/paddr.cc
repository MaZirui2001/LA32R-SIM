#include <common.h>


uint8_t pmem[CONFIG_PMEM_SIZE];

inline bool in_pmem(uint32_t addr) {
    return addr >= CONFIG_PMEM_BASE && addr < CONFIG_PMEM_BASE + CONFIG_PMEM_SIZE;
}
inline uint8_t* addr_convert(uint32_t addr){
    return pmem + addr - CONFIG_PMEM_BASE;
}
uint32_t pmem_read(uint32_t addr, uint32_t len) {
    uint8_t* p = addr_convert(addr);
    switch(len){
        case 1: return *p;
        case 2: return *(uint16_t*)p;
        case 4: return *(uint32_t*)p;
        default: assert(0);
    }
}
uint32_t paddr_read(uint32_t addr, uint32_t len) {
    assert(in_pmem(addr));
    return pmem_read(addr, len);
}

void pmem_write(uint32_t addr, uint32_t data, uint32_t len) {
    uint8_t* p = addr_convert(addr);
    switch(len){
        case 1: *p = data; break;
        case 2: *(uint16_t*)p = data; break;
        case 4: *(uint32_t*)p = data; break;
        default: assert(0);
    }

}
void paddr_write(uint32_t addr, uint32_t data, uint32_t len) {
    assert(in_pmem(addr));
    pmem_write(addr, data, len);
    return;
}