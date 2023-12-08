#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n10_nor_test)
    addi.w  s3, s3, 1
    addi.w s0, s0 ,1
    li.w  s2, 0x00
###test inst
    TEST_NOR(0xad9cc00e, 0x38b7ec24, 0x424013d1)
    TEST_NOR(0x668d5db0, 0xa0945bf0, 0x1962a00f)
    TEST_NOR(0x6d830f90, 0x66b31460, 0x904ce00f)
    TEST_NOR(0x6008f35f, 0x54ae81fa, 0x8b510c00)
    TEST_NOR(0xacc8f2d2, 0x51491760, 0x0236080d)
    TEST_NOR(0x2f8039e0, 0xf4ac6718, 0x00538007)
    TEST_NOR(0xdc9eddc0, 0x1a3aebc8, 0x21410037)
    TEST_NOR(0xfa40f126, 0xfa382538, 0x05870ac1)
    TEST_NOR(0x06033064, 0xa758b5c0, 0x58a44a1b)
    TEST_NOR(0x8d0f7094, 0x13b7b000, 0x60400f6b)
    TEST_NOR(0x596eaab2, 0x9e2f6d2f, 0x20901040)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n10_nor_test)
