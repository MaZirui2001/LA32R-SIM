#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n13_srai_w_test)
    addi.w  s3, s3, 1
    addi.w s0, s0 ,1
    li.w  s2, 0x00
###test inst
    TEST_SRAI_W(0x7e0083f0, 0x00000009, 0x003f0041)
    TEST_SRAI_W(0x13e680c0, 0x00000018, 0x00000013)
    TEST_SRAI_W(0x6d7388ec, 0x00000010, 0x00006d73)
    TEST_SRAI_W(0xc04efccc, 0x00000010, 0xffffc04e)
    TEST_SRAI_W(0xd6c67200, 0x00000014, 0xfffffd6c)
    TEST_SRAI_W(0x366ea0fe, 0x0000001e, 0x00000000)
    TEST_SRAI_W(0x4a3437c0, 0x00000007, 0x0094686f)
    TEST_SRAI_W(0x355d25a0, 0x00000013, 0x000006ab)
    TEST_SRAI_W(0x39adf6d1, 0x00000008, 0x0039adf6)
    TEST_SRAI_W(0xc0949780, 0x00000013, 0xfffff812)
    TEST_SRAI_W(0xf09ea1a0, 0x0000001d, 0xffffffff)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n13_srai_w_test)
