#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n23_sltui_test)
    addi.w  s3, s3, 1
    addi.w s0, s0 ,1
    li.w  s2, 0x0
###test inst
    TEST_SLTUI(0xc254e3d8, 0x00000469, 0x0)
    TEST_SLTUI(0x7a56334c, 0x000002f5, 0x0)
    TEST_SLTUI(0xabcd2c00, 0x000007c7, 0x0)
    TEST_SLTUI(0x25c835b7, 0x00000dba, 0x1)
    TEST_SLTUI(0x10ea3bf2, 0x00000ff4, 0x1)
    TEST_SLTUI(0x494c2712, 0x0000007a, 0x0)
    TEST_SLTUI(0x977b0d34, 0x00000280, 0x0)
    TEST_SLTUI(0x868f7bf9, 0x000005e7, 0x0)
    TEST_SLTUI(0x85a78bab, 0x00000898, 0x1)
    TEST_SLTUI(0x67b13d20, 0x000005a5, 0x0)
    TEST_SLTUI(0xd98263b6, 0x00000642, 0x0)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n23_sltui_test)
