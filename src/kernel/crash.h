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

#ifndef CRASH_H
#define CRASH_H

#include <inttypes.h>
#include "i386/isr.h"
#include "i386/vga.h"
#include "terminal.h"

void showCrashScreen(const char *exception) {
    vga_init(0x11);
    
    term_setCursorPos(1, 1);
    term_print("     __\n   _ / /\n  (_) |\n   _| |\n  (_) |\n     \\_\\", 0x1F);    

    term_setCursorPos(12, 3);
    term_print("A problem has been detected and kiwiOS has had to shut down.", 0x1F);

    term_setCursorPos(12, 5);
    term_print("*** STOP: ", 0x1F);
    term_print(exception, 0x1F);
    term_print(" ***", 0x1F);
}

#endif
