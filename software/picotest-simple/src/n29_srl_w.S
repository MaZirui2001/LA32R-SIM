#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n29_srl_w_test)
    addi.w  s3, s3, 1
    addi.w s0, s0 ,1
    li.w  s2, 0x00
###test inst
    TEST_SRL_W(0x1f8f6000, 0x0000001c, 0x00000001)
    TEST_SRL_W(0xe51f6e9c, 0x00000002, 0x3947dba7)
    TEST_SRL_W(0x055df7e0, 0x00000008, 0x00055df7)
    TEST_SRL_W(0xa821b3e6, 0x00000019, 0x00000054)
    TEST_SRL_W(0xf3330c74, 0x0000000a, 0x003cccc3)
    TEST_SRL_W(0x096b5f00, 0x0000001f, 0x00000000)
    TEST_SRL_W(0x16f2bd5e, 0x0000001b, 0x00000002)
    TEST_SRL_W(0x938a4c80, 0x0000001f, 0x00000001)
    TEST_SRL_W(0x499578b8, 0x0000001c, 0x00000004)
    TEST_SRL_W(0xe9174919, 0x00000019, 0x00000074)
    TEST_SRL_W(0x71501460, 0x00000013, 0x00000e2a)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n29_srl_w_test)
