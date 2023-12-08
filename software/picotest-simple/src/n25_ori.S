#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n25_ori_test)
    addi.w  s3, s3, 1
    addi.w s0, s0 ,1
    li.w  s2, 0x00
###test inst
    TEST_ORI(0x0d48918a, 0x00000fe6, 0x0d489fee)
    TEST_ORI(0x891d17a0, 0x00000034, 0x891d17b4)
    TEST_ORI(0x8becf220, 0x00000800, 0x8becfa20)
    TEST_ORI(0x34e01280, 0x00000155, 0x34e013d5)
    TEST_ORI(0x20192340, 0x00000cf0, 0x20192ff0)
    TEST_ORI(0x06d71894, 0x0000043a, 0x06d71cbe)
    TEST_ORI(0x9c162100, 0x00000b7e, 0x9c162b7e)
    TEST_ORI(0xd2e07498, 0x000004ea, 0xd2e074fa)
    TEST_ORI(0xe5bd1f00, 0x00000ac0, 0xe5bd1fc0)
    TEST_ORI(0x05e05844, 0x00000c78, 0x05e05c7c)
    TEST_ORI(0x1c182184, 0x00000768, 0x1c1827ec)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n25_ori_test)
