#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n11_slli_w_test)
    addi.w  s3, s3, 1
    addi.w s0, s0 ,1
    li.w  s2, 0x0
###test inst
    TEST_SLLI_W(0x47994e5e, 0x00000001, 0x8f329cbc)
    TEST_SLLI_W(0x482ac578, 0x00000009, 0x558af000)
    TEST_SLLI_W(0x7419091a, 0x0000000b, 0xc848d000)
    TEST_SLLI_W(0xba65ad72, 0x00000003, 0xd32d6b90)
    TEST_SLLI_W(0x50a5f780, 0x00000018, 0x80000000)
    TEST_SLLI_W(0x738d2871, 0x0000000f, 0x94388000)
    TEST_SLLI_W(0x556faf00, 0x00000010, 0xaf000000)
    TEST_SLLI_W(0x300535d6, 0x00000008, 0x0535d600)
    TEST_SLLI_W(0x24ec2590, 0x00000003, 0x27612c80)
    TEST_SLLI_W(0xe3cb3a58, 0x0000000c, 0xb3a58000)
    TEST_SLLI_W(0xa20d0b10, 0x00000005, 0x41a16200)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n11_slli_w_test)
