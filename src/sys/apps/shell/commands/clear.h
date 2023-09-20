/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#ifndef CLEAR_H
#define CLEAR_H

#include <sys/drivers/vga/terminal.h>

static void cmd_clear() {
    term_clear();
}

#endif
