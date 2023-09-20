/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#ifndef INFO_H
#define INFO_H

#include <sys/common.h>
#include <sys/drivers/vga/vga.h>
#include <sys/drivers/vga/terminal.h>

static void cmd_info() {
    term_println(buildstr, 0x07);
    term_println(logostr, 0x0D);
    term_println(copyrightstr, 0x07);
    term_println(licensestr, 0x07);
    term_println(peoplestr, 0x07);
}

#endif
