/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "common.h"
#include "i386/gdt.h"
#include "i386/idt.h"
#include "i386/isr.h"
#include "i386/ps2.h"
#include "i386/vga.h"
#include "terminal.h"
#include "shell/shell.h"

void kmain(void)
{
    term_clear();

    vga_init(0x0F);
    gdt_init();
    idt_init();
    //asm volatile("div %ecx");
    kbd_init();

    term_println(buildstr, 0x0F);
    term_println(logostr, 0x0D);
    term_println(copyrightstr, 0x0F);
}

void kloop(void)
{
    shell_run();
}
