#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n4_sub_w_test)
    addi.w  s3, s3, 1
    addi.w s0, s0 ,1
    li.w     s2, 0x00
###test inst
    TEST_SUB_W(0xd6fc0584, 0x5f9765a8, 0x77649fdc)
    TEST_SUB_W(0xbf9c95c2, 0x3368890e, 0x8c340cb4)
    TEST_SUB_W(0xda67a888, 0xa727b830, 0x333ff058)
    TEST_SUB_W(0x23858808, 0x657a98bc, 0xbe0aef4c)
    TEST_SUB_W(0x040ae1f0, 0x4eff0fe8, 0xb50bd208)
    TEST_SUB_W(0x45c9e968, 0xbaecca18, 0x8add1f50)
    TEST_SUB_W(0x541bce6c, 0xe3eeb018, 0x702d1e54)
    TEST_SUB_W(0x02825068, 0xa1de973a, 0x60a3b92e)
    TEST_SUB_W(0xf8c113c0, 0x052ce450, 0xf3942f70)
    TEST_SUB_W(0x96868792, 0xd109051c, 0xc57d8276)
    TEST_SUB_W(0xf53c6d68, 0xc1c46588, 0x337807e0)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n4_sub_w_test)
