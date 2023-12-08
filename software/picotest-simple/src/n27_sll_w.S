#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n27_sll_w_test)
    addi.w  s3, s3, 1
    addi.w s0, s0 ,1
    li.w  s2, 0x00
###test inst
    TEST_SLL_W(0x79dbdb34, 0x00000007, 0xeded9a00)
    TEST_SLL_W(0xa903fa10, 0x0000001d, 0x00000000)
    TEST_SLL_W(0x6bd739d8, 0x0000000d, 0xe73b0000)
    TEST_SLL_W(0x273a784a, 0x0000000a, 0xe9e12800)
    TEST_SLL_W(0x34058000, 0x00000009, 0x0b000000)
    TEST_SLL_W(0x7c825738, 0x00000002, 0xf2095ce0)
    TEST_SLL_W(0x7016cbc2, 0x0000000a, 0x5b2f0800)
    TEST_SLL_W(0x4a4a30e0, 0x00000009, 0x9461c000)
    TEST_SLL_W(0x949d24ae, 0x0000000f, 0x92570000)
    TEST_SLL_W(0x951ca218, 0x0000001c, 0x80000000)
    TEST_SLL_W(0xc137cea0, 0x00000013, 0x75000000)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n27_sll_w_test)
