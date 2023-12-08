#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n21_pcaddu12i_test)
    addi.w  s3, s3, 1
    addi.w s0, s0 ,1
    addi.w s2, zero, 0x0
###test inst
    TEST_PCADDU12I(0xc4bde)
    TEST_PCADDU12I(0xc41f2)
    TEST_PCADDU12I(0x481a0)
    TEST_PCADDU12I(0x4a6cc)
    TEST_PCADDU12I(0xf4f80)
    TEST_PCADDU12I(0xb7ac7)
    TEST_PCADDU12I(0xb78b0)
    TEST_PCADDU12I(0x6cd28)
    TEST_PCADDU12I(0x9a597)
    TEST_PCADDU12I(0x60695)
    TEST_PCADDU12I(0xee05f)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n21_pcaddu12i_test)
