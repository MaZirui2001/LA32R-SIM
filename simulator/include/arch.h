#ifndef __ARCH_H__
#define __ARCH_H__


#include <unordered_map>
#include <config.h>
#include <iostream>
#include <stdint.h>

// loongarch reg name
extern const char* reg_name[32];
// loongarch csr name 
extern std::unordered_map<unsigned int, const char*> csr_name;
extern std::unordered_map<unsigned int, unsigned int> csr_map;
extern std::unordered_map<uint32_t, uint32_t> csr_mask;
#define RESET_VECTOR CONFIG_PMEM_BASE
#define REG_SIZE  (32 + 1)
#define CSR_SIZE  (30)
#define TLB_SIZE  (16)

enum class CSRNAME{
    CRMD = 0x0, PRMD = 0x1, EUEN = 0x2, ECFG = 0x4, 
    ESTAT = 0x5, ERA = 0x6, BADV = 0x7, EENTRY = 0xc,
    TLBIDX = 0x10, TLBEHI = 0x11, TLBLO0 = 0x12, TLBLO1 = 0x13,
    ASID = 0x18, PGDL = 0x19, PGDH = 0x1a, PGD = 0x1b,
    CPUID = 0x20, SAVE0 = 0x30, SAVE1 = 0x31, SAVE2 = 0x32,
    SAVE3 = 0x33, TID = 0x40, TCFG = 0x41, TVAL = 0x42, 
    TICLR = 0x44, LLBCTL = 0x60, TLBRENTRY = 0x88, CTAG = 0x98,
    DMW0 = 0x180, DMW1 = 0x181
};
#define CSR_NAME (int)CSRNAME

enum class CSRIDX{
    CRMD = 0x0, PRMD, EUEN, ECFG,
    ESTAT, ERA, BADV, EENTRY,
    TLBIDX, TLBEHI, TLBLO0, TLBLO1,
    ASID, PGDL, PGDH, PGD,
    CPUID, SAVE0, SAVE1, SAVE2,
    SAVE3, TID, TCFG, TVAL,
    TICLR, LLBCTL, TLBRENTRY, CTAG,
    DMW0, DMW1
};

#define CSR_IDX (int)CSRIDX

typedef struct {
    uint32_t vppn;
    uint32_t ps;
    bool g;
    uint32_t asid;
    bool e;
    uint32_t ppn0;
    uint32_t plv0;
    uint32_t mat0;
    bool d0;
    bool v0;
    uint32_t ppn1;
    uint32_t plv1;
    uint32_t mat1;
    bool d1;
    bool v1;
}TLB_Entry;

struct CPU_State{
    uint32_t reg[32];
    uint32_t pc;
    uint32_t csr[30];
    TLB_Entry tlb[TLB_SIZE];
    uint64_t stable_counter;
    int state;
    uint32_t halt_pc;
    uint32_t inst;
    bool timer_int;
    uint32_t timer_past;
    // update state
    void update_state(){
        // stable counter
        stable_counter++;
        // interrupt 
        csr[CSR_IDX::ESTAT] = (csr[CSR_IDX::ESTAT] & 0xfffff7ff) | ((uint32_t)timer_int << 11);
#ifndef CONFIG_REF
        // timer int
        if(csr[CSR_IDX::TCFG] & 0x1){
            // check if timer int
            if(timer_past == 1 && csr[CSR_IDX::TVAL] == 0){
                // std::cout << "timer interrupt" << std::endl;
                timer_int = true;
            }
            // update timer
            timer_past = csr[CSR_IDX::TVAL];
            if(csr[CSR_IDX::TVAL] == 0){
                if(csr[CSR_IDX::TCFG] & 0x2){
                    // wrap
                    csr[CSR_IDX::TVAL] = (csr[CSR_IDX::TCFG] & 0xfffffffc) | 1;
                }
            }else{
                csr[CSR_IDX::TVAL]--;
            }
        }
        
#endif
    }
    // csr read
    inline uint32_t csr_read(uint32_t name){
        if(csr_map.find(name) == csr_map.end()){
            return 0;
        }
        return csr[csr_map[name]];
    }
    // csr write
    inline void csr_write(uint32_t name, uint32_t val){
        if(csr_map.find(name) == csr_map.end()){
            return;
        }
        csr[csr_map[name]] = (csr[csr_map[name]] & ~csr_mask[name]) | (val & csr_mask[name]);
        if(name == CSR_NAME::TCFG){
            csr[CSR_IDX::TVAL] = (val & 0xfffffffc) | 1;
        }
        if(name == CSR_NAME::TICLR){
            timer_int = false;   
        }
    }

};



#endif // __ARCH_H__