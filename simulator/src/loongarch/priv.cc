#include <cpu.h>
#include <common.h>
#include <paddr.h>
#include <mmu.h>
#define R(i) cpu.reg[i]
#define CSR(i) cpu.csr[i]

uint32_t do_exception(uint32_t ecode, uint32_t vaddr){
    // set PLV and IE in PRMD to those in CRMD
    CSR(CSR_IDX::PRMD) = CSR(CSR_IDX::CRMD) & 0x7;
    // set PLV to 0 and set IE to 0
    CSR(CSR_IDX::CRMD) &= 0xfffffff8;
    // tlbr: set da = 1, pg = 0
    if(ecode == 0x3f){
        CSR(CSR_IDX::CRMD) = (CSR(CSR_IDX::CRMD) & 0xffffffe7) | 0x8;
    }
    // set ecode to ESTAT
    CSR(CSR_IDX::ESTAT) = (0x7fff0000 & (ecode << 16)) | (~0x7fff0000 & CSR(CSR_IDX::ESTAT));
    // set era to pc
    CSR(CSR_IDX::ERA) = cpu.pc;
    // set badv
    if(ecode == 0x8){
        CSR(CSR_IDX::BADV) = cpu.pc;
    }
    else if(ecode == 0x9 || ecode == 0x3f || (ecode >= 0x1 && ecode <= 0x4) || ecode == 0x7){
        CSR(CSR_IDX::BADV) = vaddr;
    }
    // set vppn to TLBEHI
    if(ecode == 0x3f || (ecode >= 0x1 && ecode <= 0x4) || ecode == 0x7){
        cpu.csr_write(CSR_NAME::TLBEHI, vaddr);
    }
    return ecode == 0x3f ? CSR(CSR_IDX::TLBRENTRY) : CSR(CSR_IDX::EENTRY);
}

uint32_t do_ertn(){
    // recover CRMD
    // std::cout << std::hex << "ertn" << std::endl;
    CSR(CSR_IDX::CRMD) = (CSR(CSR_IDX::CRMD) & 0xfffffff8) | (CSR(CSR_IDX::PRMD) & 0x7);
    if(BITS(CSR(CSR_IDX::ESTAT), 21, 16) == 0x3f){
        CSR(CSR_IDX::CRMD) = (CSR(CSR_IDX::CRMD) & 0xffffffe7) | 0x10;
    }
    if(BITS(CSR(CSR_IDX::LLBCTL), 2, 2) == 0){
        CSR(CSR_IDX::LLBCTL) &= 0xfffffffe;
    }
    CSR(CSR_IDX::LLBCTL) &= 0xfffffffb;
    return CSR(CSR_IDX::ERA);
}