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
    b success
fail:
    li.w $r4, 0x1
    .word 0x80000000
success:
    li.w $r4, 0x0
    .word 0x80000000