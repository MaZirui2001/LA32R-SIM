
.text
.global addw
addw:
    li.w $r4, 1
    li.w $r5, 200
loop: 
    li.w $r10, 16
    li.w $r11, 18
    add.w $r12, $r10, $r11
    add.w $r13, $r10, $r11
    add.w $r14, $r10, $r11
    add.w $r15, $r10, $r11
    add.w $r16, $r10, $r11
    add.w $r17, $r10, $r11
    add.w $r18, $r10, $r11
    add.w $r19, $r10, $r11
    add.w $r20, $r10, $r11
    li.w $r10, 34

    
    bne $r12, $r10, fail
    bne $r13, $r10, fail
    bne $r14, $r10, fail
    addi.w $r5, $r5, -1
    beq $r5, $r0, pass
    b loop


fail:
    break 0

pass:
    li.w $r4, 0
    break 0