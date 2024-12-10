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

print_int:

    push rbp
    mov rbp, rsp
    sub rsp, 0x10

    ; Clear memory
    mov qword [rbp - 0x10], 0x0
    mov qword [rbp - 0x8], 0x0

    ; Add trailing newline
    lea rsi, [rbp - 0x1]
    mov byte [rsi], 0xa

    ; Variables for loop
    mov rax, rdi
    mov ecx, 10
    xor rbx, rbx

.loop:

    ; Get last digit
    xor rdx, rdx
    div rcx

    ; Turn to string digit
    add dl, '0'
    dec rsi
    mov byte [rsi], dl
    inc ebx

    ; Check loop condition
    test rax, rax
    jnz .loop

    ; Print
    mov rdx, rbp
    sub rdx, rsi
    mov rdi, 0x1
    mov rax, SYS_WRITE
    syscall

    leave
    ret
