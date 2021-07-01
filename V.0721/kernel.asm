bits 32
section .txt
align 4
dd 0x1BADB002
dd 0x00
dd - (0x1BADB002+0x00)

global start
extern kmain ;this function is located in kernel.c
start:
    cli
    call kmain
    hlt