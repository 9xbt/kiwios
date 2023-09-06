#include "terminal.h"
#include "i386/gdt.h"
#include "i386/idt.h"
#include "i386/isr.h"
#include "i386/ps2.h"

void kmain(void)
{
    gdt_init();
    idt_init();
    kbd_init();

    term_enableCursor();
    term_clear();

    term_print("kiwiOS [build 230905]", 0x0F);
    term_println("\n _    _          _  ___  ____\n| | _(_)_      _(_)/ _ \\/ ___|\n| |/ / \\ \\ /\\ / / | | | \\___ \\\n|   <| |\\ V  V /| | |_| |___) |\n|_|\\_\\_| \\_/\\_/ |_|\\___/|____/\n", 0x0D);
    term_println("Copyright (c) 2023 kiwiorg", 0x0F);
    term_println("All rights reserved\n", 0x0F);
}

void kloop(void)
{
    while (1)
    {
        //char c = kbd_getchar();
    }
}
