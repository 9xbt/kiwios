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

    vga_init();
    gdt_init();
    idt_init();
    kbd_init();

    term_println(buildstr, 0x0F);
    term_println(logostr, 0x0D);
    term_println(copyrightstr, 0x0F);
}

void kloop(void)
{
    shell_run();
}
