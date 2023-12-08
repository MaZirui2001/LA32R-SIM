#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n9_xor_test)
    addi.w  s3, s3, 1
    addi.w s0, s0 ,1
    li.w  s2, 0x00
###test inst
    TEST_XOR(0x1773df80, 0xb5af51d2, 0xa2dc8e52)
    TEST_XOR(0xe6223550, 0x909c98da, 0x76bead8a)
    TEST_XOR(0xf5c8a598, 0x25fd0240, 0xd035a7d8)
    TEST_XOR(0x24b53f20, 0x14d3aae8, 0x306695c8)
    TEST_XOR(0x59451f38, 0xe8aaf42b, 0xb1efeb13)
    TEST_XOR(0xca5b17a0, 0xcec70d58, 0x049c1af8)
    TEST_XOR(0x8b6a1e78, 0xa89e5ed2, 0x23f440aa)
    TEST_XOR(0x8a580190, 0xae39e660, 0x2461e7f0)
    TEST_XOR(0xdd3472f0, 0xc148dd08, 0x1c7caff8)
    TEST_XOR(0x525857e0, 0x94d67860, 0xc68e2f80)
    TEST_XOR(0xb61c2c40, 0xc15a0baa, 0x774627ea)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n9_xor_test)
