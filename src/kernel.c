#include "terminal.h"
#include "i386/gdt.h"
#include "i386/idt.h"
#include "i386/isr.h"
#include "i386/ps2.h"
#include "i386/vga.h"

void kmain(void)
{
    term_clear();

    vga_init();
    gdt_init();
    idt_init();
    kbd_init();

    term_print("\nkiwiOS [build 230906]", 0x0F);
    term_println("\n _    _          _  ___  ____\n| | _(_)_      _(_)/ _ \\/ ___|\n| |/ / \\ \\ /\\ / / | | | \\___ \\\n|   <| |\\ V  V /| | |_| |___) |\n|_|\\_\\_| \\_/\\_/ |_|\\___/|____/\n", 0x0D);
    term_println("Copyright (c) 2023 kiwiorg", 0x0F);
    term_println("All rights reserved\n", 0x0F);
}

void kloop(void)
{
}
