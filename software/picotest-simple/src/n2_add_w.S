#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n2_add_w_test)
    addi.w  s3, s3, 1
    addi.w s0, s0 ,1
    addi.w s2, zero, 0x0
###test inst
    TEST_ADD_W(0x1adef300, 0x51dd58de, 0x6cbc4bde)
    TEST_ADD_W(0x9674ea60, 0xab475792, 0x41bc41f2)
    TEST_ADD_W(0xb60db986, 0x2e56c81a, 0xe46481a0)
    TEST_ADD_W(0xd55edbc0, 0x60f5cb0c, 0x3654a6cc)
    TEST_ADD_W(0xa2b8e4e0, 0xc6e66aa0, 0x699f4f80)
    TEST_ADD_W(0xec0501a1, 0x18267926, 0x042b7ac7)
    TEST_ADD_W(0x6ade36b0, 0xc01d4200, 0x2afb78b0)
    TEST_ADD_W(0x6c088ce8, 0xa1ce4040, 0x0dd6cd28)
    TEST_ADD_W(0x4f16e8c7, 0x2412bcd0, 0x7329a597)
    TEST_ADD_W(0x020a51db, 0xb68bb4ba, 0xb8960695)
    TEST_ADD_W(0x407989a0, 0x701556bf, 0xb08ee05f)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n2_add_w_test)
