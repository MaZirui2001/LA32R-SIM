#include "asm.h"
#include "regdef.h"
#include "inst_test.h"

LEAF(n3_addi_w_test)
    addi.w  s3, s3, 1
    addi.w s0, s0 ,1
    li.w     s2, 0x0
###test inst
    TEST_ADDI_W(0xfb263d10, 0x00000c96, 0xfb2639a6)
    TEST_ADDI_W(0x7ec10538, 0x00000996, 0x7ec0fece)
    TEST_ADDI_W(0x0e505a00, 0x00000718, 0xe506118 )
    TEST_ADDI_W(0xa522b9d7, 0x00000784, 0xa522c15b)
    TEST_ADDI_W(0x9b45d7c0, 0x000006d2, 0x9b45de92)
    TEST_ADDI_W(0xa4c655b8, 0x00000c62, 0xa4c6521a)
    TEST_ADDI_W(0xa52b697a, 0x00000159, 0xa52b6ad3)
    TEST_ADDI_W(0xdcc82666, 0x0000075b, 0xdcc82dc1)
    TEST_ADDI_W(0xab24a3c3, 0x00000b0f, 0xab249ed2)
    TEST_ADDI_W(0xdb650604, 0x000009ef, 0xdb64fff3)
    TEST_ADDI_W(0x7a305380, 0x00000974, 0x7a304cf4)
###detect exception
    beq s2, zero, inst_correct
    beq zero, zero, inst_fail
END(n3_addi_w_test)
