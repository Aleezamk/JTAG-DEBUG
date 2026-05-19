.section .text
.globl _start

_start:
    la sp, _stack_top     # initialize stack
    call main             # call your C main

loop:
    j loop                # infinite loop
