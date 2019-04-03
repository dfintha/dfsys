MBALIGN equ 1 << 0
MEMINFO equ 1 << 1
FLAGS equ MBALIGN | MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .bss
align 16
stack_bottom:
    resb 16384
stack_top:

section .text
global _start:function (_start.end - _start)
_start:
    mov esp, stack_top      ; set up the top of the stack
    extern kmain            ; declare kernel entry point
    call kmain              ; call the kernel
    cli                     ; clear interrupts
.hang:
    hlt                     ; halt
    jmp .hang               ; infinite loop
.end:
