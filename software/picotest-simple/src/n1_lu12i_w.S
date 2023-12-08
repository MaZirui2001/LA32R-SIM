#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n1_lu12i_w_test)
    addi.w  s3, s3, 1
    addi.w    s0, s0 ,1
    addi.w    s2, zero, 0x0
    lu12i.w   t2, 0x1
###test inst
    addi.w    t1, zero, 0x0
    TEST_LU12I_W(0x00000, 0x00000)
    TEST_LU12I_W(0x00001, 0x00000)
    TEST_LU12I_W(0x00002, 0x00000)
    TEST_LU12I_W(0x00003, 0x00000)
    TEST_LU12I_W(0x00004, 0x00000)
    TEST_LU12I_W(0x00005, 0x00000)
    TEST_LU12I_W(0x00006, 0x00000)
    TEST_LU12I_W(0x00007, 0x00000)
    TEST_LU12I_W(0x00008, 0x00000)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n1_lu12i_w_test)
