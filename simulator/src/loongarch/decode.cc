#include <cpu.h>
#include <common.h>
#include <paddr.h>

#define R(i) cpu.reg[i]

#define INST_MATCH(opcode, mask, type, ...) {\
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
        case TYPE_2RI14: imm = SBITS(inst, 23, 10); break;
        case TYPE_2RI16: imm = SBITS(inst, 25, 10); break;
        case TYPE_1RI21: imm = BITS(inst, 25, 10) | (SBITS(inst, 4, 0) << 16); break;
        case TYPE_I26:   imm = BITS(inst, 25, 10) | (SBITS(inst, 9, 0) << 16); break;
        default:         imm = 0; break;
    }

}

void decode_exec(uint32_t inst){
    uint32_t rd = 0;
    uint32_t src1 = 0;
    uint32_t src2 = 0;
    uint32_t imm = 0;
    uint32_t dst = 0;
    uint32_t npc = cpu.pc + 4;
    // ADD.W
    INST_MATCH(0x00100000, 0xffff8000, TYPE_3R, R(rd) = src1 + src2) 
    // SUB.W
    INST_MATCH(0x00110000, 0xffff8000, TYPE_3R, R(rd) = src1 - src2) 
    // SLT
    INST_MATCH(0x00120000, 0xffff8000, TYPE_3R, R(rd) = (int32_t)src1 < (int32_t)src2)
    // SLTU
    INST_MATCH(0x00128000, 0xffff8000, TYPE_3R, R(rd) = src1 < src2)
    // NOR
    INST_MATCH(0x00140000, 0xffff8000, TYPE_3R, R(rd) = ~(src1 | src2))
    // AND
    INST_MATCH(0x00148000, 0xffff8000, TYPE_3R, R(rd) = src1 & src2)
    // OR
    INST_MATCH(0x00150000, 0xffff8000, TYPE_3R, R(rd) = src1 | src2)
    // XOR
    INST_MATCH(0x00158000, 0xffff8000, TYPE_3R, R(rd) = src1 ^ src2)
    // SLL.W
    INST_MATCH(0x00170000, 0xffff8000, TYPE_3R, R(rd) = src1 << src2)
    // SRL.W
    INST_MATCH(0x00178000, 0xffff8000, TYPE_3R, R(rd) = src1 >> src2)
    // SRA.W
    INST_MATCH(0x00180000, 0xffff8000, TYPE_3R, R(rd) = (int32_t)src1 >> src2)
    // MUL.W
    INST_MATCH(0x001c0000, 0xffff8000, TYPE_3R, R(rd) = (int32_t)src1 * (int32_t)src2)
    // MULH.W
    INST_MATCH(0x001c8000, 0xffff8000, TYPE_3R, R(rd) = ((int64_t)(int32_t)src1 * (int64_t)(int32_t)src2) >> 32)
    // MULHU.W
    INST_MATCH(0x001d0000, 0xffff8000, TYPE_3R, R(rd) = ((uint64_t)src1 * (uint64_t)src2) >> 32)
    // DIV.W
    INST_MATCH(0x00200000, 0xffff8000, TYPE_3R, R(rd) = (int32_t)src1 / (int32_t)src2)
    // MOD.W
    INST_MATCH(0x00208000, 0xffff8000, TYPE_3R, R(rd) = (int32_t)src1 % (int32_t)src2)
    // DIV.WU
    INST_MATCH(0x00210000, 0xffff8000, TYPE_3R, R(rd) = src1 / src2)
    // MOD.WU
    INST_MATCH(0x00218000, 0xffff8000, TYPE_3R, R(rd) = src1 % src2)
    // BREAK
    INST_MATCH(0x002a0000, 0xffff8000, TYPE_3R, cpu.state = SIM_END; cpu.halt_pc = cpu.pc)
    // SYSCALL
    // INST_MATCH(0x002b0000, 0xffff8000, TYPE_3R, )
    // SLLI.W
    INST_MATCH(0x00408000, 0xffff8000, TYPE_2RI8, R(rd) = src1 << BITS(imm, 4, 0))
    // SRLI.W
    INST_MATCH(0x00448000, 0xffff8000, TYPE_2RI8, R(rd) = src1 >> BITS(imm, 4, 0))
    // SRAI.W
    INST_MATCH(0x00488000, 0xffff8000, TYPE_2RI8, R(rd) = (int32_t)src1 >> BITS(imm, 4, 0))
    // SLTI
    INST_MATCH(0x02000000, 0xffc00000, TYPE_2RI12, R(rd) = (int32_t)src1 < (int32_t)imm)
    // SLTUI
    INST_MATCH(0x02400000, 0xffc00000, TYPE_2RI12, R(rd) = src1 < imm)
    // ADDI.W
    INST_MATCH(0x02800000, 0xffc00000, TYPE_2RI12, R(rd) = src1 + imm)
    // ANDI.W
    INST_MATCH(0x03400000, 0xffc00000, TYPE_2RI12, R(rd) = src1 & BITS(imm, 11, 0))
    // ORI.W
    INST_MATCH(0x03800000, 0xffc00000, TYPE_2RI12, R(rd) = src1 | BITS(imm, 11, 0))
    // XORI.W
    INST_MATCH(0x03c00000, 0xffc00000, TYPE_2RI12, R(rd) = src1 ^ BITS(imm, 11, 0))
    // LU12I.W
    INST_MATCH(0x14000000, 0xfe000000, TYPE_1RI21, R(rd) = BITS(inst, 24, 5) << 12)
    // PCADDU12I
    INST_MATCH(0x1c000000, 0xfe000000, TYPE_1RI21, R(rd) = cpu.pc + (BITS(inst, 24, 5) << 12))
    // LD.B
    INST_MATCH(0x28000000, 0xffc00000, TYPE_2RI12, R(rd) = SBITS(paddr_read(src1 + imm, 1), 7, 0))
    // LD.H
    INST_MATCH(0x28400000, 0xffc00000, TYPE_2RI12, R(rd) = SBITS(paddr_read(src1 + imm, 2), 15, 0))
    // LD.W
    INST_MATCH(0x28800000, 0xffc00000, TYPE_2RI12, R(rd) = paddr_read(src1 + imm, 4);)
    // ST.B
    INST_MATCH(0x29000000, 0xffc00000, TYPE_2RI12, paddr_write(src1 + imm, BITS(dst, 7, 0), 1))
    // ST.H
    INST_MATCH(0x29400000, 0xffc00000, TYPE_2RI12, paddr_write(src1 + imm, BITS(dst, 15, 0), 2))
    // ST.W
    INST_MATCH(0x29800000, 0xffc00000, TYPE_2RI12, paddr_write(src1 + imm, dst, 4))
    // LD.BU
    INST_MATCH(0x2a000000, 0xffc00000, TYPE_2RI12, R(rd) = BITS(paddr_read(src1 + imm, 1), 7, 0))
    // LD.HU
    INST_MATCH(0x2a400000, 0xffc00000, TYPE_2RI12, R(rd) = BITS(paddr_read(src1 + imm, 2), 15, 0))
    // PRELD
    // INST_MATCH(0x2a800000, 0xffc00000, TYPE_2RI12, )
    // DBAR
    // INST_MATCH(0x2b000000, 0xffc00000, TYPE_2RI12, )
    // IBAR
    // INST_MATCH(0x2b400000, 0xffc00000, TYPE_2RI12, )
    // JIRL
    INST_MATCH(0x4c000000, 0xfc000000, TYPE_2RI16, R(rd) = cpu.pc + 4; npc = src1 + (imm << 2))
    // B
    INST_MATCH(0x50000000, 0xfc000000, TYPE_I26, npc = cpu.pc + (imm << 2))
    // BL
    INST_MATCH(0x54000000, 0xfc000000, TYPE_I26, R(1) = cpu.pc + 4; npc = cpu.pc + (imm << 2))
    // BEQ
    INST_MATCH(0x58000000, 0xfc000000, TYPE_2RI16, if(src1 == dst) npc = cpu.pc + (imm << 2))
    // BNE
    INST_MATCH(0x5c000000, 0xfc000000, TYPE_2RI16, if(src1 != dst) npc = cpu.pc + (imm << 2))
    // BLT
    INST_MATCH(0x60000000, 0xfc000000, TYPE_2RI16, if((int32_t)src1 < (int32_t)dst) npc = cpu.pc + (imm << 2))
    // BGE
    INST_MATCH(0x64000000, 0xfc000000, TYPE_2RI16, if((int32_t)src1 >= (int32_t)dst) npc = cpu.pc + (imm << 2))
    // BLTU
    INST_MATCH(0x68000000, 0xfc000000, TYPE_2RI16, if(src1 < dst) npc = cpu.pc + (imm << 2))
    // BGEU
    INST_MATCH(0x6c000000, 0xfc000000, TYPE_2RI16, if(src1 >= dst) npc = cpu.pc + (imm << 2))

    

finish:
    R(0) = 0;
    cpu.pc = npc;
    return;
}

uint32_t inst_fetch(uint32_t pc){
    return paddr_read(pc, 4);
}
