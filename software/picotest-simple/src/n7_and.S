#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n7_and_test)
    addi.w  s3, s3, 1
    addi.w s0, s0 ,1
    li.w  s2, 0x00
###test inst
    TEST_AND(0x5c95951a, 0xca00c414, 0x48008410)
    TEST_AND(0x9ba8ba70, 0xe99fce38, 0x89888a30)
    TEST_AND(0xd30319e0, 0x0ba4cff6, 0x030009e0)
    TEST_AND(0xce6912e8, 0x6676b20e, 0x46601208)
    TEST_AND(0x1d337960, 0x744dd280, 0x14015000)
    TEST_AND(0x79565822, 0xd58a73c7, 0x51025002)
    TEST_AND(0x5493ce59, 0xa7e95630, 0x04814610)
    TEST_AND(0x4a90f478, 0xdea16664, 0x4a806460)
    TEST_AND(0x912edb93, 0x8f4b9870, 0x810a9810)
    TEST_AND(0x08040b84, 0xfa97e908, 0x08040900)
    TEST_AND(0x187a1708, 0xff84714a, 0x18001108)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n7_and_test)
