/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#ifndef SHUTDOWN_H
#define SHUTDOWN_H

#include <sys/hw/io.h>
#include <sys/drivers/vga/terminal.h>

static void cmd_shutdown(void) {
    // All tried and true methods of shutting down VMs
    outw(0xB004, 0x2000);
    outw(0x604, 0x2000);
    outw(0x4004, 0x3400);

    term_println("\nFailed to shut down!", 0x07);
}

#endif
