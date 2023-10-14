.section entry, "ax"
.globl _start
.type _start, @function

_start:
  move $r23, $r0
  la $r3, _stack_pointer
  b call_main
  // b main

