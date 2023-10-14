
.text
.global addw
addw:
    li.w $r4, 1
    li.w $r10, 16
    li.w $r11, 18
    add.w $r12, $r10, $r11
    li.w $r10, 34
    beq $r12, $r10, pass

fail:
    break 0

pass:
    li.w $r4, 0
    break 0