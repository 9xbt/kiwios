/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#ifndef HELP_H
#define HELP_H

#include <sys/drivers/vga/terminal.h>

static void cmd_help() {
    term_println("Available commands: ?/help, info, echo, cls/clear, reboot, shutdown", 0x07);
}

#endif
