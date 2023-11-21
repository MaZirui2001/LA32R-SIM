.text
.global load_store
load_store:
    li.w  $r4, 0x89
    li.w  $r5, 0xab
    li.w  $r6, 0xcd
    li.w  $r7, 0xef

    li.w  $r8, 0x1c008000
    // li.w  $r9, 0x1c008001
    // li.w  $r10, 0x1c008002
    // li.w  $r11, 0x1c008003

    st.b $r4, $r8, 0
    st.b $r5, $r8, 1
    addi.w $r0, $r0, 0
    addi.w $r0, $r0, 0
    addi.w $r0, $r0, 0
    addi.w $r0, $r0, 0
    addi.w $r0, $r0, 0
    addi.w $r0, $r0, 0
    addi.w $r0, $r0, 0
    addi.w $r0, $r0, 0
    addi.w $r0, $r0, 0
    addi.w $r0, $r0, 0
    addi.w $r0, $r0, 0
    addi.w $r0, $r0, 0
    addi.w $r0, $r0, 0
    addi.w $r0, $r0, 0
    st.h $r6, $r8, 2
    st.b $r7, $r8, 3
    // addi.w $r0, $r0, 0
    // addi.w $r0, $r0, 0
    // addi.w $r0, $r0, 0
    // addi.w $r0, $r0, 0
    // addi.w $r0, $r0, 0
    // addi.w $r0, $r0, 0
    // addi.w $r0, $r0, 0
    // addi.w $r0, $r0, 0
    // addi.w $r0, $r0, 0
    // addi.w $r0, $r0, 0
    ld.w $r10, $r8, 0
    addi.w $r0, $r0, 0
    addi.w $r0, $r0, 0
    addi.w $r0, $r0, 0
    li.w $r4 , 0x89
    addi.w $r0, $r0, 0
    addi.w $r0, $r0, 0
    addi.w $r0, $r0, 0

fail:
    break 0

pass:
    li.w $r4, 0
    break 0