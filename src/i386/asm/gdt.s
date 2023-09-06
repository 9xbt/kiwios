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
    global load_gdt

load_gdt:
    mov eax, [esp + 4]      ; get gdt pointer
    lgdt [eax]              ; load gdt

    mov ax, 0x10            ; kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    cli                     ; clear interrupts
    mov	eax, cr0            ; set bit 0 in cr0 to enter protected mode
    or eax, 1
    mov	cr0, eax

    jmp 0x08:far_jump       ; jump to far with code data segment
far_jump:
    ret
