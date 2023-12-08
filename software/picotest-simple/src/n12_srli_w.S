#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n12_srli_w_test)
    addi.w  s3, s3, 1
    addi.w s0, s0 ,1
    li.w  s2, 0x00
###test inst
    TEST_SRLI_W(0x8e8ffce0, 0x00000002, 0x23a3ff38)
    TEST_SRLI_W(0x49291230, 0x0000000f, 0x00009252)
    TEST_SRLI_W(0x25da68a0, 0x00000004, 0x025da68a)
    TEST_SRLI_W(0xecacf656, 0x0000000e, 0x0003b2b3)
    TEST_SRLI_W(0xe7bfc848, 0x0000001f, 0x00000001)
    TEST_SRLI_W(0x00115809, 0x0000001f, 0x00000000)
    TEST_SRLI_W(0x7a886604, 0x00000019, 0x0000003d)
    TEST_SRLI_W(0x7fe7a7de, 0x0000000f, 0x0000ffcf)
    TEST_SRLI_W(0x76c29838, 0x00000005, 0x03b614c1)
    TEST_SRLI_W(0xa93f5944, 0x00000011, 0x0000549f)
    TEST_SRLI_W(0x5ec1c900, 0x0000001f, 0x00000000)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n12_srli_w_test)
