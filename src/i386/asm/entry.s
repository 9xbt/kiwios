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

MAGIC equ 0x1BADB002
FLAGS equ 0
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

global stackBottom:
times 1024 db 0
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