%ifndef MACROS_INC
%define MACROS_INC 1

; Default file descriptors
%define SYS_STDIN   0
%define SYS_STDOUT  1
%define SYS_STDERR  2

; Syscall Table
%define SYS_READ    0x00
%define SYS_WRITE   0x01
%define SYS_OPEN    0x02
%define SYS_CLOSE   0x03
%define SYS_EXIT    0x3c

%endif ; MACROS_INC
