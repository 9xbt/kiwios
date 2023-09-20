;
; kiwios - An OS made in C that's as simple as eating a kiwi
; Copyright (C) 2023 kiwiorg
;

section .text
    global load_idt

load_idt:
    mov eax, [esp + 4]
    lidt [eax]
    ret
