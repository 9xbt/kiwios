/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#ifndef CRASH_H
#define CRASH_H

void showCrashScreen(const char *exception);

#include <inttypes.h>
#include <sys/tables/isr.h>
#include <sys/drivers/vga/vga.h>
#include <sys/drivers/vga/terminal.h>
#include "bsod.c"

#endif
