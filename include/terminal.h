/*
 * kiwios - An OS made in C that's as simple as eating a kiwi
 * Copyright (C) 2023 kiwiorg
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef TERMINAL_H
#define TERMINAL_H

char TERMINAL_X = 0;
char TERMINAL_Y = 0;

void term_clear(void);

void term_print(const char* str, const char col);

void term_println(const char* str, const char col);

void term_printchar(const char chr, const char col);

void term_scroll(void);

void term_setCursorPos(char x, char y);

#include "stdbool.h"
#include "i386/port.h"
#include "i386/vga.h"
#include "../src/terminal.c"

#endif