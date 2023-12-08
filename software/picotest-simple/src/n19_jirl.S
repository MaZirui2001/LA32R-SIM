#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n19_jirl_test)
    addi.w  s3, s3, 1
    addi.w s0, s0 ,1
    li.w  s2, 0x0
###test inst
    TEST_JIRL(0xc21e6e78, 0x0e2ea248, 0xc21e6e78, 0x0e2ea248)
    TEST_JIRL(0x6793c49c, 0x654b2d70, 0x6793c49c, 0x654b2d70)
    TEST_JIRL(0xff0a08b0, 0x50d2bb38, 0xff0a08b0, 0x50d2bb38)
    TEST_JIRL(0x70640e44, 0x391afbca, 0x70640e44, 0x391afbca)
    TEST_JIRL(0x0506233b, 0xb14115a8, 0x0506233b, 0xb14115a8)
    TEST_JIRL(0x9c781547, 0xde178220, 0x9c781547, 0xde178220)
    TEST_JIRL(0xa8dd2c05, 0xfb3d8034, 0xa8dd2c05, 0xfb3d8034)
    TEST_JIRL(0x01c45860, 0x6bdc4550, 0x01c45860, 0x6bdc4550)
    TEST_JIRL(0x47d1c1c0, 0xf853cd8e, 0x47d1c1c0, 0xf853cd8e)
    TEST_JIRL(0x7089b600, 0xb8da1d86, 0x7089b600, 0xb8da1d86)
    TEST_JIRL(0x7292aac0, 0x0e66c29a, 0x7292aac0, 0x0e66c29a)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n19_jirl_test)
