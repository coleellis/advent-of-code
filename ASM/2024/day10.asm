section .data

    filename db "day10.txt", 0x0

    ; Grid dimensions
    rows dd 0
    cols dd 0

section .bss

    grid resb 5000
    seen resb 5000

section .text

    %include "common.inc"
    %include "macros.inc"

    global dfs
    global fill_grid
    global run
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

dfs:

    push rbp
    mov rbp, rsp
    sub rsp, 0x4

    ; Store edx so I don't have to refactor this
    ; to not use edx and dl
    mov r8d, edx

    ; grid[i][j] == 9
    mov eax, edi
    imul eax, dword [cols]
    add eax, esi
    cmp byte [grid + eax], 0x9
    jne .one

    ; Part 1
    cmp edx, 0x1
    jne .unseen

    ; Check if we've been here
    cmp byte [seen + eax], 0x1
    je .seen
    mov byte [seen + eax], 0x1
    jmp .unseen

.seen:

    xor eax, eax
    leave
    ret

.unseen:

    mov eax, 1
    leave
    ret

.one:

    ; Return value
    mov dword [rbp - 0x4], 0x0

    ; i > 0
    cmp edi, 0x0
    jle .two

    ; arr[i-1][j] == arr[i][j] + 1
    mov eax, edi
    dec eax
    imul eax, dword [cols]
    add eax, esi
    mov dl, byte [grid + eax]
    mov eax, edi
    imul eax, dword [cols]
    add eax, esi
    mov al, byte [grid + eax]
    inc al
    cmp al, dl
    jne .two

    ; dfs(i - 1, j)
    dec edi
    mov edx, r8d
    call dfs
    add dword [rbp - 0x4], eax
    inc edi

.two:

    ; j > 0
    cmp esi, 0
    jle .three

    ; arr[i][j-1] == arr[i][j] + 1
    mov eax, edi
    imul eax, dword [cols]
    add eax, esi
    dec eax
    mov dl, byte [grid + eax]
    mov eax, edi
    imul eax, dword [cols]
    add eax, esi
    mov al, byte [grid + eax]
    inc al
    cmp al, dl
    jne .three

    ; dfs(i, j - 1)
    dec esi
    mov edx, r8d
    call dfs
    add dword [rbp - 0x4], eax
    inc esi

.three:

    ; i < rows - 1
    mov ebx, dword [rows]
    dec ebx
    cmp edi, ebx
    jge .four

    ; arr[i+1][j] == arr[i][j] + 1
    mov eax, edi
    inc eax
    imul eax, dword [cols]
    add eax, esi
    mov dl, byte [grid + eax]
    mov eax, edi
    imul eax, dword [cols]
    add eax, esi
    mov al, byte [grid + eax]
    inc al
    cmp al, dl
    jne .four

    ; dfs(i + 1, j)
    inc edi
    mov edx, r8d
    call dfs
    add dword [rbp - 0x4], eax
    dec edi

.four:

    ; j < cols - 1
    mov ebx, dword [cols]
    dec ebx
    cmp esi, ebx
    jge .end

    ; arr[i][j+1] == arr[i][j] + 1
    mov eax, edi
    imul eax, dword [cols]
    add eax, esi
    inc eax
    mov dl, byte [grid + eax]
    mov eax, edi
    imul eax, dword [cols]
    add eax, esi
    mov al, byte [grid + eax]
    inc al
    cmp al, dl
    jne .end

    ; dfs(i, j - 1)
    inc esi
    mov edx, r8d
    call dfs
    add dword [rbp - 0x4], eax
    dec esi

.end:

    mov eax, dword [rbp - 0x4]
    leave
    ret

run:

    push rbp
    mov rbp, rsp
    sub rsp, 0x10

    ; P1 and P2 totals
    mov dword [rbp - 0x10], 0x0
    mov dword [rbp - 0xc], 0x0

    ; Outer loop var
    mov dword [rbp - 0x8], 0x0

.outer:

    ; Inner loop var
    mov dword [rbp - 0x4], 0x0
    


.inner:

    ; grid[i][j] == 0
    mov eax, dword [rbp - 0x8]
    imul eax, dword [cols]
    add eax, dword [rbp - 0x4]
    mov bl, byte [grid + eax]
    test bl, bl
    jnz .end

    ; dfs(i, j, true)
    mov edi, dword [rbp - 0x8]
    mov esi, dword [rbp - 0x4]
    mov edx, 0x1
    call dfs
    add dword [rbp - 0x10], eax

    ; dfs(i, j, false)
    mov edi, dword [rbp - 0x8]
    mov esi, dword [rbp - 0x4]
    xor edx, edx
    call dfs
    add dword [rbp - 0xc], eax

    ; Looper for reset
    xor ecx, ecx

.reset:

    ; Wipe seen buffer
    mov byte [seen + ecx], 0
    inc ecx
    cmp ecx, 5000
    jl .reset

.end:

    ; Inner loop check
    inc dword [rbp - 0x4]
    mov eax, dword [cols]
    cmp dword [rbp - 0x4], eax
    jl .inner

    ; Outer loop check
    inc dword [rbp - 0x8]
    mov eax, dword [rows]
    cmp dword [rbp - 0x8], eax
    jl .outer

    ; Print one and two
    mov edi, dword [rbp - 0x10]
    call print_int
    mov edi, dword [rbp - 0xc]
    call print_int

    leave
    ret
    


_start:

    ; Get file contents
    mov rdi, filename
    call open_file

    ; Fill grid
    mov rdi, rax
    call fill_grid

    ; Run DFS on all start points
    call run

    ; Cleanup
    close_file rax
    exit_program 0
