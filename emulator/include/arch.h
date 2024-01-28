#ifndef __ARCH_H__
#define __ARCH_H__

#include <stdint.h>
#include <unordered_map>
#include <config.h>

// loongarch reg name
extern const char* reg_name[32];
extern const char* preg_name[128];
extern std::unordered_map<uint32_t, uint32_t> csr_mask;
extern std::unordered_map<unsigned int, unsigned int> csr_map;
// loongarch csr name 
extern std::unordered_map<unsigned int, const char*> csr_name;
#define RESET_VECTOR CONFIG_PMEM_BASE

struct CPU_State {
    uint32_t reg[32];
    uint32_t pc;
    uint32_t csr[30];
    int state;
    uint32_t halt_pc;
    uint32_t inst;
    inline uint32_t csr_read(uint32_t name){
        if(csr_map.find(name) == csr_map.end()){
            return 0;
        }
        return csr[csr_map[name]];
    }
    inline void csr_write(uint32_t name, uint32_t val){
        if(csr_map.find(name) == csr_map.end()){
            return;
        }
        csr[csr_map[name]] = (csr[csr_map[name]] & ~csr_mask[name]) | (val & csr_mask[name]);
    }
};

#endif // __ARCH_H__