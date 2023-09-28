/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 */

#pragma once

char TERMINAL_X = 0;
char TERMINAL_Y = 0;

void term_clear(void);
void term_print(const char* str, const char col);
void term_println(const char* str, const char col);
void term_printchar(const char chr, const char col);
void term_scroll(void);
void term_setCursorPos(char x, char y);

#include <stdbool.h>
#include <sys/hw/io.h>
#include <sys/hw/vga.h>
#include "terminal.c"
