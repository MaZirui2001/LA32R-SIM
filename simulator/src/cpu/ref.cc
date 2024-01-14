#include <common.h>
#include <difftest.h>
#include <paddr.h>
#include <cpu.h>
#include <cstring>
#include <decode.h>
__EXPORT void difftest_memcpy(paddr_t addr, void *buf, size_t n, bool direction) {
    if (direction == DIFFTEST_TO_REF) {
        memcpy(addr_convert(addr), buf, n);
    } else {
        memcpy(buf, addr_convert(addr), n);
    }
}
__EXPORT void difftest_regcpy(uint64_t *dut, bool direction) {
    if (direction == DIFFTEST_TO_REF) {
        memcpy(&cpu, dut, (REG_SIZE+CSR_SIZE) * sizeof(uint32_t));
    } else {
        memcpy(dut, &cpu, (REG_SIZE+CSR_SIZE) * sizeof(uint32_t));
    }
}

__EXPORT void difftest_raise_intr(int irq) {
    cpu.csr[0x5] = (cpu.csr[0x5] & 0xffffe000) | irq;
    cpu.pc = do_exception(0x0, 0x0);
}

__EXPORT void difftest_exec(uint64_t n) {
    cpu_exec(n);
}

