/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#include <sys/common.h>
#include <sys/hw/vga.h>
#include <sys/tables/gdt.h>
#include <sys/tables/idt.h>
#include <sys/tables/isr.h>
#include <sys/drivers/ps2/kb.h>
#include <sys/drivers/terminal/terminal.h>
#include <sys/drivers/ide/ide.h>
#include <sys/drivers/fat32/disk_interface.h>
#include <sys/drivers/fat32/fat32.h>
#include <sys/memory/memory.h>
#include <sys/apps/shell/shell.h>

extern void* kend;

void kmain()
{
    vga_init(0x0F);
    vga_enablecursor();
    mm_init(&kend);
    gdt_init();
    idt_init();
    if (!disk_mount(0))
    {
        term_print("[FAIL] ", 0x0C);
        term_print("Failed to mount HDD!\n", 0x0F);
    }
    kbd_init();

    term_println(buildstr, 0x0F);
    term_println(logostr, 0x0D);
    term_println(copyrightstr, 0x0F);
}

void kloop()
{
    shell_run();
}
