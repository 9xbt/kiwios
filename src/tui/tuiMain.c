//
// Created by ekeleze on 9/19/23.
//

#include "common.h"
#include "terminal.h"
#include "i386/gdt.h"
#include "i386/idt.h"
#include "i386/isr.h"
#include "i386/ps2.h"
#include "i386/vga.h"
#include "drivers/serial.h"
#include "shell/shell.h"

void tuiMain(void)
{
    term_clear();

    maxSel = 0;

    term_print("████████████████████████████████████████████████████████████████████████████████", 0x02);
    term_print("██", 0x02);
    term_print(" Apps                                                                       ", 0x0F);
    term_print("██", 0x02);
    term_print("████████████████████████████████████████████████████████████████████████████████", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█ ", 0x02);
    term_print("<Option 1>", 0x4F);
    term_print("                                                                   █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█ ", 0x02);
    term_print("<Option 2>", 0x0F);
    term_print("                                                                   █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("████████████████████████████████████████████████████████████████████████████████", 0x02);

    while (true) {
        int scancode = get_scancode();

        if (scancode == 0x01) {
            term_clear();
            break;
        }

        if (scancode == 0x48) {
            selectionHandler(true);
        }

        if (scancode == 0x50) {
            selectionHandler(false);
        }
    }
}

void selectionHandler(bool Up) {
    term_print("████████████████████████████████████████████████████████████████████████████████", 0x02);
    term_print("██", 0x02);
    term_print(" Apps                                                                       ", 0x0F);
    term_print("██", 0x02);
    term_print("████████████████████████████████████████████████████████████████████████████████", 0x02);

    if (Up) {
        cSel = cSel + 1;
        if (cSel > maxSel) {
            cSel = 0;
        }

        // Handle actual selection

        term_print("█                                                                              █", 0x02);
        term_print("█ ", 0x02);
        term_print("<Option 1>", 0x4F);
        term_print("                                                                   █", 0x02);
        term_print("█                                                                              █", 0x02);
        term_print("█ ", 0x02);
        term_print("<Option 2>", 0x0F);
        term_print("                                                                   █", 0x02);

    } else {
        cSel = cSel - 1;
        if (cSel < 0) {
            cSel = maxSel;
        }

        // Handle actual selection

        term_print("█                                                                              █", 0x02);
        term_print("█ ", 0x02);
        term_print("<Option 1>", 0x0F);
        term_print("                                                                   █", 0x02);
        term_print("█                                                                              █", 0x02);
        term_print("█ ", 0x02);
        term_print("<Option 2>", 0x4F);
        term_print("                                                                   █", 0x02);
    }

    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("█                                                                              █", 0x02);
    term_print("████████████████████████████████████████████████████████████████████████████████", 0x02);
}