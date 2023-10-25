.text
.global jirl

func1:
    li.w $r2, 0
    addi.w $r9, $r9, -1
    beq $r2, $r2, trap
    beq $r9, $r0, return
    bl func2
    bl func1
return:
    jirl $r0, $r1, 0
trap:
    jirl $r0, $r1, 0

func2:
    jirl $r0, $r1, 0

jirl:
    li.w $r5, 100
loop:
    li.w $r9, 16000
    bl  func1
    bl  func2
    addi.w $r5, $r5, -1
    bne $r5, $r0, loop
    b pass
    
fail:
    break 0

pass:
    li.w $r4, 0
    break 0