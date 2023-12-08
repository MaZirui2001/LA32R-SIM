#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n6_sltu_test)
    addi.w  s3, s3, 1
    addi.w s0, s0 ,1
    li.w  s2, 0x00
###test inst
    TEST_SLTU(0x158f2b29, 0x421c0a42, 0x00000001)
    TEST_SLTU(0x60343bf8, 0xdd17b30a, 0x00000001)
    TEST_SLTU(0x2d5c3180, 0x14df4718, 0x00000000)
    TEST_SLTU(0x7560fb80, 0x2a9814b9, 0x00000000)
    TEST_SLTU(0xca606900, 0x94164d3a, 0x00000000)
    TEST_SLTU(0xdf4e2bc0, 0x37bd5259, 0x00000000)
    TEST_SLTU(0xd671d650, 0xf9a49f10, 0x00000001)
    TEST_SLTU(0x9e6341e0, 0x61c70130, 0x00000000)
    TEST_SLTU(0x7e12e4af, 0xa7fa9200, 0x00000001)
    TEST_SLTU(0x24d20908, 0xe7ff9120, 0x00000001)
    TEST_SLTU(0xf49d5fa6, 0xa79b2c2e, 0x00000000)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n6_sltu_test)
