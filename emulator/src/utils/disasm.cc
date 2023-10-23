#include <common.h>
#include <arch.h>

using namespace std;

bitset<32> inst_bit;


void disasm(char* buf, uint32_t inst, uint32_t _prd, uint32_t _prj, uint32_t _prk) {
    inst_bit = bitset<32> (inst);

    // register file
    const char *rd = reg_name[BITS(inst, 4, 0)];
    const char *rj = reg_name[BITS(inst, 9, 5)];
    const char *rk = reg_name[BITS(inst, 14, 10)];

    // predicate register file
    const char *prd = preg_name[_prd];
    const char *prj = preg_name[_prj];
    const char *prk = preg_name[_prk];

    if(inst_bit[31]){
        sprintf(buf, "%-16s", "unimp");
        return;
    }
    if(inst_bit[30]){
        switch(BITS(inst, 29, 26)){
            // jirl rd, rj, offs
            case 3: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "jirl", rd, prd, rj, prj, SBITS(inst, 25, 10) << 2); return;
            // b offs
            case 4: sprintf(buf, "%-12s %d", "b", (BITS(inst, 25, 10) | (SBITS(inst, 9, 0) << 16)) << 2); return;
            // bl offs
            case 5: sprintf(buf, "%-12s %d", "bl", (BITS(inst, 25, 10) | (SBITS(inst, 9, 0) << 16)) << 2); return;
            // beq rj, rd, offs
            case 6: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "beq", rj, prj, rd, prd, SBITS(inst, 25, 10) << 2); return;
            // bne rj, rd, offs
            case 7: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "bne", rj, prj, rd, prd, SBITS(inst, 25, 10) << 2); return;
            // blt rj, rd, offs
            case 8: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "blt", rj, prj, rd, prd, SBITS(inst, 25, 10) << 2); return;
            // bge rj, rd, offs
            case 9: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "bge", rj, prj, rd, prd, SBITS(inst, 25, 10) << 2); return;
            // bltu rj, rd, offs
            case 10: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "bltu", rj, prj, rd, prd, SBITS(inst, 25, 10) << 2); return;
            // bgeu rj, rd, offs
            case 11: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "bgeu", rj, prj, rd, prd, SBITS(inst, 25, 10) << 2); return;
            
            default: sprintf(buf, "%-16s", "unimp"); return;
        }
    }
    if(inst_bit[29]){
        if(inst_bit[28]){
            switch(BITS(inst, 27, 15)){
                // dbar hint
                case 0x10e4: sprintf(buf, "%-12s %d", "dbar", SBITS(inst, 14, 0)); return;
                // ibar
                case 0x10e5: sprintf(buf, "%-12s %d", "ibar", SBITS(inst, 14, 0)); return;

                default: sprintf(buf, "%-16s", "unimp"); return;
            }
        }
        else {
            if(!inst_bit[27]){
                // automatic
                sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", inst_bit[24] ? "sc.w" : "ll.w", rd, prd, rj, prj, SBITS(inst, 23, 10));
            }
            else{
                switch(BITS(inst, 26, 22)){
                    // ld.b rd, rj, si12
                    case 0: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "ld.b", rd, prd, rj, prj, SBITS(inst, 21, 10)); return;
                    // ld.h rd, rj, si12
                    case 1: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "ld.h", rd, prd, rj, prj, SBITS(inst, 21, 10)); return;
                    // ld.w rd, rj, si12
                    case 2: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "ld.w", rd, prd, rj, prj, SBITS(inst, 21, 10)); return;
                    // st.b rd, rj, si12
                    case 4: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "st.b", rd, prd, rj, prj, SBITS(inst, 21, 10)); return;
                    // st.h rd, rj, si12
                    case 5: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "st.h", rd, prd, rj, prj, SBITS(inst, 21, 10)); return;
                    // st.w rd, rj, si12
                    case 6: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "st.w", rd, prd, rj, prj, SBITS(inst, 21, 10)); return;
                    // ld.bu rd, rj, si12
                    case 8: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "ld.bu", rd, prd, rj, prj, SBITS(inst, 21, 10)); return;
                    // ld.hu rd, rj, si12
                    case 9: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "ld.hu", rd, prd, rj, prj, SBITS(inst, 21, 10)); return;
                    // preld hint, rj, si12
                    case 10: sprintf(buf, "%-12s %d, %-4s(%-4s), %d", "preld", BITS(inst, 4, 0), rj, prj, SBITS(inst, 21, 10)); return;

                    default: sprintf(buf, "%-16s", "unimp"); return;
                }
            }
        }
    }
    if(inst_bit[28]){
        switch(BITS(inst, 27, 25)){
            // lu12i.w rd, si20
            case 2: sprintf(buf, "%-12s %-4s(%-4s), %d", "lu12i.w", rd, prd, SBITS(inst, 24, 5)); return;
            // lui rd, si20
            case 6: sprintf(buf, "%-12s %-4s(%-4s), %d", "pcaddu12i", rd, prd, SBITS(inst, 24, 5)); return;
            default: sprintf(buf, "%-16s", "unimp"); return;
        }
    }
    if(inst_bit[27]){
        // float TODO
        sprintf(buf, "%-16s", "unimp");
        return;
    }
    if(inst_bit[26]){
        const char *csr;
        if(csr_name.find(BITS(inst, 19, 10)) != csr_name.end()){
            csr = csr_name[BITS(inst, 19, 10)];
        }
        else{
            sprintf(buf, "%-16s", "unimp");
            return;
        }
        if(BITS(inst, 25, 24) == 0){
            switch(BITS(inst, 9, 5)){
                // csrrd rd, csr
                case 0: sprintf(buf, "%-12s %-4s(%-4s), %s", "csrrd", rd, prd, csr); return;
                // csrrw rd, csr
                case 1: sprintf(buf, "%-12s %-4s(%-4s), %s", "csrrw", rd, prd, csr); return;
                // csrxchg rd, rj, csr
                default: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %s", "csrxchg", rd, prd, rj, prj, csr); return;
            }
        }
        else if(BITS(inst, 25, 24) == 2){
            if(BITS(inst, 23, 22) == 0) {
                // cacop code, rj, si12
                sprintf(buf, "%-12s %d, %-4s(%-4s), %d", "cacop", BITS(inst, 4, 0), rj, prj, BITS(inst, 21, 10));
            }
            else if(BITS(inst, 23, 22) == 1){
                if(BITS(inst, 21, 17) != 0x04){
                    sprintf(buf, "%-16s", "unimp");
                }
                else{
                    if(BITS(inst, 16, 15) == 3){
                        // invtlb op, rj, rk
                        sprintf(buf, "%-12s %d, %-4s(%-4s), %-4s(%-4s)", "invtlb", BITS(inst, 4, 0), rj, prj, rk, prk);
                    }
                    else if(BITS(inst, 16, 15) == 1){
                        // idle level
                        sprintf(buf, "%-12s %d", "idle", BITS(inst, 14, 0));
                    }
                    else if(BITS(inst, 16, 15) == 0){
                        switch(BITS(inst, 14, 10)){
                            case 0xa: {
                                if(BITS(inst, 9, 0) != 0) sprintf(buf, "%-16s", "unimp");
                                // tlbsearch
                                else sprintf(buf, "%-12s", "tlbsearch");
                            }
                            case 0xb: {
                                if(BITS(inst, 9, 0) != 0) sprintf(buf, "%-16s", "unimp");
                                // tlbrd
                                else sprintf(buf, "%-12s", "tlbrd");
                            }
                            case 0xc: {
                                if(BITS(inst, 9, 0) != 0) sprintf(buf, "%-16s", "unimp");
                                // tlbwr
                                else sprintf(buf, "%-12s", "tlbwr");
                            }
                            case 0xd: {
                                if(BITS(inst, 9, 0) != 0) sprintf(buf, "%-16s", "unimp");
                                // tlbfill
                                else sprintf(buf, "%-12s", "tlbfill");
                            }
                            case 0xe: {
                                if(BITS(inst, 9, 0) != 0) sprintf(buf, "%-16s", "unimp");
                                // ertn
                                else sprintf(buf, "%-12s", "ertn");
                            }
                            default: sprintf(buf, "%-16s", "unimp");
                        }
                    }
                    else {
                        sprintf(buf, "%-16s", "unimp");
                    }
                }
            }
            else {
                sprintf(buf, "%-16s", "unimp");
            }
        }
        else {
            sprintf(buf, "%-16s", "unimp");
        }
    }
    if(inst_bit[25]){
        switch(BITS(inst, 24, 22)){
            // slti rd, rj, si12
            case 0: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "slti", rd, prd, rj, prj, SBITS(inst, 21, 10)); return;
            // sltui rd, rj, si12
            case 1: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "sltui", rd, prd, rj, prj, SBITS(inst, 21, 10)); return;
            // addi.w rd, rj, si12
            case 2: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "addi.w", rd, prd, rj, prj, SBITS(inst, 21, 10)); return;
            // andi rd, rj, si12
            case 5: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "andi", rd, prd, rj, prj, SBITS(inst, 21, 10)); return;
            // ori rd, rj, si12
            case 6: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "ori", rd, prd, rj, prj, SBITS(inst, 21, 10)); return;
            // xori rd, rj, si12
            case 7: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "xori", rd, prd, rj, prj, SBITS(inst, 21, 10)); return;

            default: sprintf(buf, "%-16s", "unimp"); return;
        }
    }
    if(inst_bit[24]){
        // float
        sprintf(buf, "%-16s", "unimp");
    }
    if(inst_bit[23]){
        // no legal
        sprintf(buf, "%-16s", "unimp");
    }
    if(inst_bit[22]){
        switch(BITS(inst, 21, 15)){
            // slli.w rd, rj, ui5
            case 0x1: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "slli.w", rd, prd, rj, prj, SBITS(inst, 14, 10)); return;
            // srli.w rd, rj, ui5
            case 0x9: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "srli.w", rd, prd, rj, prj, SBITS(inst, 14, 10)); return;
            // srai.w rd, rj, ui5
            case 0x11: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %d", "srai.w", rd, prd, rj, prj, SBITS(inst, 14, 10)); return;

            default: sprintf(buf, "%-16s", "unimp"); return;
        }
    }
    if(inst_bit[21]){
        switch(BITS(inst, 20, 15)){
            // div.w rd, rj, rk
            case 0x0: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %-4s(%-4s)", "div.w", rd, prd, rj, prj, rk, prk); return;
            // mod.w rd, rj, rk
            case 0x1: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %-4s(%-4s)", "mod.w", rd, prd, rj, prj, rk, prk); return;
            // div.wu rd, rj, rk
            case 0x2: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %-4s(%-4s)", "div.wu", rd, prd, rj, prj, rk, prk); return;
            // mod.wu rd, rj, rk
            case 0x3: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %-4s(%-4s)", "mod.wu", rd, prd, rj, prj, rk, prk); return;
            // break code
            case 0x14: sprintf(buf, "%-12s %d", "break", BITS(inst, 14, 0)); return;
            // syscall code
            case 0x15: sprintf(buf, "%-12s %d", "syscall", BITS(inst, 14, 0)); return;

            default: sprintf(buf, "%-16s", "unimp"); return;
        }
    }
    if(inst_bit[20]){
        switch(BITS(inst, 19, 15)){
            // add.w rd, rj, rk
            case 0x0: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %-4s(%-4s)", "add.w", rd, prd, rj, prj, rk, prk); return;
            // sub.w rd, rj, rk
            case 0x2: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %-4s(%-4s)", "sub.w", rd, prd, rj, prj, rk, prk); return;
            // slt rd, rj, rk
            case 0x4: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %-4s(%-4s)", "slt", rd, prd, rj, prj, rk, prk); return;
            // sltu rd, rj, rk
            case 0x5: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %-4s(%-4s)", "sltu", rd, prd, rj, prj, rk, prk); return;
            // nor rd, rj, rk
            case 0x8: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %-4s(%-4s)", "nor", rd, prd, rj, prj, rk, prk); return;
            // and rd, rj, rk
            case 0x9: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %-4s(%-4s)", "and", rd, prd, rj, prj, rk, prk); return;
            // or rd, rj, rk
            case 0xa: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %-4s(%-4s)", "or", rd, prd, rj, prj, rk, prk); return;
            // xor rd, rj, rk
            case 0xb: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %-4s(%-4s)", "xor", rd, prd, rj, prj, rk, prk); return;
            // sll.w rd, rj, rk
            case 0xe: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %-4s(%-4s)", "sll.w", rd, prd, rj, prj, rk, prk); return;
            // srl.w rd, rj, rk
            case 0xf: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %-4s(%-4s)", "srl.w", rd, prd, rj, prj, rk, prk); return;
            // sra.w rd, rj, rk
            case 0x10: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %-4s(%-4s)", "sra.w", rd, prd, rj, prj, rk, prk); return;
            // mul.w rd, rj, rk
            case 0x18: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %-4s(%-4s)", "mul.w", rd, prd, rj, prj, rk, prk); return;
            // mulh.w rd, rj, rk
            case 0x19: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %-4s(%-4s)", "mulh.w", rd, prd, rj, prj, rk, prk); return;
            // mulh.wu rd, rj, rk
            case 0x1a: sprintf(buf, "%-12s %-4s(%-4s), %-4s(%-4s), %-4s(%-4s)", "mulh.wu", rd, prd, rj, prj, rk, prk); return;

            default: sprintf(buf, "%-16s", "unimp"); return;
        }
    }
    if(inst_bit[19] || inst_bit[18] || inst_bit[17] || inst_bit[16] || inst_bit[15]){
        sprintf(buf, "%-16s", "unimp");
        return;
    }
    if(BITS(inst, 14, 13) == 3){
        switch(BITS(inst, 12, 10)){
            // rdcntid.w rj or rdcntvl.w rd
            case 0: sprintf(buf, "%-12s %-4s(%-4s)", BITS(inst, 4, 0) != 0 ? "rdcntvl.w" : "rdcntid.w", BITS(inst, 4, 0) != 0 ? rd : rj, BITS(inst, 4, 0) != 0 ? prd : prj); return;
            // rdcntvh.w rd
            case 1: sprintf(buf, "%-12s %-4s(%-4s)", "rdcntvh.w", rd, prd); return;
        }
    }
    else {
        sprintf(buf, "%-16s", "unimp");
        return;
    }
}
// int main(){
//     uint32_t inst;
//     char buf[100];
//     ifstream fin("../../test/test", ios::binary);
//     ofstream four("./result");
//     while(!fin.eof()){
//         fin.read((char*)&inst, sizeof(inst));
//         disasm(buf, inst);
//         four << buf << endl;
//     }
//     return 0;
// }
    