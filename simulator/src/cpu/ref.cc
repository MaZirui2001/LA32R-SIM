#include <common.h>
#include <difftest.h>
#include <paddr.h>
#include <cpu.h>
#include <cstring>
#include <priv.h>
#include <mmu.h>
__EXPORT void difftest_memcpy(paddr_t addr, void *buf, size_t n, bool direction) {
    if (direction == DIFFTEST_TO_REF) {
        memcpy(addr_convert(addr), buf, n);
    } else {
        memcpy(buf, addr_convert(addr), n);
    }
}
__EXPORT void difftest_regcpy(uint64_t *dut, bool direction) {
    if (direction == DIFFTEST_TO_REF) {
        memcpy(&cpu, dut, (REG_SIZE) * sizeof(uint32_t));
    } else {
        memcpy(dut, &cpu, (REG_SIZE) * sizeof(uint32_t));
    }
}

__EXPORT void difftest_raise_intr(int irq) {
    cpu.csr[0x4] = (cpu.csr[0x4] & 0xffffe000) | irq;
    if(irq & 0x800){
        cpu.timer_int = 1;
    }
    cpu.pc = do_exception(0x0, 0x0);
}

__EXPORT void difftest_exec(uint64_t n) {
    cpu_exec(n);
}
__EXPORT void difftest_tlbfill_sync(uint32_t idx){
    tlb_write(idx);
}

__EXPORT void difftest_init(uint64_t *dut){
    memcpy(&cpu, dut, (REG_SIZE + CSR_SIZE) * sizeof(uint32_t));
}

