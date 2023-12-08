#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n24_andi_test)
    addi.w  s3, s3, 1
    addi.w s0, s0 ,1
    li.w  s2, 0x00
###test inst
    TEST_ANDI(0x4c23cdd4, 0x00000e89, 0x00000c80)
    TEST_ANDI(0xa1286600, 0x000008aa, 0x00000000)
    TEST_ANDI(0xea42f8c0, 0x00000d3e, 0x00000800)
    TEST_ANDI(0xfbbea379, 0x00000654, 0x00000250)
    TEST_ANDI(0x701ff540, 0x0000001f, 0x00000000)
    TEST_ANDI(0x509b8bd4, 0x00000d3c, 0x00000914)
    TEST_ANDI(0x7f92d195, 0x000007a0, 0x00000180)
    TEST_ANDI(0x2e273e78, 0x0000075e, 0x00000658)
    TEST_ANDI(0x866dcbc0, 0x0000084c, 0x00000840)
    TEST_ANDI(0xd0b35788, 0x00000224, 0x00000200)
    TEST_ANDI(0x05d143e2, 0x0000037a, 0x00000362)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n24_andi_test)
