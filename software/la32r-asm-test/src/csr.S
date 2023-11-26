.text
.global csr
csr:
    li.w $r4, 0xabcdabcd
    li.w $r3, 0xf0f0f0f0
    csrxchg $r4, $r3, 0x6
    csrxchg $r4, $r3, 0x6
    csrxchg $r4, $r3, 0x6
    csrwr $r4, 0x6
    csrwr $r4, 0x6
    csrrd $r4, 0x6
    csrrd $r4, 0x6
    csrrd $r4, 0x6
    beq $r4, $r0, success
fail:
    li.w $r4, 0x1
    break 0
success:
    li.w $r4, 0x0
    break 0