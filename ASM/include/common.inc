section .data

    file_error db "Could not open file", 0xa
    file_error_len equ $ - file_error

section .text

%include "macros.inc"

%macro close_file 1
    mov rax, SYS_CLOSE
    mov rdi, $1
    syscall
%endmacro

%macro exit_program 1
    mov rax, SYS_EXIT
    mov rdi, $1
    syscall
%endmacro

open_file:
    ; open(filename, O_RDONLY)
    mov rax, SYS_OPEN
    xor rsi, rsi
    xor rdx, rdx
    syscall

    cmp rax, 0
    jle .bad
    ret

.bad:

    ; write(SYS_STDOUT, file_error, file_error_len)
    mov rax, SYS_WRITE
    mov rdi, SYS_STDOUT
    mov rsi, file_error
    mov rdx, file_error_len
    syscall

    exit_program 1
