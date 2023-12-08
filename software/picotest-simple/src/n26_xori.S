#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n26_xori_test)
    addi.w  s3, s3, 1
    addi.w s0, s0 ,1
    li.w  s2, 0x00
###test inst
    TEST_XORI(0x4406a500, 0x000004bf, 0x4406a1bf)
    TEST_XORI(0xb5f52460, 0x00000abe, 0xb5f52ede)
    TEST_XORI(0x34547fee, 0x00000cfa, 0x34547314)
    TEST_XORI(0x4d7c6e70, 0x00000df4, 0x4d7c6384)
    TEST_XORI(0x0f04a9e8, 0x0000031e, 0x0f04aaf6)
    TEST_XORI(0xebec4441, 0x0000040b, 0xebec404a)
    TEST_XORI(0x6634ae18, 0x00000388, 0x6634ad90)
    TEST_XORI(0x91ab1a58, 0x00000a27, 0x91ab107f)
    TEST_XORI(0x799c2469, 0x00000287, 0x799c26ee)
    TEST_XORI(0x33412a00, 0x000009cd, 0x334123cd)
    TEST_XORI(0x3e00f810, 0x00000da6, 0x3e00f5b6)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n26_xori_test)
