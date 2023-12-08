#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n8_or_test)
    addi.w  s3, s3, 1
    addi.w s0, s0 ,1
    li.w  s2, 0x0
###test inst
    TEST_OR(0x50e41484, 0xad35ea94, 0xfdf5fe94)
    TEST_OR(0xbbbfafe4, 0xc8e94400, 0xfbffefe4)
    TEST_OR(0xf293f134, 0xa7cc798a, 0xf7dff9be)
    TEST_OR(0xfb4eee5e, 0x66968a90, 0xffdeeede)
    TEST_OR(0xbc988af7, 0x986e2136, 0xbcfeabf7)
    TEST_OR(0x1ec77b94, 0x1bf2b5cc, 0x1ff7ffdc)
    TEST_OR(0x3f4f40ca, 0x89bf86b2, 0xbfffc6fa)
    TEST_OR(0xcf97afe8, 0x3c845a89, 0xff97ffe9)
    TEST_OR(0x74926eec, 0x556dc1dc, 0x75ffeffc)
    TEST_OR(0xbb9c5258, 0xc090aa10, 0xfb9cfa58)
    TEST_OR(0xcad74640, 0xdb28e181, 0xdbffe7c1)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n8_or_test)
