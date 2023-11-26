#ifndef __ARCH_H__
#define __ARCH_H__


#include <unordered_map>
#include <config.h>
#include <stdint.h>

// loongarch reg name
extern const char* reg_name[32];
// loongarch csr name 
extern std::unordered_map<unsigned int, const char*> csr_name;
#define RESET_VECTOR CONFIG_PMEM_BASE
#define REG_SIZE  (32 + 1)

typedef struct {
    uint32_t reg[32];
    uint32_t pc;
    uint32_t csr[512];
    uint64_t stable_counter;
    int state;
    uint32_t halt_pc;
    uint32_t inst;
} CPU_State;

enum CSR_NAME{
    CRMD = 0x0, PRMD = 0x1, EUEN = 0x2, ECFG = 0x4, 
    ESTAT = 0x5, ERA = 0x6, BADV = 0x7, EENTRY = 0xc,
    TLBIDX = 0x10, TLBEHI = 0x11, TLBLO0 = 0x12, TLBLO1 = 0x13,
    ASID = 0x18, PGDL = 0x19, PGDH = 0x1a, PGD = 0x1b,
    CPUID = 0x20, SAVE0 = 0x30, SAVE1 = 0x31, SAVE2 = 0x32,
    SAVE3 = 0x33, TID = 0x40, TCFG = 0x41, TVAL = 0x42, 
    TICLR = 0x44, LLBCTL = 0x60, TLBRENTRY = 0x88, CTAG = 0x98,
    DMW0 = 0x180, DMW1 = 0x181
};
#endif // __ARCH_H__