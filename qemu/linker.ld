/* Minimal RISC-V Bare-Metal Linker Script */

OUTPUT_ARCH(riscv)
ENTRY(_start)

MEMORY
{
    RAM (rwx) : ORIGIN = 0x80001000, LENGTH = 128K
}

SECTIONS
{
    .text :
    {
        *(.text.init)
        *(.text*)
    } > RAM

    .rodata :
    {
        *(.rodata*)
    } > RAM

    .data :
    {
        *(.data*)
    } > RAM

    .bss :
    {
        *(.bss*)
        *(COMMON)
    } > RAM

    /DISCARD/ :
    {
        *(.comment)
    }
    _stack_top = ORIGIN(RAM) + LENGTH(RAM);
}
