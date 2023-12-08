#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n22_slti_test)
    addi.w  s3, s3, 1
    addi.w s0, s0 ,1
    li.w  s2, 0x00
###test inst
    TEST_SLTI(0xd9d129b5, 0x00000988, 0x1)
    TEST_SLTI(0xbc13c90c, 0x000005e9, 0x1)
    TEST_SLTI(0x9c7c8fa6, 0x00000db8, 0x1)
    TEST_SLTI(0xfa9c8750, 0x000007fe, 0x1)
    TEST_SLTI(0x5a5723dc, 0x00000220, 0x0)
    TEST_SLTI(0x3bddb5bc, 0x00000444, 0x0)
    TEST_SLTI(0xf3dccb50, 0x000003fb, 0x1)
    TEST_SLTI(0xdb8e5d8c, 0x00000516, 0x1)
    TEST_SLTI(0x1da08490, 0x00000dfc, 0x0)
    TEST_SLTI(0x8e7b1468, 0x00000fa2, 0x1)
    TEST_SLTI(0xaa2475a4, 0x00000422, 0x1)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n22_slti_test)
