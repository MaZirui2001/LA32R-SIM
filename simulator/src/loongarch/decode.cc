#include <cpu.h>
#include <common.h>
#include <paddr.h>
#include <mmu.h>
#include <random>
#include <priv.h>

#define R(i) cpu.reg[i]
#define CSR(i) cpu.csr[i]

#define INST_MATCH(opcode, mask, type, name, ...) {\
    if(((opcode ^ inst) & mask) == 0){ \
       decode_oprand(inst, type, rd, src1, src2, dst, imm); \
        __VA_ARGS__ ; \
       goto finish; \
    } \
} 
enum {
    TYPE_2R, TYPE_3R, TYPE_4R, 
    TYPE_2RI8, TYPE_2RI12, TYPE_2RI14, TYPE_2RI16, TYPE_1RI21, 
    TYPE_I26
};
void decode_oprand(uint32_t inst, int type, uint32_t &rd, uint32_t &src1, uint32_t &src2, uint32_t &dst, uint32_t &imm){
    int rj = BITS(inst, 9, 5);
    int rk = BITS(inst, 14, 10);
    // int ra = BITS(inst, 19, 15);
    rd = BITS(inst, 4, 0);

    src1 = R(rj);
    src2 = R(rk);
    dst = R(rd);

    switch(type){
        case TYPE_2R:    imm = 0; break;
        case TYPE_3R:    imm = 0; break;
        case TYPE_4R:    imm = 0; break;
        case TYPE_2RI8:  imm = SBITS(inst, 17, 10); break;
        case TYPE_2RI12: imm = SBITS(inst, 21, 10); break;
        case TYPE_2RI14: imm = SBITS(inst, 23, 10) << 2; break;
        case TYPE_2RI16: imm = SBITS(inst, 25, 10); break;
        case TYPE_1RI21: imm = BITS(inst, 25, 10) | (SBITS(inst, 4, 0) << 16); break;
        case TYPE_I26:   imm = BITS(inst, 25, 10) | (SBITS(inst, 9, 0) << 16); break;
        default:         imm = 0; break;
    }

}

void decode_exec(uint32_t inst, uint32_t exception_fetch){
    uint32_t rd = 0;
    uint32_t rj = BITS(inst, 9, 5);
    uint32_t src1 = 0;
    uint32_t src2 = 0;
    uint32_t imm = 0;
    uint32_t dst = 0;
    uint32_t csr_rd = BITS(inst, 18, 10); //reduce
    uint32_t npc = cpu.pc + 4;
    bool with_exp = false;
    if(cpu.idle_state){
        npc = cpu.pc;
        goto finish;
    }
    
    if(exception_fetch != 0){
        npc = do_exception(exception_fetch, cpu.pc);
        goto finish;
    }
    
#ifndef CONFIG_REF
    if((cpu.csr[CSR_IDX::ESTAT] & cpu.csr[CSR_IDX::ECFG] & 0x1fff) && (cpu.csr[CSR_IDX::CRMD] & 0x4)){
        with_exp = true;
    }
#endif
    //INST_MATCH(0x80000000, 0xffffffff, TYPE_2R,   TRAP,         cpu.state = SIM_END; cpu.halt_pc = cpu.pc; printf("ok\n"))
    INST_MATCH(0x00006000, 0xfffffc1f, TYPE_2R,    RDCNTID.W,    R(rj) = CSR(CSR_IDX::TID))
    INST_MATCH(0x00006000, 0xffffffe0, TYPE_2R,    RDCNTVL.W,    R(rd) = cpu.stable_counter & 0xffffffff)
    INST_MATCH(0x00006400, 0xffffffe0, TYPE_2R,    RDCNTVH.W,    R(rd) = cpu.stable_counter >> 32)
    INST_MATCH(0x00100000, 0xffff8000, TYPE_3R,    ADD.W,        R(rd) = src1 + src2) 
    INST_MATCH(0x00110000, 0xffff8000, TYPE_3R,    SUB.W,        R(rd) = src1 - src2) 
    INST_MATCH(0x00120000, 0xffff8000, TYPE_3R,    SLT,          R(rd) = (int32_t)src1 < (int32_t)src2)
    INST_MATCH(0x00128000, 0xffff8000, TYPE_3R,    SLTU,         R(rd) = src1 < src2)
    INST_MATCH(0x00140000, 0xffff8000, TYPE_3R,    NOR,          R(rd) = ~(src1 | src2))
    INST_MATCH(0x00148000, 0xffff8000, TYPE_3R,    AND,          R(rd) = src1 & src2)
    INST_MATCH(0x00150000, 0xffff8000, TYPE_3R,    OR,           R(rd) = src1 | src2)
    INST_MATCH(0x00158000, 0xffff8000, TYPE_3R,    XOR,          R(rd) = src1 ^ src2)
    INST_MATCH(0x00170000, 0xffff8000, TYPE_3R,    SLL.W,        R(rd) = src1 << src2)
    INST_MATCH(0x00178000, 0xffff8000, TYPE_3R,    SRL.W,        R(rd) = src1 >> src2)
    INST_MATCH(0x00180000, 0xffff8000, TYPE_3R,    SRA.W,        R(rd) = (int32_t)src1 >> src2)
    INST_MATCH(0x001c0000, 0xffff8000, TYPE_3R,    MUL.W,        R(rd) = (int32_t)src1 * (int32_t)src2)
    INST_MATCH(0x001c8000, 0xffff8000, TYPE_3R,    MULH.W,       R(rd) = ((int64_t)(int32_t)src1 * (int64_t)(int32_t)src2) >> 32)
    INST_MATCH(0x001d0000, 0xffff8000, TYPE_3R,    MULH.WU,      R(rd) = ((uint64_t)src1 * (uint64_t)src2) >> 32)
    INST_MATCH(0x00200000, 0xffff8000, TYPE_3R,    DIV.W,        R(rd) = (int32_t)src1 / (int32_t)src2)
    INST_MATCH(0x00208000, 0xffff8000, TYPE_3R,    MOD.W,        R(rd) = (int32_t)src1 % (int32_t)src2)
    INST_MATCH(0x00210000, 0xffff8000, TYPE_3R,    DIV.WU,       R(rd) = src1 / src2)
    INST_MATCH(0x00218000, 0xffff8000, TYPE_3R,    MOD.WU,       R(rd) = src1 % src2)
    INST_MATCH(0x002a0000, 0xffff8000, TYPE_3R,    BREAK,        npc = do_exception(BRK, 0x0))
    INST_MATCH(0x002b0000, 0xffff8000, TYPE_3R,    SYSCALL,      npc = do_exception(SYS, 0x0))
    INST_MATCH(0x00408000, 0xffff8000, TYPE_2RI8,  SLLI.W,       R(rd) = src1 << BITS(imm, 4, 0))
    INST_MATCH(0x00448000, 0xffff8000, TYPE_2RI8,  SRLI.W,       R(rd) = src1 >> BITS(imm, 4, 0))
    INST_MATCH(0x00488000, 0xffff8000, TYPE_2RI8,  SRAI.W,       R(rd) = (int32_t)src1 >> BITS(imm, 4, 0))
    INST_MATCH(0x02000000, 0xffc00000, TYPE_2RI12, SLTI,         R(rd) = (int32_t)src1 < (int32_t)imm)
    INST_MATCH(0x02400000, 0xffc00000, TYPE_2RI12, SLTUI,        R(rd) = src1 < imm)
    INST_MATCH(0x02800000, 0xffc00000, TYPE_2RI12, ADDI.W,       R(rd) = src1 + imm)
    INST_MATCH(0x03400000, 0xffc00000, TYPE_2RI12, ANDI,         R(rd) = src1 & BITS(imm, 11, 0))
    INST_MATCH(0x03800000, 0xffc00000, TYPE_2RI12, ORI,          R(rd) = src1 | BITS(imm, 11, 0))
    INST_MATCH(0x03c00000, 0xffc00000, TYPE_2RI12, XORI,         R(rd) = src1 ^ BITS(imm, 11, 0)) 
    INST_MATCH(0x04000000, 0xff0003e0, TYPE_2RI12, CSRRD,        R(rd) = cpu.csr_read(csr_rd))
    INST_MATCH(0x04000020, 0xff0003e0, TYPE_2RI12, CSRWR,        R(rd) = cpu.csr_read(csr_rd); cpu.csr_write(csr_rd, dst))
    INST_MATCH(0x04000000, 0xff000000, TYPE_2RI12, CSRXCHG,      R(rd) = cpu.csr_read(csr_rd); cpu.csr_write(csr_rd, (dst & src1) | (cpu.csr_read(csr_rd) & ~src1)); )
    INST_MATCH(0x06000000, 0xffc00000, TYPE_2RI12, CACOP,        if(BITS(inst, 4, 3) == 0x2) {uint32_t vaddr = src1 + imm; auto addr_pair = vaddr_check(vaddr, 0x0, 0x2); if(addr_pair.second != 0) {npc = do_exception(addr_pair.second, vaddr);}})
    INST_MATCH(0x06482800, 0xffffffff, TYPE_3R,    TLBSRCH,      tlb_srch())
    INST_MATCH(0x06482c00, 0xffffffff, TYPE_3R,    TLBRD,        tlb_read(BITS(CSR(CSR_IDX::TLBIDX), 3, 0)))
    INST_MATCH(0x06483000, 0xffffffff, TYPE_3R,    TLBWR,        tlb_write(BITS(CSR(CSR_IDX::TLBIDX), 3, 0)))
#ifndef CONFIG_REF
    INST_MATCH(0x06483400, 0xffffffff, TYPE_3R,    TLBFILL,      tlb_write(rand() % 16))
#else
    INST_MATCH(0x06483400, 0xffffffff, TYPE_3R,    TLBFILL,      )
#endif
    INST_MATCH(0x06483800, 0xffffffff, TYPE_3R,    ERTN,         npc = do_ertn())
    INST_MATCH(0x06488000, 0xffff8000, TYPE_3R,    IDLE,         cpu.idle_state = 1)
    INST_MATCH(0x06498000, 0xffff8000, TYPE_3R,    INVTLB,       if(!tlb_invalid(BITS(inst, 4, 0), src1, src2)){npc = do_exception(INE, 0x0);})
    INST_MATCH(0x14000000, 0xfe000000, TYPE_1RI21, LU12I.W,      R(rd) = BITS(inst, 24, 5) << 12)
    INST_MATCH(0x1c000000, 0xfe000000, TYPE_1RI21, PCADDU12I,    R(rd) = cpu.pc + (BITS(inst, 24, 5) << 12))
    INST_MATCH(0x20000000, 0xff000000, TYPE_2RI14, LL.W,         uint32_t vaddr = src1 + imm; auto addr_pair = vaddr_check(vaddr, 0x3, 0x2); if(addr_pair.second != 0){npc = do_exception(addr_pair.second, vaddr);} else {R(rd) = paddr_read(addr_pair.first, 4); CSR(CSR_IDX::LLBCTL) |= 1;})
    INST_MATCH(0x21000000, 0xff000000, TYPE_2RI14, SC.W,         if(BITS(CSR(CSR_IDX::LLBCTL), 0, 0)){uint32_t vaddr = src1 + imm; auto addr_pair = vaddr_check(vaddr, 0x3, 0x4); if(addr_pair.second != 0){npc = do_exception(addr_pair.second, vaddr);} else {paddr_write(addr_pair.first, dst, 4); R(rd) = 1; CSR(CSR_IDX::LLBCTL) &= 0xffffffe;}} else{R(rd) = 0;})
    INST_MATCH(0x28000000, 0xffc00000, TYPE_2RI12, LD.B,         uint32_t vaddr = src1 + imm; auto addr_pair = vaddr_check(vaddr, 0x0, 0x2); if(addr_pair.second != 0){npc = do_exception(addr_pair.second, vaddr);} else {R(rd) = SBITS(paddr_read(addr_pair.first, 1), 7, 0);})
    INST_MATCH(0x28400000, 0xffc00000, TYPE_2RI12, LD.H,         uint32_t vaddr = src1 + imm; auto addr_pair = vaddr_check(vaddr, 0x1, 0x2); if(addr_pair.second != 0){npc = do_exception(addr_pair.second, vaddr);} else {R(rd) = SBITS(paddr_read(addr_pair.first, 2), 15, 0);})
    INST_MATCH(0x28800000, 0xffc00000, TYPE_2RI12, LD.W,         uint32_t vaddr = src1 + imm; auto addr_pair = vaddr_check(vaddr, 0x3, 0x2); if(addr_pair.second != 0){npc = do_exception(addr_pair.second, vaddr);} else {R(rd) = paddr_read(addr_pair.first, 4);})
    INST_MATCH(0x29000000, 0xffc00000, TYPE_2RI12, ST.B,         uint32_t vaddr = src1 + imm; auto addr_pair = vaddr_check(vaddr, 0x0, 0x4); if(addr_pair.second != 0){npc = do_exception(addr_pair.second, vaddr);} else {paddr_write(addr_pair.first, BITS(dst, 7, 0), 1);})
    INST_MATCH(0x29400000, 0xffc00000, TYPE_2RI12, ST.H,         uint32_t vaddr = src1 + imm; auto addr_pair = vaddr_check(vaddr, 0x1, 0x4); if(addr_pair.second != 0){npc = do_exception(addr_pair.second, vaddr);} else {paddr_write(addr_pair.first, BITS(dst, 15, 0), 2);})
    INST_MATCH(0x29800000, 0xffc00000, TYPE_2RI12, ST.W,         uint32_t vaddr = src1 + imm; auto addr_pair = vaddr_check(vaddr, 0x3, 0x4); if(addr_pair.second != 0){npc = do_exception(addr_pair.second, vaddr);} else {paddr_write(addr_pair.first, dst, 4);})
    INST_MATCH(0x2a000000, 0xffc00000, TYPE_2RI12, LD.BU,        uint32_t vaddr = src1 + imm; auto addr_pair = vaddr_check(vaddr, 0x0, 0x2); if(addr_pair.second != 0){npc = do_exception(addr_pair.second, vaddr);} else {R(rd) = BITS(paddr_read(addr_pair.first, 1), 7, 0);})
    INST_MATCH(0x2a400000, 0xffc00000, TYPE_2RI12, LD.HU,        uint32_t vaddr = src1 + imm; auto addr_pair = vaddr_check(vaddr, 0x1, 0x2); if(addr_pair.second != 0){npc = do_exception(addr_pair.second, vaddr);} else {R(rd) = BITS(paddr_read(addr_pair.first, 2), 15, 0);})
    INST_MATCH(0x2ac00000, 0xffc00000, TYPE_2RI12, PRELD,        )
    INST_MATCH(0x38720000, 0xffff8000, TYPE_2RI12, DBAR,         )
    INST_MATCH(0x38728000, 0xffff8000, TYPE_2RI12, IBAR,         ) 
    INST_MATCH(0x4c000000, 0xfc000000, TYPE_2RI16, JIRL,         R(rd) = cpu.pc + 4; npc = src1 + (imm << 2))
    INST_MATCH(0x50000000, 0xfc000000, TYPE_I26,   B,            npc = cpu.pc + (imm << 2))
    INST_MATCH(0x54000000, 0xfc000000, TYPE_I26,   BL,           R(1) = cpu.pc + 4; npc = cpu.pc + (imm << 2))
    INST_MATCH(0x58000000, 0xfc000000, TYPE_2RI16, BEQ,          if(src1 == dst) npc = cpu.pc + (imm << 2))
    INST_MATCH(0x5c000000, 0xfc000000, TYPE_2RI16, BNE,          if(src1 != dst) npc = cpu.pc + (imm << 2))
    INST_MATCH(0x60000000, 0xfc000000, TYPE_2RI16, BLT,          if((int32_t)src1 < (int32_t)dst) npc = cpu.pc + (imm << 2))
    INST_MATCH(0x64000000, 0xfc000000, TYPE_2RI16, BGE,          if((int32_t)src1 >= (int32_t)dst) npc = cpu.pc + (imm << 2))
    INST_MATCH(0x68000000, 0xfc000000, TYPE_2RI16, BLTU,         if(src1 < dst) npc = cpu.pc + (imm << 2))
    INST_MATCH(0x6c000000, 0xfc000000, TYPE_2RI16, BGEU,         if(src1 >= dst) npc = cpu.pc + (imm << 2))

    npc = do_exception(INE, 0x0);

finish:
    R(0) = 0;
    cpu.update_state();
    if(with_exp){
        npc = do_exception(INT, 0x0);
    }
    cpu.pc = npc;
    return;
}

std::pair<uint32_t, uint32_t> inst_fetch(uint32_t pc){
    if(pc & 0x3){
        return std::make_pair(0x80000001, ADEF);
    }
    auto paddr = addr_translate(pc, 0x1);
    if(paddr.second != 0){
        return std::make_pair(0x80000001, paddr.second); 
    }
    return std::make_pair(paddr_read((uint32_t)paddr.first, 4), paddr.second);
}
