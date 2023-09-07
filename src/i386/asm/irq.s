;
; kiwios - An OS made in C that's as simple as eating a kiwi
; Copyright (C) 2023 kiwiorg
;
; This program is free software; you can redistribute it and/or
; modify it under the terms of the GNU General Public License
; as published by the Free Software Foundation; either version 2
; of the License, or (at your option) any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program.  If not, see <https://www.gnu.org/licenses/>.
;

section .text
    extern isr_irq_handler

irq_handler:
    pusha                   ; push all registers
    mov ax, ds
    push eax                ; save ds

    mov ax, 0x10            ; load kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp
    call isr_irq_handler
    pop esp

    pop ebx                 ; restore kernel data segment
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa                    ; restore all registers
    add esp, 0x8            ; restore stack for erro no been pushed

    sti                     ; re-enable interrupts
    iret
    
%macro IRQ 2
  global irq_%1
  
  irq_%1:
    cli
    push byte 0
    push byte %2
    jmp irq_handler
%endmacro

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47
