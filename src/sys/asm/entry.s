;
; kiwios - An OS made in C that's as simple as eating a kiwi
; Copyright (C) 2023 kiwiorg
;

[BITS 32]

MAGIC equ 0x1BADB002
FLAGS equ 0
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

global stackBottom:
times 4096 db 0
stackTop:

section .text
    global _start
    extern kmain
    extern kloop

    _start:
	    mov esp, stackTop

	    call kmain
        jmp _loop
        
    _loop:
        call kloop
        jmp _loop