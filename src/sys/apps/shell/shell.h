/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#ifndef SHELL_H
#define SHELL_H

#include <sys/drivers/ps2/kb.h>
#include <sys/drivers/vga/terminal.h>
#include <sys/hw/io.h>
#include <string.h>
#include "commands/help.h"
#include "commands/info.h"
#include "commands/clear.h"
#include "commands/echo.h"
#include "commands/reboot.h"
#include "commands/shutdown.h"

static void shell_run() {
    term_print("$ ", 0x0F);
    char* input = kbd_getstring();

    if (!strcmp(input, ""));
    else if (!strcmp(input, "?") || !strcmp(input, "help")) {
        cmd_help();
    }
    else if (!strcmp(input, "info")) {
        cmd_info();
    }
    else if (!strcmp(input, "cls") || !strcmp(input, "clear")) {
        cmd_clear();
    }
    else if (!strncmp(input, "echo", 4)) {
        cmd_echo(input);
    }
    else if (!strcmp(input, "reboot")) {
        cmd_reboot();
    }
    else if (!strcmp(input, "shutdown")) {
        cmd_shutdown();
    }
    else {
        term_print("Command \"", 0x0C);
        term_print(input, 0x0C);
        term_println("\" not found.", 0x0C);
    }
}

#endif
