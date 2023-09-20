/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#ifndef ECHO_H
#define ECHO_H

#include <sys/drivers/vga/terminal.h>

static void cmd_echo(char* input) {
    term_println(input + 5, 0x07);
}

#endif
