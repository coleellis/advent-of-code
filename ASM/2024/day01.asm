section .data

    filename db "day02.txt", 0x0

section .text

global _start

_start:
    ; 0x3c (exit)
    mov rax, 0x3c
    xor rdi, rdi
    syscall

