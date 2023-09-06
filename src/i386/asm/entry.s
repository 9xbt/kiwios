; set magic number to 0x1BADB002 to identified by bootloader 
MAGIC equ 0x1BADB002

; set flags to 0
FLAGS equ 0

; set the checksum
CHECKSUM equ -(MAGIC + FLAGS)

; set multiboot enabled
section .multiboot

; define type to long for each data defined as above
dd MAGIC
dd FLAGS
dd CHECKSUM

; set the stack bottom 
global stackBottom:

; define the maximum size of stack to 1024 bytes
times 1024 db 0

; set the stack top which grows from higher to lower
stackTop:

section .text
    global _start
    extern kmain
    extern kloop

    _start:
        ; assign current stack pointer location to stackTop
	    mov esp, stackTop

        ; call kmain
	    call kmain

        ; main loop
        jmp _loop
        
    _loop:
        ; call kloop
        call kloop

        ; loop
        jmp _loop