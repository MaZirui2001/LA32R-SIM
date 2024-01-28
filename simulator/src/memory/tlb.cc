#include <common.h>
#include <cmath>
#include <cpu.h>

uint32_t tlb_idx_width = (uint32_t)log2(TLB_SIZE);

void tlb_read(uint32_t idx){
    auto tlb_entry = cpu.tlb[idx];
    bool e = tlb_entry.e;
    if(e){
        cpu.csr[CSR_NAME::ASID] = tlb_entry.asid;
        cpu.csr[CSR_NAME::TLBEHI] = (tlb_entry.vppn << 13);
        cpu.csr[CSR_NAME::TLBLO0] = (tlb_entry.ppn0 << 8) | ((uint32_t)(tlb_entry.g) << 6) 
                                                          | (tlb_entry.mat0 << 4) 
                                                          | (tlb_entry.plv0 << 2)
                                                          | ((uint32_t)(tlb_entry.d0) << 1)
                                                          | ((uint32_t)(tlb_entry.v0));
        cpu.csr[CSR_NAME::TLBLO1] = (tlb_entry.ppn1 << 8) | ((uint32_t)(tlb_entry.g) << 6)
                                                          | (tlb_entry.mat1 << 4)
                                                          | (tlb_entry.plv1 << 2)
                                                          | ((uint32_t)(tlb_entry.d1) << 1)
                                                          | ((uint32_t)(tlb_entry.v1));
        cpu.csr[CSR_NAME::TLBIDX] = (cpu.csr[CSR_NAME::TLBIDX] & ~0xbf000000) | ((tlb_entry.ps << 24) & 0xbf000000);
    }
    else{
        cpu.csr[CSR_NAME::ASID] = 0;
        cpu.csr[CSR_NAME::TLBEHI] = 0;
        cpu.csr[CSR_NAME::TLBLO0] = 0;
        cpu.csr[CSR_NAME::TLBLO1] = 0;
        cpu.csr[CSR_NAME::TLBIDX] = (cpu.csr[CSR_NAME::TLBIDX] & ~0xbf000000) | (0x80000000 & 0xbf000000);
    }

}
void tlb_write(uint32_t idx){
    // uint32_t idx = BITS(cpu.csr[CSR_NAME::TLBIDX], tlb_idx_width-1, 0);
    TLB_Entry tlb_entry;
    tlb_entry.vppn = BITS(cpu.csr[CSR_NAME::TLBEHI], 31, 13);
    tlb_entry.ps = BITS(cpu.csr[CSR_NAME::TLBIDX], 31, 24);
    tlb_entry.g = BITS(cpu.csr[CSR_NAME::TLBLO0], 6, 6) && BITS(cpu.csr[CSR_NAME::TLBLO1], 6, 6);
    tlb_entry.asid = BITS(cpu.csr[CSR_NAME::ASID], 9, 0);
    tlb_entry.e = BITS(cpu.csr[CSR_NAME::ESTAT], 21, 16) == 0x3f ? true : !BITS(cpu.csr[CSR_NAME::TLBIDX], 31, 31);
    tlb_entry.ppn0 = BITS(cpu.csr[CSR_NAME::TLBLO0], 31, 8);
    tlb_entry.plv0 = BITS(cpu.csr[CSR_NAME::TLBLO0], 3, 2);
    tlb_entry.mat0 = BITS(cpu.csr[CSR_NAME::TLBLO0], 5, 4);
    tlb_entry.d0 = BITS(cpu.csr[CSR_NAME::TLBLO0], 1, 1);
    tlb_entry.v0 = BITS(cpu.csr[CSR_NAME::TLBLO0], 0, 0);
    tlb_entry.ppn1 = BITS(cpu.csr[CSR_NAME::TLBLO1], 31, 8);
    tlb_entry.plv1 = BITS(cpu.csr[CSR_NAME::TLBLO1], 3, 2);
    tlb_entry.mat1 = BITS(cpu.csr[CSR_NAME::TLBLO1], 5, 4);
    tlb_entry.d1 = BITS(cpu.csr[CSR_NAME::TLBLO1], 1, 1);
    tlb_entry.v1 = BITS(cpu.csr[CSR_NAME::TLBLO1], 0, 0);
    cpu.tlb[idx] = tlb_entry;
}
void tlb_srch(){
    uint32_t asid = BITS(cpu.csr[CSR_NAME::ASID], 9, 0);
    uint32_t vppn = BITS(cpu.csr[CSR_NAME::TLBEHI], 31, 13);

    uint32_t hit_idx = -1;
    for(uint32_t i = 0; i < TLB_SIZE; i++){
        if(cpu.tlb[i].e && (cpu.tlb[i].g || cpu.tlb[i].asid == asid) && cpu.tlb[i].vppn == vppn){
            hit_idx = i;
            break;
        }
    }
    if(hit_idx == -1){
        cpu.csr[CSR_NAME::TLBIDX] = (cpu.csr[CSR_NAME::TLBIDX] & ~0x80000000) | (0x80000000 & 0x80000000);
    }
    else{
        uint32_t mask = TLB_SIZE - 1;
        cpu.csr[CSR_NAME::TLBIDX] = (cpu.csr[CSR_NAME::TLBIDX] & ~mask) | (hit_idx & mask);
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
            // clear TLB entry whose asid = asid and h = 0 and va[31:13] = va[31:13]
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