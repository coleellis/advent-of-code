section .data

    filename db "day10.txt", 0x0

    ; Grid dimensions
    rows dd 0
    cols dd 0

section .bss

    grid resb 1000

section .text

    %include "common.inc"
    %include "macros.inc"

    global fill_grid
    global _start

fill_grid:
    xor ebx, ebx

.loop:
    ; read(fd, grid, 1)
    mov rax, SYS_READ
    lea rsi, [grid+ebx]
    mov rdx, 1
    syscall

    ; End condition -- no byte read
    cmp rax, 0
    jle .out

    ; Stop at the newline
    cmp byte [grid + ebx], 0xa
    je .nl

    ; This assumes the grid only has numbers
    ; so we can subtract 0x30 = '0' to get
    ; its digit value.
    sub byte [grid + ebx], 0x30
    jmp .inc

.nl:
    ; Ignore the newline, but store num cols
    cmp dword [cols], 0
    jnz .loop
    mov dword [cols], ebx
    jmp .loop

.inc:
    inc ebx
    jmp .loop

.out:
    ; Get number of rows
    xor rdx, rdx
    mov rax, rbx
    mov ebx, dword [cols]
    div ebx
    mov dword [rows], eax
    ret

_start:
    ; Get file contents
    mov rdi, filename
    call open_file

    ; Fill grid
    mov rdi, rax
    call fill_grid

    ; Cleanup
    close_file rax
    exit_program 0
