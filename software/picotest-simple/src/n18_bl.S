#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n18_bl_test)
    addi.w  s3, s3, 1
    addi.w s0, s0 ,1
    li.w  s2, 0x0
###test inst
    TEST_BL(0x8c3e1efa, 0xeb2bd57c, 0x8c3e1efa, 0xeb2bd57c)
    TEST_BL(0xfbc1f5d0, 0xb91bc0b0, 0xfbc1f5d0, 0xb91bc0b0)
    TEST_BL(0xc1062356, 0xf8d60c60, 0xc1062356, 0xf8d60c60)
    TEST_BL(0x0b2dc8e4, 0xff276d2f, 0x0b2dc8e4, 0xff276d2f)
    TEST_BL(0x312fabd9, 0x970387ac, 0x312fabd9, 0x970387ac)
    TEST_BL(0x46360a68, 0xf903f5cd, 0x46360a68, 0xf903f5cd)
    TEST_BL(0x41cc660a, 0x52295cdc, 0x41cc660a, 0x52295cdc)
    TEST_BL(0x48fa3a04, 0x69636126, 0x48fa3a04, 0x69636126)
    TEST_BL(0xbcd7cfec, 0x779a95ec, 0xbcd7cfec, 0x779a95ec)
    TEST_BL(0x5fc96388, 0xc43c4580, 0x5fc96388, 0xc43c4580)
    TEST_BL(0x2e6acb2a, 0x3ff930e4, 0x2e6acb2a, 0x3ff930e4)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n18_bl_test)
