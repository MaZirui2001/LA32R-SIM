#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n28_sra_w_test)
    addi.w  s3, s3, 1
    addi.w s0, s0 ,1
    li.w  s2, 0x00
###test inst
    TEST_SRA_W(0x3e594300, 0x00000003, 0x07cb2860)
    TEST_SRA_W(0x171e0116, 0x00000004, 0x0171e011)
    TEST_SRA_W(0xfb98a1c4, 0x00000017, 0xfffffff7)
    TEST_SRA_W(0x6ff8fac0, 0x00000019, 0x00000037)
    TEST_SRA_W(0x09d99740, 0x00000015, 0x0000004e)
    TEST_SRA_W(0x9dce37bf, 0x0000000d, 0xfffcee71)
    TEST_SRA_W(0x5eb1157a, 0x00000015, 0x000002f5)
    TEST_SRA_W(0x88f10b2d, 0x0000000b, 0xfff11e21)
    TEST_SRA_W(0xb10709b0, 0x0000001a, 0xffffffec)
    TEST_SRA_W(0x12de8e6c, 0x00000016, 0x0000004b)
    TEST_SRA_W(0x5a19d7d4, 0x0000000a, 0x00168675)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n28_sra_w_test)
