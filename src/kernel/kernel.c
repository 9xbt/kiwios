/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#include <sys/common.h>
#include <sys/tables/gdt.h>
#include <sys/tables/idt.h>
#include <sys/tables/isr.h>
#include <sys/drivers/ps2/kb.h>
#include <sys/drivers/vga/vga.h>
#include <sys/drivers/vga/terminal.h>
#include <sys/apps/shell/shell.h>

void kmain()
{
    vga_init(0x0F);
    vga_enablecursor();
    gdt_init();
    idt_init();
    kbd_init();

    term_println(buildstr, 0x0F);
    term_println(logostr, 0x0D);
    term_println(copyrightstr, 0x0F);
}

void kloop()
{
    shell_run();
}
