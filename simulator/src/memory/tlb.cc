#include <common.h>
#include <cmath>
#include <cpu.h>

uint32_t tlb_idx_width = (uint32_t)log2(TLB_SIZE);

uint64_t tlb_convert(uint32_t vaddr, uint32_t mem_type){
    uint32_t hit_idx = -1;
    uint32_t asid = BITS(cpu.csr[CSR_IDX::ASID], 9, 0);
    bool found_v = false;
    bool found_d = false;
    uint32_t found_plv = 0;
    uint32_t found_ps = 0;
    uint32_t found_ppn = 0;
    for(int i = 0; i < TLB_SIZE; i++){
        auto ps = cpu.tlb[i].ps;
        if(cpu.tlb[i].e && (cpu.tlb[i].g || cpu.tlb[i].asid == asid) && (cpu.tlb[i].vppn >> (ps - 12)) == BITS(vaddr, 31, ps+1)){
            hit_idx = i;
            break;
        }
    }
    if(hit_idx == -1){
        return ((uint64_t)0x3f << 32) | vaddr;
    }else{
        auto tlb_entry = cpu.tlb[hit_idx];
        found_ps = tlb_entry.ps;
        if(BITS(vaddr, found_ps, found_ps)== 0){
            found_v = tlb_entry.v0;
            found_d = tlb_entry.d0;
            found_plv = tlb_entry.plv0;
            found_ppn = tlb_entry.ppn0;
        }else{
            found_v = tlb_entry.v1;
            found_d = tlb_entry.d1;
            found_plv = tlb_entry.plv1;
            found_ppn = tlb_entry.ppn1;
        }
    }
    if(found_v == 0){
        switch(mem_type){
            case(0x1): return ((uint64_t)0x3 << 32) | vaddr; // PIF
            case(0x2): return ((uint64_t)0x1 << 32) | vaddr; // PIL
            case(0x4): return ((uint64_t)0x2 << 32) | vaddr; // PIS
            default: return (uint64_t)vaddr;
        }
    }
    if(BITS(cpu.csr[CSR_IDX::CRMD], 1, 0) > found_plv){
        return (uint64_t)0x7 << 32 | vaddr; // PPI
    }
    if(mem_type == 0x4 && !found_d){
        return (uint64_t)0x4 << 32 | vaddr; // PME
    }
    return (BITS(found_ppn, 19, found_ps-12) << (found_ps-12)) | BITS(vaddr, found_ps-1, 0);

}

void tlb_read(uint32_t idx){
    auto tlb_entry = cpu.tlb[idx];
    bool e = tlb_entry.e;
    if(e){
        cpu.csr[CSR_IDX::ASID] = tlb_entry.asid;
        cpu.csr[CSR_IDX::TLBEHI] = (tlb_entry.vppn << 13);
        cpu.csr[CSR_IDX::TLBLO0] = (tlb_entry.ppn0 << 8) | ((uint32_t)(tlb_entry.g) << 6) 
                                                          | (tlb_entry.mat0 << 4) 
                                                          | (tlb_entry.plv0 << 2)
                                                          | ((uint32_t)(tlb_entry.d0) << 1)
                                                          | ((uint32_t)(tlb_entry.v0));
        cpu.csr[CSR_IDX::TLBLO1] = (tlb_entry.ppn1 << 8) | ((uint32_t)(tlb_entry.g) << 6)
                                                          | (tlb_entry.mat1 << 4)
                                                          | (tlb_entry.plv1 << 2)
                                                          | ((uint32_t)(tlb_entry.d1) << 1)
                                                          | ((uint32_t)(tlb_entry.v1));
        cpu.csr[CSR_IDX::TLBIDX] = (cpu.csr[CSR_IDX::TLBIDX] & ~0xbf000000) | ((tlb_entry.ps << 24) & 0xbf000000);
    }
    else{
        cpu.csr[CSR_IDX::ASID] = 0;
        cpu.csr[CSR_IDX::TLBEHI] = 0;
        cpu.csr[CSR_IDX::TLBLO0] = 0;
        cpu.csr[CSR_IDX::TLBLO1] = 0;
        cpu.csr[CSR_IDX::TLBIDX] = (cpu.csr[CSR_IDX::TLBIDX] & ~0xbf000000) | (0x80000000 & 0xbf000000);
    }

}
void tlb_write(uint32_t idx){
    // uint32_t idx = BITS(cpu.csr[CSR_IDX::TLBIDX], tlb_idx_width-1, 0);
    TLB_Entry tlb_entry;
    tlb_entry.vppn = BITS(cpu.csr[CSR_IDX::TLBEHI], 31, 13);
    tlb_entry.ps = BITS(cpu.csr[CSR_IDX::TLBIDX], 31, 24);
    tlb_entry.g = BITS(cpu.csr[CSR_IDX::TLBLO0], 6, 6) && BITS(cpu.csr[CSR_IDX::TLBLO1], 6, 6);
    tlb_entry.asid = BITS(cpu.csr[CSR_IDX::ASID], 9, 0);
    tlb_entry.e = BITS(cpu.csr[CSR_IDX::ESTAT], 21, 16) == 0x3f ? true : !BITS(cpu.csr[CSR_IDX::TLBIDX], 31, 31);
    tlb_entry.ppn0 = BITS(cpu.csr[CSR_IDX::TLBLO0], 31, 8);
    tlb_entry.plv0 = BITS(cpu.csr[CSR_IDX::TLBLO0], 3, 2);
    tlb_entry.mat0 = BITS(cpu.csr[CSR_IDX::TLBLO0], 5, 4);
    tlb_entry.d0 = BITS(cpu.csr[CSR_IDX::TLBLO0], 1, 1);
    tlb_entry.v0 = BITS(cpu.csr[CSR_IDX::TLBLO0], 0, 0);
    tlb_entry.ppn1 = BITS(cpu.csr[CSR_IDX::TLBLO1], 31, 8);
    tlb_entry.plv1 = BITS(cpu.csr[CSR_IDX::TLBLO1], 3, 2);
    tlb_entry.mat1 = BITS(cpu.csr[CSR_IDX::TLBLO1], 5, 4);
    tlb_entry.d1 = BITS(cpu.csr[CSR_IDX::TLBLO1], 1, 1);
    tlb_entry.v1 = BITS(cpu.csr[CSR_IDX::TLBLO1], 0, 0);
    cpu.tlb[idx] = tlb_entry;
}
void tlb_srch(){
    uint32_t asid = BITS(cpu.csr[CSR_IDX::ASID], 9, 0);
    uint32_t vppn = BITS(cpu.csr[CSR_IDX::TLBEHI], 31, 13);

    uint32_t hit_idx = -1;
    for(uint32_t i = 0; i < TLB_SIZE; i++){
        if(cpu.tlb[i].e && (cpu.tlb[i].g || cpu.tlb[i].asid == asid) && cpu.tlb[i].vppn == vppn){
            hit_idx = i;
            break;
        }
    }
    if(hit_idx == -1){
        cpu.csr[CSR_IDX::TLBIDX] = (cpu.csr[CSR_IDX::TLBIDX] & ~0x80000000) | (0x80000000 & 0x80000000);
    }
    else{
        uint32_t mask = (TLB_SIZE - 1) | 0x80000000;
        cpu.csr[CSR_IDX::TLBIDX] = (cpu.csr[CSR_IDX::TLBIDX] & ~mask) | (hit_idx & mask);
    }
}
bool tlb_invalid(uint32_t op, uint32_t asid, uint32_t va){
    switch(op){
        case(0x0):
        case(0x1):{
            // clear all TLB entries
            for(uint32_t i = 0; i < TLB_SIZE; i++){
                cpu.tlb[i].e = false;
            }
            return true;
        }
        case(0x2):{
            // clear TLB entry whose g = 1
            for(uint32_t i = 0; i < TLB_SIZE; i++){
                if(cpu.tlb[i].g){
                    cpu.tlb[i].e = false;
                }
            }
            return true;
        }
        case(0x3):{
            // clear TLB entry whose g = 0
            for(uint32_t i = 0; i < TLB_SIZE; i++){
                if(!cpu.tlb[i].g){
                    cpu.tlb[i].e = false;
                }
            }
            return true;
        }
        case(0x4):{
            // clear TLB entry whose asid = asid and g = 0
            for(uint32_t i = 0; i < TLB_SIZE; i++){
                if(cpu.tlb[i].asid == asid && !cpu.tlb[i].g){
                    cpu.tlb[i].e = false;
                }
            }
            return true;
        }
        case(0x5):{
            // clear TLB entry whose asid = asid and g = 0 and va[31:13] = va[31:13]
            for(uint32_t i = 0; i < TLB_SIZE; i++){
                if(cpu.tlb[i].asid == asid && !cpu.tlb[i].g && cpu.tlb[i].vppn == BITS(va, 31, 13)){
                    cpu.tlb[i].e = false;
                }
            }
            return true;
        }
        case(0x6):{
            // clear TLB entry whose asid = asid or g = 1,  and va[31:22] = va[31:22]
            for(uint32_t i = 0; i < TLB_SIZE; i++){
                if((cpu.tlb[i].asid == asid || cpu.tlb[i].g) && cpu.tlb[i].vppn == BITS(va, 31, 13)){
                    cpu.tlb[i].e = false;
                }
            }
            return true;
        }
        default: {
            std::cout << "tlb_invalid: invalid op" << std::endl;
            return false;
        }
    }

}